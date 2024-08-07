# chip-shmoneh
An emulator (or interpreter) for the [CHIP-8](https://en.wikipedia.org/wiki/CHIP-8) virtual machine.

![Title Image](https://ysfm.co.il/chip8/chip3.gif) ![Title Image](https://ysfm.co.il/chip8/chip2.gif)
![Title Image](https://ysfm.co.il/chip8/chip1.gif) ![Title Image](https://ysfm.co.il/chip8/chip4.gif)

## Features
* High compatibility with CHIP-8 roms from all across the internet.
* Enable or disable quirks via a configuration file.
* Reduce graphical flickering using a double buffer method.
* Configurable pixel grid.
* Configurable CPU speed. 
* Optional color mode.
* Save states and rewind.
* (Coming soon) Audio.

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

### Keyboard commands
* Spacebar (hold) - Run CPU in unlimited speed.
* F1 - Quick save.
* F2 - Quick load.
* F3 - Pause emulation toggle.
* F4 (hold) - Rewind. Make sure to enable it in the configuration first.

## Dependencies
* [SDL2](https://www.libsdl.org/)

