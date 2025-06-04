SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

ifeq ($(ARCH), avr)
firmware_SRC := $(SRC_DIR)arch/avr/main.c \
				$(SRC_DIR)arch/avr/usart.c
endif

firmware_CFLAGS := $(cc_flags)
firmware_LDFLAGS := $(ld_flags)
firmware_DEP :=

$(call compile_target,firmware)
$(call link_target,firmware)
$(call link_target_firmware_bin,firmware)

ALL := $(firmware_BIN)
