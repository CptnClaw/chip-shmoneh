# chip-shmoneh
An emulator (or interpreter) for the [CHIP-8](https://en.wikipedia.org/wiki/CHIP-8) virtual machine.

![Title Image](https://ysfm.co.il/c1.gif)

## Features
* High compatibility with CHIP-8 roms from all across the internet.
* Enable or disable quirks via a configuration file.
* Reduce graphical flickering using a double buffer method.
* Configurable pixel grid.
* Configurable CPU speed. Hold spacebar to run unrestricted. FPS is printed to standard output.
* (Coming soon) Audio.
* (Coming soon) Save states and rewind.


## Getting started
### Building
Make sure you have a working C development environment. This project uses `clang` for compilation. 
The only dependency is `SDL2`.
Build the project by
```shell
make
```
This will produce an executable file called `chip-shmoneh`.

### Running
Usage is
```shell
./chip-shmoneh <rom file>
```
To configure, edit `chip-shmoneh.conf`. It is a simple space-delimited text file. See comments inside for more information.

## Dependencies
* SDL2

