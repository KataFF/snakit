# z523087 - Makefile to autorun demo
SOURCE_CLIENT=client.c
OUTPUT_CLIENT=client.elf
SOURCE_SERVER=server.c
OUTPUT_SERVER=server.elf
ADDR=localhost
PORT=12345

# Default target
default: bsv bcl demo;

# Build server
bsv:
	gcc -o $(OUTPUT_SERVER) $(SOURCE_SERVER)

# Build client
bcl:
	gcc -o $(OUTPUT_CLIENT) $(SOURCE_CLIENT) -lncurses -lz

# Run Server and then client
demo:
	echo "Running client & server demo."
	kitty ./$(OUTPUT_SERVER) $(ADDR) $(PORT) &
	kitty ./$(OUTPUT_CLIENT) $(ADDR) $(PORT) &

