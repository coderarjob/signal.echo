const std = @import("std");

pub fn build(b: *std.Build) !void {

    const exe = b.addExecutable(.{
        .name = "dv",
        .root_module = b.createModule(.{
            .root_source_file =  b.path("src/main.zig"),
            .target = b.graph.host,
            .optimize = b.standardOptimizeOption(.{})
        }),
    });
    b.installArtifact(exe);
    
    const run_exe = b.addRunArtifact(exe);
    if (b.args) |args| run_exe.addArgs(args);
    b.step("run", "Runs the application").dependOn(&run_exe.step);

    const test_exe = b.addTest(.{
        .root_module = b.createModule(.{
            .root_source_file = b.path("src/testmain.zig"),
            .target = b.graph.host
        }),
    });
    const run_test = b.addRunArtifact(test_exe);
    run_test.skip_foreign_checks = true;
    b.step("test", "Runs tests").dependOn(&run_test.step);
}
