program: $(firmware_BIN)
	avrdude -c usbasp -p m8a -U flash:w:"$^":i

program_fuses:
	avrdude -c usbasp -p m8a -U lfuse:w:0xff:m -U hfuse:w:0xc9:m

reset:
	avrdude -c usbasp -p m8a -U signature:r:-:h

.PHONY: program reset program_fuses
