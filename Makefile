build: 
	clang *.c -std=c11 `sdl2-config --libs --cflags` -lSDL2_image -o chip-shmoneh
run:
	./chip-shmoneh
