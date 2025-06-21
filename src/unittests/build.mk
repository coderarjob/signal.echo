SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

# ==================================================================
utils_test_SRC := $(SRC_DIR)utils_test.c
utils_test_CFLAGS := $(cc_flags)
utils_test_LDFLAGS := $(ld_flags)
utils_test_DEP :=

$(call compile_target,utils_test)
$(call link_target,utils_test)

# ==================================================================
$(ARCH)_hal_test_SRC := $(SRC_DIR)arch/$(ARCH)/hal_test.c

$(ARCH)_hal_test_CFLAGS := $(cc_flags)
$(ARCH)_hal_test_LDFLAGS := $(ld_flags)
$(ARCH)_hal_test_DEP := -DHAL_UNITTEST

$(call compile_target,$(ARCH)_hal_test)
$(call link_target,$(ARCH)_hal_test)

# ==================================================================

ALL := $(utils_test_ELF) \
	   $($(ARCH)_hal_test_ELF)
