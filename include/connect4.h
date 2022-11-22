#ifndef __CONNECT4_H__
#define __CONNECT4_H__

#include <limits.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NROWS 6        // Number of rows of the board
#define NCOLS 7        // Number of columns of the board
#define INF 100000000  // lower bound when doing 4-in-a-row. In each board we can have at most 100 points per string and in total there are 4 * NCOLS strings.

/// @brief Adds a tile of the player 'player' in the column 'col'.
/// @param board Board of the game.
/// @param col Column in which we want to play.
/// @param player Player that is doing the play.
void addTile(char board[NROWS][NCOLS], int col, char player);

/// @brief Clear all the screen.
void clean();

/// @brief Computes the number of available columns to play in given the actual board 'board'.
/// @param board Board of the game.
/// @return Number of available columns
int computeNumChilds(char board[NROWS][NCOLS]);

/// @brief Extracts the 3 closest tiles in the board in the North and South directions from the position row = 'row' and column = 'col' of the board 'board'
/// @param board Board of the game.
/// @param row Row of the board from where we are creating the string.
/// @param col Column of the board from where we are creating the string.
/// @return A pointer to a string of length 6 formed with the 3 tiles in the North the tile [row, col] +  the 3 tiles in the South of the tile [row, col].
char* consecutiveN_S(char board[NROWS][NCOLS], int row, int col);

/// @brief Extracts the 3 closest tiles in the board in the North-West and South-East directions from the position row = 'row' and column = 'col' of the board 'board'
/// @param board Board of the game.
/// @param row Row of the board from where we are creating the string.
/// @param col Column of the board from where we are creating the string.
/// @return A pointer to a string of length 6 formed with the 3 tiles in the North-West the tile [row, col] + the 3 tiles in the South-East of the tile [row, col].
char* consecutiveNW_SE(char board[NROWS][NCOLS], int row, int col);

/// @brief Extracts the 3 closest tiles in the board in the North-East and South-West directions from the position row = 'row' and column = 'col' of the board 'board'
/// @param board Board of the game.
/// @param row Row of the board from where we are creating the string.
/// @param col Column of the board from where we are creating the string.
/// @return A pointer to a string of length 6 formed with the 3 tiles in the North-East the tile [row, col] + the 3 tiles in the South-West of the tile [row, col].
char* consecutiveNE_SW(char board[NROWS][NCOLS], int row, int col);

/// @brief Extracts the 3 closest tiles in the board in the West and East directions from the position row = 'row' and column = 'col' of the board 'board'
/// @param board Board of the game.
/// @param row Row of the board from where we are creating the string.
/// @param col Column of the board from where we are creating the string.
/// @return A pointer to a string of length 6 formed with the 3 tiles in the West the tile [row, col] + the 3 tiles in the East of the tile [row, col].
char* consecutiveW_E(char board[NROWS][NCOLS], int row, int col);

/// @brief Gives a mark to the string 'str' centered at a position that has a tile from player 'player'. The higher the mark is, the
/// @param str
/// @param player
/// @return
int evaluateString(char* str, char player);

char* exchangeOnesAndTwos(char* str);

/// @brief Evaluates the actual board.
/// @param board Board of the game.
/// @return The mark given to that board.
int heuristicFunction(char board[NROWS][NCOLS]);

/// @brief Checks whether or not the coordinate [row, col] of the board is inside the limits of the board.
/// @param row Number of the row.
/// @param col Number of the column.
/// @return Returns 1 ( = True) if it is [row, col] is inside the limits and 0 ( = False) if not.
int insideLimits(int row, int col);

/// @brief Checks whether or not is 4-in-a-row on the board in the last play.
/// @param board Board of the game.
/// @param col Number of the column of the last play.
/// @return Returns 1 ( = True) if there is 4-in-a-row and 0 ( = False) if not.
int is4InRow(char board[NROWS][NCOLS], int col);

/// @brief Checks whether or not the board is full.
/// @param board Board of the game.
/// @return Returns 1 ( = True) if the board is full and 0 ( = False) if not.
int isFull(char board[NROWS][NCOLS]);

/// @brief Function to swap between players easily.
/// @param player One player.
/// @return Returns the other player.
char otherPlayer(char player);

/// @brief Does the match.
/// @return Returns '0' if there is a draw, '1' if the computer wins or '2' if the player wins.
char playGame2();

/// @brief Prints the board of the game on the screen.
/// @param board Board of the game.
void printBoard(char board[NROWS][NCOLS]);

void printLine(int len);

// /// @brief
// /// @param board
// /// @param row
// /// @param col
// /// @return   // print a line of dashes of length 'len'
// char* removeCenterChar(char* str);

/// @brief Converts a string of 6 digits from the set {0, 1, 2} into a number of base 3 (hence, a number between 0 and 728).
/// @param str String to be converted
/// @return The number in base 3
int stringToBase3(char* str);

/// @brief Decides who is going to start the game.
/// @return Returns '1' if the computer is going to start or '2' if it is the player instead.
char whoStarts();

#endif
