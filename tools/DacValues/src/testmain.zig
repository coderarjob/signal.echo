const std = @import("std");
const expect = std.testing.expect;
const expectApproxEqAbs = std.testing.expectApproxEqAbs;
const Dac = @import("Dac.zig");

test "dac creation" {
    const dac = Dac.new(6);
    try expect(dac.bits == 6);
    try expectApproxEqAbs(63.999, dac.max_value, 1e-3);
    try expect(dac.length == 64);
    try expectApproxEqAbs(15.635e-3, dac.resolution_volts, 1e-3);
}

test "transform waveform" {
    const allocator = std.testing.allocator;
    const dac = Dac.new(6);

    const data_in = [_]f64{ 0.0, 0.5, 1.0 };
    const data_out = try dac.transform_waveform(allocator, &data_in, false, 0.5);
    defer allocator.free(data_out);

    try expect(data_out.len == data_in.len);
    try expect(data_out[0] == 32);
    try expect(data_out[1] == 47);
    try expect(data_out[2] == 63);
}
