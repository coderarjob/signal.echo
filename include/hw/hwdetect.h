#pragma once

// Here is list of all the supported values for the ARCH macro. Without these definitions, ifdef
// guards using ARCH will fail.
#define AVR 1

#if defined(ARCH)
    #if ARCH != AVR
        #error "ARCH is invalid"
    #endif
#else
    #error "ARCH is not set"
#endif // defined (ARCH)
