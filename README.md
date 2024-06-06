# Sketch File Visualizer

This repository contains the source code for a Sketch File Visualizer, a project developed as part of the COMS10016: Imperative and Functional Programming course at the University of Bristol. The project involves creating a program (`sketch.c`) that reads and visualizes .sk sketch files using a provided display module.

## Project Overview

### Task Description

The main task is to develop a program (`sketch.c`) that reads in and visualizes .sk files using the `displayfull.h` module for graphics. The .sk files contain drawings or graphics encoded as a sequence of single-byte commands. The project is divided into several steps to incrementally build a sketch viewer with increasing functionality:

1. **Basic Sketch Viewer**: Supports simple commands to draw white lines on a black background.
2. **Intermediate Sketch Viewer**: Adds support for additional commands to handle colors, blocks, and absolute positioning.

### Provided Files

- `sketch.h` - Skeleton header file
- `sketch.c` - Skeleton C file to be completed
- `Makefile` - Basic Makefile for Unix
- `displayfull.h` - Display module header
- `displayfull.c` - Display module implementation
- `test.c` - Testing framework
- `sketch00.sk` to `sketch09.sk` - Example sketch files for testing

## Getting Started

### Prerequisites

To compile and run the project, you need to have `clang` and `SDL2` installed on your Unix-based system.

### Installation

1. Clone the repository:
    ```
    https://github.com/henry3361/Graphix_display.git
    ```

2. Extract all provided files into your project directory.

### Compilation

To compile the provided skeleton files with graphics, use:
```
clang -std=c11 -Wall -pedantic -g sketch.c displayfull.c -I/usr/include/SDL2 -lSDL2 -o sketch -fsanitize=undefined -fsanitize=address
```

### Running the Program

To run the program on a sketch file:
```
./sketch sketch00.sk
```

This will open a 200 x 200 black display window where the sketch will be visualised

### Testing

To test without the graphics module:
```
clang -DTESTING -std=c11 -Wall -pedantic -g sketch.c test.c -I/usr/include/SDL2 -o test -fsanitize=undefined -fsanitize=address
```
```
./test
```

Make sure all sketch files(sketch00.sk to sketch09.sk) are persent in your local folder during testing

