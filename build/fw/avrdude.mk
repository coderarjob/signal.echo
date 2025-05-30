program: $(firmware_BIN)
	avrdude -c usbasp -p m8a -U flash:w:"$^":i

reset:
	avrdude -c usbasp -p m8a -U signature:r:-:h

.PHONY: program reset
