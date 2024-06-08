# Sketch File Visualizer

This repository contains the source code for a Sketch File Visualizer. The project involves creating a program (`sketch.c`) that reads and visualizes `.sk` sketch files using a provided display module.


# Project Overview

This project consists of two main C source files, `sketch.c` and `displayfull.c`, and their corresponding header files `sketch.h` and `displayfull.h`. The codebase primarily deals with graphics-related functions, providing functionalities for displaying and manipulating various graphic objects.


## File Descriptions

### sketch.c
The `sketch.c` file includes functions necessary for creating and manipulating graphic objects. The main functionalities of this file are:
- Initialization of graphic objects
- Setting and changing object properties
- Rendering objects

### sketch.h
The `sketch.h` file declares the functions used in `sketch.c` and defines the necessary data structures. This header file allows other source files to use the functionalities provided by `sketch.c`.

### displayfull.c
The `displayfull.c` file includes functions necessary for displaying graphic objects on the screen. The main functionalities of this file are:
- Setting the position of graphic objects
- Setting the color and style of objects
- Handling the movement and animation of objects

### displayfull.h
The `displayfull.h` file declares the functions used in `displayfull.c` and defines the necessary data structures. This header file allows other source files to use the functionalities provided by `displayfull.c`.


## Installation and Build

To compile and run the project, you need to have `clang` and `SDL2` installed on your Unix-based system.

### Installation

1. **Clone the repository:**
    ```sh
    https://github.com/henry3361/Graphix_display.git
    ```

2. Extract all provided files into your project directory.

### Compilation

**To compile the provided skeleton files with graphics, use:**
    ```sh
    clang -std=c11 -Wall -pedantic -g sketch.c displayfull.c -I/usr/include/SDL2 -lSDL2 -o sketch -fsanitize=undefined -fsanitize=address
    ```

### Running the Program

**To run the program on a sketch file:**
    ```sh
    ./sketch sketch00.sk
    ```

This will open a 200 x 200 black display window where the sketch will be visualised

### Testing

**To test without the graphics module:**
    ```sh
    clang -DTESTING -std=c11 -Wall -pedantic -g sketch.c test.c -I/usr/include/SDL2 -o test -fsanitize=undefined -fsanitize=address
    ```
    ```sh
    ./test
    ```

Make sure all sketch files(sketch00.sk to sketch09.sk) are persent in your local folder during testing

