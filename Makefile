BUILD ?= fw
BUILD_DIR ?= out

INCLUDE_ROOT_DIR := include
OBJ_DIR := $(BUILD_DIR)/obj
SRC_ROOT_DIR := src

ifeq ($(and $(OBJ_DIR), $(SRC_ROOT_DIR), $(BUILD_DIR), $(INCLUDE_ROOT_DIR)),)
$(error Invalid build path setup. Required variables are not set)
endif
# ============================================================================================

all:

# ============================================================================================
include build/gcc_rules.mk
include build/fw/config.mk

ifeq ($(and $(clock), $(machine), $(COMPILER), $(ARCH)),)
$(error Invalid build setup. Required variables are not set)
endif

# ============================================================================================
ifeq ($(BUILD), fw)
# ============================================================================================

include build/fw/toolchain_$(ARCH)_gcc.mk

ifeq ($(and $(CC), $(OBJCOPY), $(OBJDUMP), $(PROGRAMMER), $(AR), $(LD)),)
$(error Invalid toolchain setup. Required variables are not set)
endif

include build/fw/$(PROGRAMMER).mk
include $(SRC_ROOT_DIR)/fw/build.mk

# ============================================================================================
else ifeq ($(BUILD), ut)
# ============================================================================================

include build/ut/toolchain_gcc.mk

ifeq ($(and $(CC), $(OBJCOPY), $(OBJDUMP), $(AR), $(LD)),)
$(error Invalid toolchain setup. Required variables are not set)
endif

include $(SRC_ROOT_DIR)/unittests/build.mk

run: $(ALL)
	@for f in $^; do                               \
    	echo "=================================="; \
    	echo "Test: $$f";                          \
    	echo "----------------------------------"; \
		$$f;                                       \
	done

.PHONY: run

endif
# ============================================================================================

all: $(ALL)

clean:
	rm -rf $(BUILD_DIR)

-include $(shell [ -e $(BUILD_DIR) ] && find "$(BUILD_DIR)" -nowarn -type f -iname "*.d")

.PHONY: clean all
