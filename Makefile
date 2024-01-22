# z523087 - Makefile for client
SOURCE=client.c
OUTPUT=client.elf

# Default target
default: bcl;

# Build client
bcl:
	gcc -o $(OUTPUT) $(SOURCE) -lncurses -lz
	./$(OUTPUT)