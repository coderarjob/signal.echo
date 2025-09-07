## Version 1.0 release notes

### Hardware features
See ./schematic/scopetester_schematic.pdf for details

### Sofware features

| Mode          | Description                                                     | Output pin     |
|---------------|-----------------------------------------------------------------|----------------|
| USART         | Decode should read 'HelloX' where X is between 'A' and 'Z'.     | DIGI_OUT_1     |
|               | Spec: 10kbps, No Parity, 1 stop bit, 8 bits                     |                |
| RUNT PULSE    | Square wave with intermitent positive and negative runt pulses. | ANG_OUT_0      |
|               | Spec: 3.8 KHz square wave with 1 runt pulse every 1000 pulses.  |                |
| TWO PULSE     | Two time coorolated square waves in separate chanels.           | DIGI_OUT_0 &   |
|               | Spec: 3.9 ms pulse of 76.9 KHz sq wave, every 34 ms             | DIGI_OUT_1     |
| SAWTOOTH WAVE | Sawtooth wave of a fixed frequency.                             | ANG_OUT_0      |
|               | Spec: 48 Khz output frequency.                                  |                |
| SAWTOOTH WAVE | Triangle wave of a fixed frequency.                             | ANG_OUT_0      |
|               | Spec: 24.5 Khz output frequency.                                |                |
| I2C           | Decode address to 0x5, data to should read 'Hello' repeatedly.  | SCL=DIGI_OUT_0 |
|               | Spec: R/W bit is present.                                       | SDA=DIGI_OUT_1 |
| SINE WAVE     | Sine wave of a fixed frequency.                                 | ANG_OUT_0      |
|               | Spec: 4 Khz output frequency.                                   |                |
| AM WAVE       | Amplitude modulation wave of a fixed frequency.                 | ANG_OUT_0      |
|               | Spec: Signal of 102 Hz, Carrier of 40 KHz  output frequency.    |                |
