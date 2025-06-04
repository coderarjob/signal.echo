CC := gcc
LD := ld
OBJDUMP := objdump
OBJCOPY := objcopy
AR := ar

cc_definitions :=

ld_flags :=

cc_flags := $(cc_definitions)          \
		    -Wall                      \
		    -Wextra                    \
		    -std=c99                   \
		    -I $(INCLUDE_ROOT_DIR)     \
		    -MMD                       \
		    -MP

ifdef DEBUG
	cc_flags += -g
endif
