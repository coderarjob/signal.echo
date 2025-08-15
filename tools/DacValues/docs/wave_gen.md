##### 14-August-2025 19:44:42
# Generation of waves using DAC
##### Tags: electronics

The microcontoller is indexing into an array of values and writes them to DAC. The timing between
each writes is not controlled but can be taken as constant. Say the aray contains values that
represent one cycle of a sine wave. When these are written out, the frequency of the resulting
waveform will depend on two things:
1. `T` - The time spent by the microcontoller between writing two consecutive values to the DAC.
2. `N` - Number of values that represent the one cycle. If there are more number of points/values
   then it will take more time to dump the whole array to the DAC. Thus (frequency of the
   wave) `f ~ 1/(T * N)`.

The above relation of `f` & `N` means that a fast waveform requires less number of points but
also for the same reason will look bad because of the large quantization steps. This will be played
with depending on what waveform is generated.

All this happens in the microcontoller side and as you can see it just dumps data into the DAC and
does not control either the frequency or the look of it. Both depends on the how the values are
generated.

### Generation of DAC data - Sine wave

As stated above the DAC values given to the microcontoller represent one cycle of the required
waveform (one cycle all that is required because the waveform is repeating). If we want to increase
frequency, less points will represent that cycle, and a nicer looking waveform (but lower frequency)
will have more points for the same cycle.

Take the example of sine wave generation:

#### Algorithm

`sine(freq_scale, sample_count)` where 

* `freq_scale` - Number of generated points (samples) will be decreased to increase frequency by
  this amount
* `sample_count` - This many points will make one cycle of the repeating waveform, when `freq_scale`
  is 1.


```c
sine(freq_scale, sample_count) {
    // Time is incremented by this amount in each iteration.
    dt = freq_scale / sample_count
    
    // Since we stop iterating when time of 1.0 is reached, the number of samples that will be
    // in the output by then is 1/dt or `sample_count/freq_scale` number of points. That is as
    // `freq_scale` increases, N decreases and vice-versa.
    // Also note we have reached full cylcle (2 * PI radians) when time reached 1.0.
    N = 1/dt
    
    // Output list
    List(f64) output = empty;
    for (t = 0; t < 1.0; t += dt) {
        output.add(sin(2 * PI * t))
    }
    
    return output
}
```

#### Explanation

After `N = 1/dt` iterations, we will have `t = N * dt => t = dt/dt = 1`. In other words after `N`
iterations we have
* Number of cycles: 1
* Number of radians traversed: `2 * PI`.
* Number of sample points: `sample_count/freq_scale`.

So in the end, if `freq_scale` is 1, output represents one cycle and will have `sample_count` number
of points. If `freq_scale` is 2, output still will represent one cycle but now will have
`sample_count/2` number of points. Less number of points to equates to faster dump thus more
frequency.

##### Why not use `sin(2 * PI * freq_scale * t)` instead?

Lets do the same calculation as above. Since `freq_scale` now moved to the sine function, `dt`
becomes `dt = 1.0 / sample_count`. After `N = 1/dt` iterations, we will have `t = N * dt => t =
dt/dt = 1`. This remains the same, but the outcome is different. So  after `N` iterations we have
* Number of cycles: `freq_scale`. If it is 1, then 1 cycle, if its 2 then 2 cycles and so on.
* Number of radians traversed: `2 * PI * freq_scale`.
* Number of sample points: `sample_count`

So in the end, if `freq_scale` is 1, like before output represents one cycle and will have
`sample_count` number of points. If however `freq_scale` is 2, output will instead represent 2
cycles but will still have `sample_count` number of points. Same number of points representing more
number of cycles means less number of points per cycle and thus like before this equates to faster
dump thus more frequency.

So now that we know the difference between the two ways, the former method is chosen for generating
sine wave, since it always output one single cycle, which is what we want.

### Generation of DAC data - AM wave

Much of the things remain the same and I will not mention them again here.

#### Algorithm

`am(freq_scale, sample_count)` where 

* `freq_scale` - Number of complete cycles of the carrier wave in 0.5 cycle of the signal wave. This
  determines the frequency of the carrier wave and thus the density in the AM wave.
* `sample_count` - This many points will make 0.5 cycle of the repeating waveform. Unlike the sine
  wave case here we will always produce this many samples irrespective of the `freq_scale` value.

```c
am(freq_scale, sample_count) {
    // Time is incremented by this amount in each iteration.
    dt = 1.0 / sample_count
    
    // Since we stop iterating when time of 1.0 is reached, the number of samples that will be
    // in the output by then is 1/dt or `sample_count` number of points.
    N = 1/dt
    
    // Output list
    List(f64) output = empty;
    for (t = 0; t < 1.0; t += dt) {
        output.add(sin(2 * PI * t * 0.5) * cos(2 * PI * time * freq_scale * BASE_FREQ)
    }
    
    return output
}
```

#### Expectations

After `N = 1/dt` iterations, we will have `t = N * dt => t = dt/dt = 1`. In other words after `N`
iterations we have
* Number of cycles (carrier wave): `freq_scale * BASE_FREQ`
* Number of cycles (signal wave): 0.5
* Number of radians traversed (carrier wave): `2 * PI * freq_scale * BASE_FREQ`
* Number of radians traversed (signal wave): `2 * PI * 0.5`
* Number of sample points: `sample_count`

Note that this is exactly what other (alternate) method described in the Sine wave generation
section.

-------------------------


