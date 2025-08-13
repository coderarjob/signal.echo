<p align="center">
    <img src="/docs/images/logo.png"/>
    <br/>
</p>

## About

This is a hardware project based on Atmega8A microcontroller. This project came about from a
personal need for a demo board to test my new oscilloscope. I plan to create a complete PCB
along with firmware in this repo.

### Screenshots

##### 1. Serial RS232 (TTL Level) decoding test

![rs232](docs/images/usart.png)

##### 2. Serial I2C decoding test

![rs232](docs/images/i2c.png)

##### 3. Positive & negative Runt detection pulse

![Positive runt pulse](docs/images/positive_runt.png)

![Negative runt pulse](docs/images/negative_runt.png)

##### 4. Burst mode pulses

![Negative runt pulse](docs/images/burst_pulses.png)

##### 5. Sine wave

![Sine wave](docs/images/sine_wave.png)
![Sine wave](docs/images/sine_wave_freq_dist.png)
![Sine wave](docs/images/sine_wave_fft.png)

##### 6. Triangle wave

![Triangle wave](docs/images/triangle_wave.png)
![Triangle wave](docs/images/triangle_wave_freq_dist.png)
![Triangle wave](docs/images/triangle_wave_fft.png)

##### 7. Sawtooth wave

![Sawtooth wave](docs/images/sawtooth_wave.png)
![Sawtooth wave](docs/images/sawtooth_wave_freq_dist.png)
![Sawtooth wave](docs/images/sawtooth_wave_fft.png)

### Goals

- [X] Firmware: RS232 sample output (positive)
- [X] Firmware: I2C sample output
- [X] Firmware: Runt pulse (+ve & -ve runt pulses)
- [X] Firmware: Sine wave pattern
- [X] Firmware: Amplitude Modulation wave pattern
- [X] Firmware: Triangle wave pattern
- [X] Firmware: Sawtooth wave pattern
- [X] Firmware: Burst data in two lines
- [X] Firmware: Separate arch independent codes
- [X] Unittests: Add unittests for utils
- [X] Unittests: Add unittests for existing tests

## Building prerequisites

1. Requires Linux environment for building.
2. GNU Make
3. avr-gcc
4. avr-libc

### Firmware

```
BUILD_DIR=out make
```

Firmware is the `./out/firmware.hex` file. To program micro with avrdude, we can do `make program`.

### Unittests

We can build every unittests and run them using the `run` target.

```
BUILD=ut BUILD_DIR=out/ut make run
```

### Tools

Some tools which are used exclusively in this project are/will be put into the `tools` folder. Each
may have different prerequisites and build procedures. For information see `Readme.md` of each
tool.

# Feedback

Open a GitHub issue or drop a email at arjobmukherjee@gmail.com. I would love to hear your
suggestions and feedbacks.
