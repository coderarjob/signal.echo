BUILD ?= fw
BUILD_DIR ?= out

INCLUDE_ROOT_DIR := include
OBJ_DIR := $(BUILD_DIR)/obj

all:

ifeq ($(BUILD), fw)
SRC_ROOT_DIR := src

include build/fw/config.mk

ifneq ($(COMPILER), gcc)
$(error Only GCC compiler is supported for AVR)
endif

include build/fw/toolchain_avr_gcc.mk
include build/gcc_rules.mk

include $(SRC_ROOT_DIR)/fw/build.mk

$(call compile_target,firmware)
$(call link_target,firmware)
$(call link_target_firmware_bin,firmware)

all: $(firmware_BIN)
endif

clean:
	rm -rf $(BUILD_DIR)

-include $(shell [ -e $(BUILD_DIR) ] && find "$(BUILD_DIR)" -nowarn -type f -iname "*.d")

.PHONY: clean all
