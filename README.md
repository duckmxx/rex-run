# rex
Chrome dino clone made using C++ and raylib. 

## Controls
Space to start, jump, and reset.


# Build Instructions

## Requirements

- C++23 compatible compiler
- Raylib
- Make

## Linux

Install Raylib and build tools using your package manager.

### Arch-based
```bash
sudo pacman -S raylib make
```

Build:

```bash
make
```

Run:

```bash
./main
```

### Ubuntu/Debian

```bash
sudo apt install build-essential make libraylib-dev
```

Build:

```bash
make
```

Run:

```bash
./main
```

## macOS

Install dependencies with Homebrew:

```bash
brew install raylib
```

Build:

```bash
make
```

Run:

```bash
./main
```

## Windows

### MSYS2 (Recommended)

Install MSYS2, then open the UCRT64 terminal and install dependencies:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-raylib
pacman -S make
```

Build:

```bash
make
```

Run:

```bash
./main.exe
```

## Clean

Remove build files:

```bash
make clean
```