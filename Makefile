CC=clang
CSTD=-std=c11
SOURCE=config.c debug.c events.c graphics.c hardware.c main.c processor.c stack.c display.c
OUTPUT=chip-shmoneh
DEBUG=-g3 -O0
TEST=roms/2-ibm-logo.ch8

# Should be the output of `sdl2-config --cflags --libs` 
SDL=-I/usr/include/SDL2 -D_REENTRANT -L/usr/lib -lSDL2

SDLIMG=-lSDL2_image 

build: 
	$(CC) $(SOURCE) $(CSTD) $(SDL) $(SDLIMG) -o $(OUTPUT)
debug: 
	$(CC) $(SOURCE) $(DEBUG) $(CSTD) $(SDL) $(SDLIMG) -o $(OUTPUT)
run:
	./$(OUTPUT) $(TEST)
clean:
	rm -rf $(OUTPUT)