const std = @import("std");
const mem = std.mem;
const math = std.math;

bits: u32,
max_value: f64,
length: f64,
resolution_volts: f64,

const Self = @This();

pub fn new(bits: u32) Self {
    const length = @as(f64, @floatFromInt(std.math.pow(u32, 2, bits)));
    return .{
        .bits = bits,
        .max_value = length - 1.0,
        .length = length,
        .resolution_volts = 1.0 / length,
    };
}

pub fn transform_waveform(self: *const Self, allocator: mem.Allocator, waveform: []const f64, start_offset: f64) ![]const u32 {
    var ret = std.ArrayList(u32).init(allocator);
    defer ret.deinit();

    const offset_dac_value = self.length * start_offset;

    for (waveform) |item| {
        const out_dac_value: u32 = @intFromFloat(math.floor(offset_dac_value + item * (self.max_value - offset_dac_value)));
        try ret.append(out_dac_value);
    }
    return ret.toOwnedSlice();
}
