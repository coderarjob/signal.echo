const std = @import("std");
const Allocator = std.mem.Allocator;
const Dac = @import("Dac.zig");
const math = std.math;

const PI = math.pi;
const F64ArrayList = std.ArrayList(f64);

allocator: Allocator,
dac: Dac,

const Self = @This();

pub const Waves = enum {
    sine,
    amp_modulation,
    sine_x_on_x,
};


pub fn init(allocator: Allocator, dac: Dac) Self {
    return .{ .allocator = allocator, .dac = dac };
}

pub fn amp_modulation(self: Self, freq_scaler: f64) ![]const f64 {
    const INNER_WAVE_RADIANS: f64 = PI / 8.0;
    var values = F64ArrayList.init(self.allocator);
    defer values.deinit();

    const end_rad = 2.0 * PI;
    const step_rad = freq_scaler * (PI / 2.0) / self.dac.length;

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

pub fn sine_x_on_x(self: Self, freq_scaler: f64) ![]const f64 {
    var values = F64ArrayList.init(self.allocator);
    defer values.deinit();

    const end_rad = 2.0 * PI;
    const step_rad = freq_scaler * (PI / 2.0) / self.dac.length;

    var angle_rad: f64 = -end_rad;
    while (angle_rad <= end_rad) : (angle_rad += step_rad) {
        try values.append(math.sin(angle_rad) / angle_rad);
    }

    return values.toOwnedSlice();
}

pub fn sine(self: Self, freq_scaler: f64) ![]const f64 {
    var values = F64ArrayList.init(self.allocator);
    defer values.deinit();

    const end_rad = 2.0 * PI;

    // Frequency scaling works by reaching the full cycle faster/slower, that is
    // increasing/decreasing the step value by that much amount. When freq_scaler > 1, we will be
    // incrementing the angle in larger steps so there will be less number of points in the output
    // vector (and full cycle will be reached with less number of points i.e faster). When
    // freq_scaler < 1, the opposite happens and there will be more number of points.
    const step_rad = freq_scaler * (PI / 2.0) / self.dac.length;

    var angle_rad: f64 = 0.0;
    while (angle_rad <= end_rad) : (angle_rad += step_rad) {
        try values.append(math.sin(angle_rad));
    }

    return values.toOwnedSlice();
}

pub fn deinit(self: Self, values: []const f64) void {
    self.allocator.free(values);
}
