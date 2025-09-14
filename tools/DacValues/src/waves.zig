const std = @import("std");
const Allocator = std.mem.Allocator;
const Dac = @import("Dac.zig");
const math = std.math;

const PI = math.pi;
const F64ArrayList = std.array_list.Managed(f64);

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

pub fn amp_modulation(self: Self, freq_scaler: f64, sample_count: u32) ![]const f64 {
    var values = F64ArrayList.init(self.allocator);
    defer values.deinit();

    const step_time = 1.0 / @as(f64, @floatFromInt(sample_count));

    // 50 is chosen just as some base. The base value will make freq_scaler value behave more how it
    // behaves for the sine wave generation, i.e it simply scales the frequency.
    const carrier_freq = 50.0 * freq_scaler;

    var time: f64 = 0.0;
    while (time <= 1.0) : (time += step_time) {
        const v = (1 + math.sin(2.0 * PI * time - PI / 2.0)) * 0.5 * math.cos(2.0 * PI * time * carrier_freq);
        try values.append(v);
    }
    return values.toOwnedSlice();
}

pub fn sine_x_on_x(self: Self, freq_scaler: f64, sample_count: u32) ![]const f64 {
    var values = F64ArrayList.init(self.allocator);
    defer values.deinit();

    const time_step = freq_scaler / @as(f64, @floatFromInt(sample_count));

    var time: f64 = -5.0;
    while (time <= 5.0) : (time += time_step) {
        const x = 2.0 * PI * time;
        try values.append(math.sin(x) / x);
    }

    return values.toOwnedSlice();
}

pub fn sine(self: Self, freq_scaler: f64, sample_count: u32) ![]const f64 {
    var values = F64ArrayList.init(self.allocator);
    defer values.deinit();

    // Frequency scaling works by reaching the full cycle faster/slower in more/less number of
    // samples.
    const time_step = freq_scaler / @as(f64, @floatFromInt(sample_count));

    var time: f64 = 0.0;
    while (time <= 1.0) : (time += time_step) {
        try values.append(math.sin(2.0 * PI * time));
    }

    return values.toOwnedSlice();
}

pub fn deinit(self: Self, values: []const f64) void {
    self.allocator.free(values);
}
