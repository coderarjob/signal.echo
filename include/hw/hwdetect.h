#pragma once

// Here is list of all the supported values for the MPU_ARCH macro. Without these definitions, ifdef
// guards using MPU_ARCH will fail.
#define AVR 1

#if defined(MPU_ARCH)
    #if MPU_ARCH == AVR
    #else
        #error "MPU_ARCH is invalid"
    #endif
#else
    #error "MPU_ARCH is not set"
#endif // defined (MPU_ARCH)
