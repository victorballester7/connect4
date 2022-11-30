#ifndef __CONNECT4_H__
#define __CONNECT4_H__

#define _GNU_SOURCE
#include <limits.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

extern int NROWS, NCOLS;

#define INF 100000000  // lower bound when doing 4-in-a-row. In each board we can have at most 100 points per string and in total there are 4 * NCOLS strings.

/// @brief Adds a tile of the player 'player' in the column 'col'.
/// @param board Board of the game.
/// @param col Column in which we want to play.
/// @param player Player that is doing the play.
void addTile(char **board, int col, char player);

/// @brief Computes the number of available columns to play in given the actual board 'board'.
/// @param board Board of the game.
/// @return Number of available columns
int computeNumChilds(char **board);

/// @brief Extracts the 3 closest tiles in the board in the North and South directions from the position row = 'row' and column = 'col' of the board 'board'
/// @param board Board of the game.
/// @param row Row of the board from where we are creating the string.
/// @param col Column of the board from where we are creating the string.
/// @return A pointer to a string of length 6 formed with the 3 tiles in the North the tile [row, col] +  the 3 tiles in the South of the tile [row, col].
char *consecutiveN_S(char **board, int row, int col);

/// @brief Extracts the 3 closest tiles in the board in the North-East and South-West directions from the position row = 'row' and column = 'col' of the board 'board'
/// @param board Board of the game.
/// @param row Row of the board from where we are creating the string.
/// @param col Column of the board from where we are creating the string.
/// @return A pointer to a string of length 6 formed with the 3 tiles in the North-East the tile [row, col] + the 3 tiles in the South-West of the tile [row, col].
char *consecutiveNE_SW(char **board, int row, int col);

/// @brief Extracts the 3 closest tiles in the board in the North-West and South-East directions from the position row = 'row' and column = 'col' of the board 'board'
/// @param board Board of the game.
/// @param row Row of the board from where we are creating the string.
/// @param col Column of the board from where we are creating the string.
/// @return A pointer to a string of length 6 formed with the 3 tiles in the North-West the tile [row, col] + the 3 tiles in the South-East of the tile [row, col].
char *consecutiveNW_SE(char **board, int row, int col);

/// @brief Extracts the 3 closest tiles in the board in the West and East directions from the position row = 'row' and column = 'col' of the board 'board'
/// @param board Board of the game.
/// @param row Row of the board from where we are creating the string.
/// @param col Column of the board from where we are creating the string.
/// @return A pointer to a string of length 6 formed with the 3 tiles in the West the tile [row, col] + the 3 tiles in the East of the tile [row, col].
char *consecutiveW_E(char **board, int row, int col);

/// @brief Gives a mark to the string 'str' centered at a position that has a tile from player 'player'. The higher the mark is, the
/// @param str String to be evaluated.
/// @param player Player whose tile is in the middle of the string.
/// @return The mark given to the string.
int evaluateString(char *str, char player);

/// @brief Find the row, column and direction where the 4-in-a-row starts.
/// @param board Board of the game.
/// @param row Row in which there is one tile of the 4-in-a-row.
/// @param col Column in which there is one tile of the 4-in-a-row (associated with the previous row).
/// @return The direction in which the 4-in-a-row is done.
char find4InRow(char **board, int *row, int *col);

/// @brief Get the position of the first '0' value in the board from the left continuing the direction of three joint tiles.
/// @param board Board of the game.
/// @param direction Direction in which the 4-in-a-row is.
/// @param zeroRow Row of the first zero closest to the 4-in-a-row form the left in the direction 'direction'.
/// @param zeroCol Column of the first zero closest to the 4-in-a-row form the left in the direction 'direction'.
void getFirstLeftClosestZeroInGOODONE_VALUE(char **board, int direction, int *zeroRow, int *zeroCol);

/// @brief Get the position of the first '0' value in the board from the left continuing the direction of three joint tiles.
/// @param board Board of the game.
/// @param direction Direction in which the 4-in-a-row is.
/// @param zeroRow Row of the first zero closest to the 4-in-a-row form the left in the direction 'direction'.
/// @param zeroCol Column of the first zero closest to the 4-in-a-row form the left in the direction 'direction'.
void getFirstRightClosestZeroInGOODONE_VALUE(char **board, int direction, int *zeroRow, int *zeroCol);

/// @brief Evaluates the actual board.
/// @param board Board of the game.
/// @return The mark given to that board.
int heuristicFunction(char **board, char player);

/// @brief Checks whether or not the coordinate [row, col] of the board is inside the limits of the board.
/// @param row Number of the row.
/// @param col Number of the column.
/// @return Returns 1 ( = True) if it is [row, col] is inside the limits and 0 ( = False) if not.
int insideLimits(int row, int col);

/// @brief Checks whether or not is 4-in-a-row on the board in the last play.
/// @param board Board of the game.
/// @param col Number of the column of the last play.
/// @return Returns 1 ( = True) if there is 4-in-a-row and 0 ( = False) if not.
int is4InRow(char **board, int col);

/// @brief Checks whether or not the board is full.
/// @param board Board of the game.
/// @return Returns 1 ( = True) if the board is full and 0 ( = False) if not.
int isFull(char **board);

/// @brief Check if there is the same tile above of the position [row, col].
/// @param board Board of the game.
/// @param row Row of the tile.
/// @param col COlumn of the tile.
/// @return 1 if there is the same tile on the left and 0 otherwise.
int isSameTileAbove(char **board, int row, int col);

/// @brief Check if there is the same tile in the North-west direction of the position [row, col].
/// @param board Board of the game.
/// @param row Row of the tile.
/// @param col COlumn of the tile.
/// @return 1 if there is the same tile on the left and 0 otherwise.
int isSameTileInTheNW(char **board, int row, int col);

/// @brief Check if there is the same tile in the south-west of the position [row, col].
/// @param board Board of the game.
/// @param row Row of the tile.
/// @param col COlumn of the tile.
/// @return 1 if there is the same tile on the left and 0 otherwise.
int isSameTileInTheSW(char **board, int row, int col);

/// @brief Check if there is the same tile on the left of the position [row, col].
/// @param board Board of the game.
/// @param row Row of the tile.
/// @param col COlumn of the tile.
/// @return 1 if there is the same tile on the left and 0 otherwise.
int isSameTileOnTheLeft(char **board, int row, int col);

/// @brief Function to swap between players easily.
/// @param player One player.
/// @return Returns the other player.
char otherPlayer(char player);

/// @brief Does the match.
/// @return Returns '0' if there is a draw, '1' if the computer wins or '2' if the player wins.
char playGame();

/// @brief Converts a string of 6 digits from the set {0, 1, 2} into a number of base 3 (hence, a number between 0 and 728).
/// @param str String to be converted
/// @return The number in base 3
int stringToBase3(char *str);

/// @brief Computes the sum of the components of a vector.
/// @param v The vector whose components are to be summed.
/// @param n The length of the vector.
/// @return The sum of the components of the vector.
int sum(int v[], size_t n);

// char whoStarts();
// void printLine(int len);
// void addTile2(char **board, int col, char player);
// char playGame2();
// void printBoard(char **board);
#endif
