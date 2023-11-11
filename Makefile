build: 
	clang *.c -std=c11 `sdl2-config --libs --cflags` -lSDL2_image -o chip-shmoneh
debug: 
	clang *.c -g3 -O0 -std=c11 `sdl2-config --libs --cflags` -lSDL2_image -o chip-shmoneh
run:
	./chip-shmoneh ../chip8-test-suite/bin/2-ibm-logo.ch8
