SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifeq ($(ARCH), avr)
firmware_SRC := $(SRC_DIR)arch/avr/main.c \
				$(SRC_DIR)arch/avr/usart.c
firmware_CFLAGS := $(cc_flags)
firmware_LDFLAGS := $(ld_flags)
firmware_DEP := avrlib
endif
