CC := avr-gcc
LD := avr-ld
OBJDUMP := avr-objdump
OBJCOPY := avr-objcopy
AR := avr-ar

PROGRAMMER := avrdude
MPU_ARCH   := AVR

cc_definitions := -DF_CPU=$(clock)        \
				  -DMPU_ARCH=$(MPU_ARCH)  \
				  -DHW_VER=$(HW_VER)

ifeq ($(DEBUG), 1)
	cc_definitions += -DDEBUG
endif

ld_flags := -mmcu=${machine}           \
			-L $(BUILD_DIR)

cc_flags := $(cc_definitions)               \
			-mmcu=${machine}                \
		    -mint8                          \
		    -fpack-struct                   \
		    -funsigned-char                 \
		    -funsigned-bitfields            \
		    -fshort-enums                   \
		    -Os                             \
		    -Wall                           \
		    -Wextra                         \
		    -std=c99                        \
		    -I $(INCLUDE_ROOT_DIR)          \
		    -I $(INCLUDE_ROOT_DIR)/arch/avr \
		    -MMD                            \
		    -MP


ifeq ($(DEBUG), 1)
	cc_flags += -g
endif
