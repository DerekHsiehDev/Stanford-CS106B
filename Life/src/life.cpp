/**
 * @file
 * @brief Stanford Assignment 1: C++ implementation of the Game of Life
 * @author Derek Hsieh
 * @date 4/30/2023
 */


#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "strlib.h"
#include <chrono>
#include <thread>

using namespace std;


/**
 * @brief Set the game board from a string representation.
 *
 * @param content The string representation of the game board.
 * @param gameboard The game board to be set.
 */
void setGameboardFromString(string &content, Grid<bool> &gameboard);

/**
 * @brief Print the game board to the console.
 *
 * @param gameboard The game board to be printed.
 */
void printGameboard(Grid<bool> &gameboard);

/**
 * @brief Advance the game board to the next generation.
 *
 * @param gameboard The game board to be advanced.
 * @param isWrapped Whether the game board should wrap around its edges.
 */
void advanceGeneration(Grid<bool>& gameboard, bool isWrapped);

/**
 * @brief Animate a specified number of generations of the game board.
 *
 * @param frames The number of generations to animate.
 * @param gameboard The game board to be animated.
 * @param isWrapped Whether the game board should wrap around its edges.
 */
void animateGeneration(int frames, Grid<bool> &gameboard, bool isWrapped);

/**
 * @brief Get the contents of a file and set the game board size accordingly.
 *
 * @param fileName The name of the file to read.
 * @param gameboard The game board whose size will be set.
 * @return The contents of the file as a string.
 */
string getFileContents(string fileName, Grid<bool> &gameboard);



int main() {
    cout << "Welcome to the CS 106B Game of Life," << endl <<
        "a simulation of the lifecycle of a bacteria colony." << endl
         << "Cells (X) live and die by the following rules:" << endl
         << "- A cell with 1 or fewer neighbors dies." << endl
         << "- Locations with 2 neighbors remain stable." << endl
         << "- Locations with 3 neighbors will create life." << endl
         << "- A cell with 4 or more neighbors dies.\n" << endl;

    string fileName = getLine("Grid Input File Name?");

    string userInput = ""; // a, t, q

    Grid<bool> gameboard(0,0);

    while(!fileExists(fileName)) {

        cout << "file doesn't exist. try again" << endl;
        fileName = getLine("Grid Input File Name?");
    }

    string gameboardContent = getFileContents(fileName, gameboard);
    setGameboardFromString(gameboardContent, gameboard);


    string wrappedInput = getLine("Should the simulation wrap around the grid (y/n)?");
    bool isWrapped = false;



    if(wrappedInput == "y") {
        isWrapped = true;
    }





    printGameboard(gameboard);
    userInput = getLine("a)nimate, t)ick, q)uit?");

    // get file contents

    while(userInput != "q") {

        if(userInput == "a") {
            int frames = getInteger("How many frames?");



            animateGeneration(frames, gameboard, isWrapped);


        } else if(userInput == "t") {

            advanceGeneration(gameboard, isWrapped) ;

            printGameboard(gameboard);

        } else {
            cout << "please pick one of the following" << endl;

            userInput = getLine("a)nimate, t)ick, q)uit?");
        }



        userInput = getLine("a)nimate, t)ick, q)uit?");

    }


    cout << "Have a nice life!" << endl;


    return 0;

}



void setGameboardFromString(string &content, Grid<bool> &gameboard) {

    int contentIndex = 0;

    for(int i = 0; i < gameboard.numRows(); i++) {
        for(int j = 0; j < gameboard.numCols(); j++) {
            char currentChar = content[contentIndex];

            if(currentChar == '-') {
                gameboard[i][j] = false;

            } else {
                gameboard[i][j] = true;
            }
            contentIndex++;
        }
    }


}

void printGameboard(Grid<bool> &gameboard) {

    for(int i = 0; i < gameboard.numRows(); i++) {
        for(int j = 0; j < gameboard.numCols(); j++) {
            //            cout << gameboard[i][j] == true ? "X" : "-";
            if(gameboard[i][j]) {
                cout << "X";
            } else {
                cout << "-";
            }
        }
        cout << endl;
    }

}

string getFileContents(string fileName, Grid<bool> &gameboard) {

    ifstream input;


    openFile(input, fileName);
    int cols = -1, rows = -1;

    string line;

    string gameboardString = "";



    while(getline(input, line)) {
        if(cols == -1 && stringToInteger(line)) {
            int intValue = stringToInteger(line);

            if(rows == -1) {
                rows = intValue;
            } else {
                cols = intValue;
                gameboard.resize(rows, cols);
            }
        } else {
            // populate gameboard

            // full line,

                gameboardString += (line);

        }


    }

    input.close();

    return gameboardString;

}

void advanceGeneration(Grid<bool>& gameboard, bool isWrapped = false) {

    int numRows = gameboard.numRows();
    int numCols = gameboard.numCols();

    Grid<bool> nextGeneration(numRows, numCols);

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            int aliveNeighbors = 0;

            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    // only check neighbors, x = 0, y = 0 means that its checking the current cell
                    if (x == 0 && y == 0) continue;

                    int neighborRow = i + x;
                    int neighborCol = j + y;

                    if (gameboard.inBounds(neighborRow, neighborCol)) {
                        if(gameboard[neighborRow][neighborCol])
                            aliveNeighbors++;
                    } else if(isWrapped) {
                        // wrapped col and row
                        int wrappedRow = (neighborRow + numRows) % numRows;
                        int wrappedCol = (neighborCol + numCols) % numCols;

                        if(gameboard[wrappedRow][wrappedCol]) {
                            aliveNeighbors++;
                        }
                    }
                }
            }

            bool currentCell = gameboard[i][j];

            if (currentCell && (aliveNeighbors < 2 || aliveNeighbors > 3)) {
                nextGeneration[i][j] = false;
            } else if (!currentCell && aliveNeighbors == 3) {
                nextGeneration[i][j] = true;
            } else {
                nextGeneration[i][j] = currentCell;
            }
        }
    }

    gameboard = nextGeneration;

}

void animateGeneration(int frames, Grid<bool> &gameboard, bool isWrapped = false) {


    for (int i = 0; i < frames; i++) {

        clearConsole();

        // Print the updated grid

        advanceGeneration(gameboard, isWrapped);

        printGameboard(gameboard);

        // Advance the generation

        // Pause the execution for the specified duration
        pause(50);


    }


}







