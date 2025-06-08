CC := avr-gcc
LD := avr-ld
OBJDUMP := avr-objdump
OBJCOPY := avr-objcopy
AR := avr-ar

PROGRAMMER := avrdude
MPU_ARCH   := AVR

cc_definitions := -DF_CPU=$(clock)        \
				  -DMPU_ARCH=$(MPU_ARCH)

ld_flags := -mmcu=${machine}           \
			-L $(BUILD_DIR)

cc_flags := $(cc_definitions)          \
			-mmcu=${machine}           \
		    -mint8                     \
		    -fpack-struct              \
		    -funsigned-char            \
		    -funsigned-bitfields       \
		    -fshort-enums              \
		    -Os                        \
		    -Wall                      \
		    -Wextra                    \
		    -std=c99                   \
		    -I $(INCLUDE_ROOT_DIR)     \
		    -MMD                       \
		    -MP


ifdef DEBUG
	cc_flags += -g
endif
