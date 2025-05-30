BUILD ?= fw
BUILD_DIR ?= out

INCLUDE_ROOT_DIR := include
OBJ_DIR := $(BUILD_DIR)/obj

all:

ifeq ($(BUILD), fw)
SRC_ROOT_DIR := src

ifeq ($(and $(OBJ_DIR), $(SRC_ROOT_DIR), $(BUILD_DIR), $(INCLUDE_ROOT_DIR)),)
$(error Invalid build path setup. Required variables are not set)
endif

include build/fw/config.mk

ifeq ($(and $(clock), $(machine), $(COMPILER), $(ARCH)),)
$(error Invalid build setup. Required variables are not set)
endif

include build/fw/toolchain_avr_gcc.mk
include build/gcc_rules.mk

include $(SRC_ROOT_DIR)/fw/build.mk

ifeq ($(and $(CC), $(OBJCOPY), $(OBJDUMP), $(PROGRAMMER), $(AR), $(LD)),)
$(error Invalid toolchain setup. Required variables are not set)
endif

$(call compile_target,firmware)
$(call link_target,firmware)
$(call link_target_firmware_bin,firmware)

all: $(firmware_BIN)

include build/fw/$(PROGRAMMER).mk
endif

clean:
	rm -rf $(BUILD_DIR)

-include $(shell [ -e $(BUILD_DIR) ] && find "$(BUILD_DIR)" -nowarn -type f -iname "*.d")

.PHONY: clean all
