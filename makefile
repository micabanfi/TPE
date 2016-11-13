COMPILER=gcc
OUTPUT_FILE=TPE
FILES=buttonsAndScissorsBack.c buttonsAndScissorsBack.h buttonsAndScissorsFront.c

ALL:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES) -lm
wall:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES) -Wall -lm
clean:
	rm $(OUTPUT_FILE)
