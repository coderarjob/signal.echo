## DacValues

This tool generates numbers to recreate waveforms using our DAC hardware. These numbers are used
in the firmware code to generate various waveforms.

### Prerequisites

1. Zig compiler 0.15.1

There is no particular reason to use Zig language, other than my liking for it.

### Building and running

`zig build` by default puts the binary within the `zig-out/bin` directory.

```bash
$ zig build
$ ./zig-out/bin/dv # Displays help and uage information
```

It is also possible to run the binary using `zig build` as shown below.

```bash
$ zig build run -- <args> # Refer to usage for <args>
```

### Unittests

```bash
$ zig build test
```

# Feedback

Open a GitHub issue or drop a email at arjobmukherjee@gmail.com. I would love to hear your
suggestions and feedbacks.
