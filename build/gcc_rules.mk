# Implicit rules
$(OBJ_DIR)/%.o: $(SRC_ROOT_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -DF_CPU=$(clock) $< -o $@

$(BUILD_DIR)/%.elf:
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.hex:
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O ihex $^ $@
	$(OBJDUMP) -dSl $^ > $(@:%.hex=%.lst)

# Definitions to setup target variables and prerequisits
define compile_target
	;# Create derived variables for each target (these are not 'target specific variables')
	$(eval $1_OBJ := $($1_SRC:$(SRC_ROOT_DIR)/%.c=$(OBJ_DIR)/%.o))
	;# Create target specific variables
	$(foreach obj, $($1_OBJ), $(eval $(obj): CFLAGS := $($1_CFLAGS)))
endef

define link_target
	;# Create derived variables for each target (these are not 'target specific variables')
	$(eval $1_ELF := $(BUILD_DIR)/$1.elf)

	;# Create target specific variables
	$(eval $($1_ELF): LDFLAGS := $($1_LDFLAGS))

	;# Specify explicitly the prerequisits for each target's elf & hex files (which are its obj files &
	;# .a files of its dependencies)
	$(eval $($1_ELF): $($1_OBJ) $($($1_DEP)_OBJ))
endef

define link_target_firmware_bin
	;# Create derived variables for each target (these are not 'target specific variables')
	$(eval $1_BIN := $(BUILD_DIR)/$1.hex)
	;# Specify explicitly the prerequisits for the main target's hex file
	$(eval $($1_BIN): $($1_ELF))
endef
