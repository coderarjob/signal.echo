SRC_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

example_test_SRC := $(SRC_DIR)example_test.c
example_test_CFLAGS := $(cc_flags)
example_test_LDFLAGS := $(ld_flags)
example_test_DEP := 

$(call compile_target,example_test)
$(call link_target,example_test)

ALL := $(example_test_ELF)
