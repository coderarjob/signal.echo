SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

# ==================================================================
utils_test_SRC := $(SRC_DIR)utils_test.c
utils_test_CFLAGS := $(cc_flags)
utils_test_LDFLAGS := $(ld_flags)
utils_test_DEP :=

$(call compile_target,utils_test)
$(call link_target,utils_test)

# ==================================================================
feature_test_SRC := $(SRC_DIR)feature_test.c \
					$(SRC_ROOT_DIR)/fw/main.c

feature_test_CFLAGS := $(cc_flags)
feature_test_LDFLAGS := $(ld_flags)
feature_test_DEP :=

$(call compile_target,feature_test)
$(call link_target,feature_test)

# ==================================================================

ALL := $(utils_test_ELF) \
	   $(feature_test_ELF)
