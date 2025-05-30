CC := avr-gcc
LD := avr-ld
OBJDUMP := avr-objdump
OBJCOPY := avr-objcopy
AR := avr-ar

PROGRAMMER := avrdude

ld_flags := -mmcu=${machine}           \
			-L $(BUILD_DIR)

cc_flags := -mmcu=${machine}           \
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
