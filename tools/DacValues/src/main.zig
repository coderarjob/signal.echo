const std = @import("std");
const Dac = @import("Dac.zig");
const Gen = @import("waves.zig");
const Waves = Gen.Waves;

const Allocator = std.mem.Allocator;
const stdout = std.io.getStdOut().writer();

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
            const value = args.next() orelse {
                std.debug.print("Frequency value was not provided.\n", .{});
                return error.Failed;
            };
            freq_scalar = std.fmt.parseFloat(f64, value) catch |e|{
                std.debug.print("Invalid floating point value: {s}.\n", .{value});
                return e;
            };
        } else if (std.mem.eql(u8, arg, "--bits")) {
            const value = args.next() orelse {
                std.debug.print("Dac bits was not provided.\n", .{});
                return error.Failed;
            };
            dac_bits = std.fmt.parseInt(u32, value, 10) catch |e|{
                std.debug.print("Invalid numeric value: {s}.\n", .{value});
                return e;
            };
        } else {
            mode = std.meta.stringToEnum(Waves, arg) orelse {
                std.debug.print("Invalid mode: {s}.\n", .{arg});
                return error.Failed;
            };
        }
    }

    return .{
        .mode = mode orelse {
            std.debug.print("Wave value was not provided\n", .{});
            return error.Failed;
        },
        .interpolate = interpolate,
        .freq_scalar = freq_scalar,
        .dac_bits = dac_bits orelse {
            std.debug.print("Dac bits was not provided\n", .{});
            return error.Failed;
        }};
}

fn usage(program_name: []const u8) void {
    const usage_str = "[--interpolate] [--freq=<freq>]";
    std.debug.print("Usage: {s}\n{s} ", .{program_name, usage_str});
    inline for (std.meta.tags(Waves), 0..) |t, i| {
        const c = if (i == 0) '[' else '|';
        std.debug.print("{c}{s}", .{ c, @tagName(t) });
    }
    std.debug.print("]\n", .{});
}

pub fn main() !void {
    var gpa: std.heap.GeneralPurposeAllocator(.{}) = .init;
    const allocator = gpa.allocator();
    defer std.debug.assert(gpa.deinit() == .ok);

    var args = try std.process.argsWithAllocator(allocator);
    defer args.deinit();

    const program_name = args.next() orelse unreachable;
    const input = parse_args(&args) catch {
        usage(program_name);
        std.process.exit(1);
    };

    const dac = Dac.new(input.dac_bits);
    const gen = Gen.init(allocator, dac);
    const rvalues, const dac_offset: f64 = switch (input.mode) {
        .sine =>           .{ try gen.sine(input.freq_scalar), 0.5 },
        .sine_x_on_x =>    .{ try gen.sine_x_on_x(input.freq_scalar), 0.2 },
        .amp_modulation => .{ try gen.amp_modulation(input.freq_scalar), 0.5 },
    };
    defer gen.deinit(rvalues);

    const dac_values = try dac.transform_waveform(allocator, rvalues, input.interpolate, dac_offset);
    defer allocator.free(dac_values);

    for (dac_values) |v| try stdout.print("{},\n", .{v});
}
