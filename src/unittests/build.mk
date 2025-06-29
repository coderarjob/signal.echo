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

feature_test_SRC := $(SRC_DIR)feature_test.c   \
					$(SRC_ROOT_DIR)/fw/tests.c

feature_test_CFLAGS := $(cc_flags)
feature_test_LDFLAGS := $(ld_flags)
feature_test_DEP :=

$(call compile_target,feature_test)
$(call link_target,feature_test)

# ==================================================================

fwmain_test_SRC := $(SRC_DIR)fwmain_test.c  \
				   $(SRC_ROOT_DIR)/fw/main.c

fwmain_test_CFLAGS := $(cc_flags)
fwmain_test_LDFLAGS := $(ld_flags)
fwmain_test_DEP :=

$(call compile_target,fwmain_test)
$(call link_target,fwmain_test)

# ==================================================================

modes_test_SRC := $(SRC_DIR)modes_test.c    \
				  $(SRC_ROOT_DIR)/fw/mode.c

modes_test_CFLAGS := $(cc_flags)
modes_test_LDFLAGS := $(ld_flags)
modes_test_DEP :=

$(call compile_target,modes_test)
$(call link_target,modes_test)

# ==================================================================

ALL := $(utils_test_ELF)       \
	   $($(ARCH)_hal_test_ELF) \
	   $(feature_test_ELF)     \
	   $(fwmain_test_ELF)      \
	   $(modes_test_ELF)
