# Conway's Game of Life - CS106B Assignment 1

This repository contains my C++ implementation of Conway's Game of Life for Stanford's CS106B Assignment 1. The program is built using the Stanford C++ library, specifically using the Grid class for the 2D array representation of the game.

## Table of Contents
- [Introduction](#introduction)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Credits](#credits)
- [License](#license)

## Introduction

Conway's Game of Life is a cellular automaton devised by John Horton Conway in 1970. The game is a zero-player game, meaning its evolution is determined by its initial state, requiring no further input. The program simulates the cells' interaction based on a set of rules and displays the resulting generations.

The rules are as follows:
1. Any live cell with fewer than two live neighbors dies, as if by underpopulation.
2. Any live cell with two or three live neighbors lives on to the next generation.
3. Any live cell with more than three live neighbors dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

This implementation is built using the Stanford C++ library, specifically utilizing the Grid class for the 2D array representation of the game board.

## Getting Started

### Prerequisites

To run this program, you will need:

1. A C++ compiler that supports C++11 or later, such as GCC or Clang.
2. QT Creator

### Installation

1. Clone the repository or download the project files.
2. Ensure QT Creator is running properly.
3. Open the Life.pro file.

## Usage

1. Run the compiled program.
2. The program will prompt you for an input file containing the initial state of the Game of Life grid. The format of the input file should be one of the provided text files in the "res" folder.
3. Once the input file is loaded, the program will display the initial state and begin simulating the Game of Life.
4. You can animate the simulation with multiple generations, advance one generation at a time, or quit the program by following the on-screen prompts.

## Credits

This implementation of Conway's Game of Life was developed as part of Stanford University's CS106B course: Programming Abstractions. The original assignment description can be found [here](https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1176//assn/life.html).

## License

This project is provided for educational purposes only. Please refer to Stanford University's academic policies for guidelines on using this implementation in your coursework.