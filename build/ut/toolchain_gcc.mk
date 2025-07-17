CC := gcc
LD := ld
OBJDUMP := objdump
OBJCOPY := objcopy
AR := ar

# Convert ARCH to upper case.
MPU_ARCH := $(shell echo $(ARCH)|tr 'a-z' 'A-Z')

cc_definitions := -DF_CPU=$(clock)    \
				  -DARCH=$(MPU_ARCH)  \
				  -DHW_VER=$(HW_VER)  \
				  -DUNITTESTS

ld_flags :=

cc_flags := $(cc_definitions)           \
		    -Wall                       \
		    -Wextra                     \
		    -std=c99                    \
		    -I $(INCLUDE_ROOT_DIR)      \
		    -I $(INCLUDE_ROOT_DIR)/mock \
		    -MMD                        \
		    -MP

ifeq ($(DEBUG), 1)
	cc_flags += -g
endif
