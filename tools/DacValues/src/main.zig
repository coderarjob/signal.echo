const std = @import("std");
const Dac = @import("Dac.zig");
const Allocator = std.mem.Allocator;
const math = std.math;
const expect = std.testing.expect;
const expectApproxEqAbs = std.testing.expectApproxEqAbs;
const assert = std.debug.assert;
const stdout = std.io.getStdOut().writer();

const PI = math.pi;
const F64ArrayList = std.ArrayList(f64);

const Waves = enum {
    sine,
    amplitude_modulation,
    sine_x_on_x,
};

const ParsedArgResult = struct {
    mode: Waves,
    interpolate: bool,
    freq_scalar: f64,
    dac_bits: u32
};

fn parse_args(args: *std.process.ArgIterator) !ParsedArgResult {
    var interpolate: bool = false;
    var freq_scalar: f64 = 1.0;
    var dac_bits: ?u32 = null;
    var mode: ?Waves = null;
    while (args.next()) |arg| {
        if (std.mem.eql(u8, arg, "--interpolate")) {
            interpolate = true;
        } else if (std.mem.eql(u8, arg, "--freq")) {
            const value = args.next() orelse return error.InvalidFrequency;
            freq_scalar = try std.fmt.parseFloat(f64, value);
        } else if (std.mem.eql(u8, arg, "--bits")) {
            const value = args.next() orelse return error.InvalidDacBits;
            dac_bits = try std.fmt.parseInt(u32, value, 10);
        } else {
            mode = std.meta.stringToEnum(Waves, arg) orelse return error.InvalidModeOrOption;
        }
    }

    return .{
        .mode = mode orelse return error.ModeNotSet,
        .interpolate = interpolate,
        .freq_scalar =  freq_scalar,
        .dac_bits = dac_bits orelse return error.DacBitsNotSet
    };
}

fn usage(program_name: []const u8) void {
    std.debug.print("Usage: {s} [--interpolate] [--freq=<freq>] ", .{program_name});
    inline for (std.meta.tags(Waves), 0..) |t, i| {
        const c = if (i == 0) '[' else '|';
        std.debug.print("{c}{s}", .{ c, @tagName(t) });
    }
    std.debug.print("]\n", .{});
}

pub fn main() !void {
    var gpa: std.heap.GeneralPurposeAllocator(.{}) = .init;
    const allocator = gpa.allocator();
    defer assert(gpa.deinit() == .ok);

    var args = try std.process.argsWithAllocator(allocator);
    defer args.deinit();

    const program_name = args.next() orelse unreachable;
    const input = parse_args(&args) catch |err| {
        std.debug.print("Error: {s}\n", .{@errorName(err)});
        usage(program_name);
        std.process.exit(1);
    };

    const dac = Dac.new(input.dac_bits);
    const rvalues, const dac_offset: f64 = switch (input.mode) {
        .sine => .{ try sine(allocator, &dac, input.freq_scalar), 0.5 },
        .sine_x_on_x => .{ try sine_x_on_x(allocator, &dac, input.freq_scalar), 0.2 },
        .amplitude_modulation => .{ try amplitude_modulation(allocator, &dac, input.freq_scalar), 0.5 },
    };
    defer allocator.free(rvalues);

    const dac_values = try dac.transform_waveform(allocator, rvalues, input.interpolate, dac_offset);
    defer allocator.free(dac_values);

    for (dac_values) |v| try stdout.print("{},\n", .{v});
}

fn amplitude_modulation(allocator: Allocator, dac: *const Dac, freq_scaler: f64) ![]const f64 {
    const INNER_WAVE_RADIANS: f64 = PI / 8.0;
    var values = F64ArrayList.init(allocator);
    defer values.deinit();

    const end_rad = 2.0 * PI;
    const step_rad = freq_scaler * (PI / 2.0) / dac.length;

    var angle_rad: f64 = 0.0;
    var end_inner_rad: f64 = 0.0;
    var angle_inner_rad: f64 = 0.0;
    while (angle_rad <= end_rad) : (angle_rad += step_rad) {
        const ampl = math.sin(angle_rad);
        angle_inner_rad = end_inner_rad;
        end_inner_rad += INNER_WAVE_RADIANS;

        if (end_inner_rad > 2.0 * PI) end_inner_rad = INNER_WAVE_RADIANS;
        if (angle_inner_rad > end_inner_rad) angle_inner_rad = 0.0;

        while (angle_inner_rad <= end_inner_rad) : (angle_inner_rad += step_rad) {
            try values.append((ampl * math.cos(angle_inner_rad)));
        }
    }
    return values.toOwnedSlice();
}

fn sine_x_on_x(allocator: Allocator, dac: *const Dac, freq_scaler: f64) ![]const f64 {
    var values = F64ArrayList.init(allocator);
    defer values.deinit();

    const end_rad = 2.0 * PI;
    const step_rad = freq_scaler * (PI / 2.0) / dac.length;

    var angle_rad: f64 = -end_rad;
    while (angle_rad <= end_rad) : (angle_rad += step_rad) {
        try values.append(math.sin(angle_rad) / angle_rad);
    }

    return values.toOwnedSlice();
}

fn sine(allocator: Allocator, dac: *const Dac, freq_scaler: f64) ![]const f64 {
    var values = F64ArrayList.init(allocator);
    defer values.deinit();

    const end_rad = 2.0 * PI;

    // Frequency scaling works by reaching the full cycle faster/slower, that is
    // increasing/decreasing the step value by that much amount. When freq_scaler > 1, we will be
    // incrementing the angle in larger steps so there will be less number of points in the output
    // vector (and full cycle will be reached with less number of points i.e faster). When
    // freq_scaler < 1, the opposite happens and there will be more number of points.
    const step_rad = freq_scaler * (PI / 2.0) / dac.length;

    var angle_rad: f64 = 0.0;
    while (angle_rad <= end_rad) : (angle_rad += step_rad) {
        try values.append(math.sin(angle_rad));
    }

    return values.toOwnedSlice();
}
