#ifndef __SETUP_H__
#define __SETUP_H__

#define _GNU_SOURCE
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "../include/minimax.h"

// #define WINDOWS // uncomment this line to use it for windows.

#ifdef WINDOWS
#include <direct.h>
#define pwd _getcwd
#else
#include <unistd.h>  // also for sleep() function. In Windows use <windows.h>
#define pwd getcwd
#endif

// #define TERMINAL_WIDTH 80   // By default it is stored in constant COLS when ncurses.h is started.
// #define TERMINAL_HEIGHT 80  // By default it is stored in constant LINES when ncurses.h is started.
#define WIN_WIDTH 50
#define WIN_HEIGHT 11
#define BLINKING_INTERVAL 400000  // in microseconds
#define BLINKING_TIMES 5
#define ANIMATION_INTERVAL 25000  // in microseconds
#define MIN_DEPTH 4               // minimum depth that the algorithm will play in practice

/// @brief Function to make the blinking of the 4-in-a-row when you win or lose the game.
/// @param startRow Row where the 4-in-a-row starts.
/// @param startCol Column where the 4-in-a-row starts.
/// @param direction Direction in which the 4-in-a-row extends (can be 'h' (for horizontal), 'v' (for vertical), 'd' (for the NW - SE diagonal) or 'D' (for the SW - NE diagonal)).
/// @param color Color of the tiles that make the 4-in-a-row.
void blinking(int startRow, int startCol, char direction, int color);

/// @brief Clears the first two lines of the screen.
void clearFirst3Lines();

/// @brief Clears the n-th line of the screen.
/// @param n number of the line to be cleared.
void clearLine(int n);

/// @brief It creates an abstract window on the screen.
/// @param height Height of the window.
/// @param width Width of the window.
/// @param startRow Row where the window starts.
/// @param startCol Column where the window starts.
/// @return A pointer to the window.
WINDOW* createWindow(int height, int width, int startRow, int startCol);

/// @brief Destroys a window previously created.
/// @param win The window to be destroyed.
void destroy_win(WINDOW* win);

/// @brief Draws the board of the game on the screen.
void drawBoard();

/// @brief Draws a tile on the board.
/// @param row Row where the tile should be drawn.
/// @param col Column where the tile should be drawn.
/// @param color Color of the tile.
void drawTile(int row, int col, int color);

/// @brief It clears the screen and returns to the main terminal interface.
void ending();

/// @brief Makes the animations for the end of the match.
/// @param winner The result of the game (can be '0' (there has been a draw), '1'  (the winner has been the computer) or '2' (the winner has been the player)).
/// @param startRow Row where the 4-in-a-row starts (if any).
/// @param startCol Column where the 4-in-a-row starts (if any).
/// @param direction Direction in which the 4-in-a-row extends (can be 'h' (for horizontal), 'v' (for vertical), 'd' (for the NW - SE diagonal) or 'D' (for the SW - NE diagonal)) (if any).
/// @return The option of the menu 'menuEndingMenu' for choosing what to do after the match.
int endOfMatch(char winner, int startRow, int startCol, char direction);

/// @brief Converts the DEPTH of the algorithm into a more firendlier name of difficulty.
/// @return The name of the difficulty associated with the current DEPTH.
char* getDifficulty();

/// @brief Converts the size of the tiles of the board into "small", "medium" or "large"
/// @return Either on of the following strings "small", "medium" or "large".
char* getNameSize();

/// @brief Checks whether or not a key has been pressed.
/// @return 1 if a key has been pressed and 0 otherwise.
int kbhit();

/// @brief Menu for changing the board size.
/// @param menu_win Pointer to the window where the menu is printed.
/// @param n_choices Number of choices of the menu.
/// @param startX x-coordinate of the window where the options start to be printed.
/// @param startY y-coordinate of the window where the options start to be printed.
/// @param row_extra An extra parameter to distinguish between printing the columns and the rows.
/// @return Pointer to the list of choices.
char** menuBoardSize(WINDOW* menu_win, int* n_choices, int* startX, int* startY, int row_extra);

/// @brief Pre-configuration menu for the columns in the menuBoardSize.
/// @param menu_win Pointer to the window where the menu is printed.
/// @param n_choices Number of choices of the menu.
/// @param startX x-coordinate of the window where the options start to be printed.
/// @param startY y-coordinate of the window where the options start to be printed.

/// @return Pointer to the list of choices.
char** menuBoardSizeCols(WINDOW* menu_win, int* n_choices, int* startX, int* startY);

/// @brief Pre-configuration menu for the rows in the menuBoardSize.
/// @param menu_win Pointer to the window where the menu is printed.
/// @param n_choices Number of choices of the menu.
/// @param startX x-coordinate of the window where the options start to be printed.
/// @param startY y-coordinate of the window where the options start to be printed.

/// @return Pointer to the list of choices.
char** menuBoardSizeRows(WINDOW* menu_win, int* n_choices, int* startX, int* startY);

/// @brief Menu for changing the colors of the tiles.
/// @param menu_win Pointer to the window where the menu is printed.
/// @param n_choices Number of choices of the menu.
/// @param startX x-coordinate of the window where the options start to be printed.
/// @param startY y-coordinate of the window where the options start to be printed.
/// @param col_extra An extra parameter to distinguish between the tiles of the player and the tiles of the computer.
/// @return Pointer to the list of choices.
char** menuColors(WINDOW* menu_win, int* n_choices, int* startX, int* startY, int col_extra);

/// @brief Pre-configuration menu for the color of the tiles of the player in the menuColors.
/// @param menu_win Pointer to the window where the menu is printed.
/// @param n_choices Number of choices of the menu.
/// @param startX x-coordinate of the window where the options start to be printed.
/// @param startY y-coordinate of the window where the options start to be printed.
/// @return Pointer to the list of choices.
char** menuColorsP1(WINDOW* menu_win, int* n_choices, int* startX, int* startY);

/// @brief Pre-configuration menu for the color of the tiles of the computer in the menuColors.
/// @param menu_win Pointer to the window where the menu is printed.
/// @param n_choices Number of choices of the menu.
/// @param startX x-coordinate of the window where the options start to be printed.
/// @param startY y-coordinate of the window where the options start to be printed.
/// @return Pointer to the list of choices.
char** menuColorsP2(WINDOW* menu_win, int* n_choices, int* startX, int* startY);

/// @brief Menu for changing the difficulty of the game.
/// @param menu_win Pointer to the window where the menu is printed.
/// @param n_choices Number of choices of the menu.
/// @param startX x-coordinate of the window where the options start to be printed.
/// @param startY y-coordinate of the window where the options start to be printed.
/// @return Pointer to the list of choices.
char** menuDifficulty(WINDOW* menu_win, int* n_choices, int* startX, int* startY);

/// @brief Menu for printing the options for what to do at the end of the game.
/// @param menu_win Pointer to the window where the menu is printed.
/// @param n_choices Number of choices of the menu.
/// @param startX x-coordinate of the window where the options start to be printed.
/// @param startY y-coordinate of the window where the options start to be printed.
/// @return Pointer to the list of choices.
char** menuEndingMenu(WINDOW* menu_win, int* n_choices, int* startX, int* startY);

/// @brief Menu for printing the main menu (start-up menu).
/// @param menu_win Pointer to the window where the menu is printed.
/// @param n_choices Number of choices of the menu.
/// @param startX x-coordinate of the window where the options start to be printed.
/// @param startY y-coordinate of the window where the options start to be printed.
/// @return Pointer to the list of choices.
char** menuMainMenu(WINDOW* menu_win, int* n_choices, int* startX, int* startY);

/// @brief Menu for printing the settings of the game.
/// @param menu_win Pointer to the window where the menu is printed.
/// @param n_choices Number of choices of the menu.
/// @param startX x-coordinate of the window where the options start to be printed.
/// @param startY y-coordinate of the window where the options start to be printed.
/// @return Pointer to the list of choices.
char** menuSettings(WINDOW* menu_win, int* n_choices, int* startX, int* startY);

/// @brief Menu for printing the statistics of the game.
/// @param menu_win Pointer to the window where the menu is printed.
/// @param n_choices Number of choices of the menu.
/// @param startX x-coordinate of the window where the options start to be printed.
/// @param startY y-coordinate of the window where the options start to be printed.
/// @return Pointer to the list of choices.
char** menuStats(WINDOW* menu_win, int* n_choices, int* startX, int* startY);

/// @brief Menu for printing the top tile when making a play during the match.
/// @param menu_win Pointer to the window where the menu is printed.
/// @param n_choices Number of choices of the menu.
/// @param startX x-coordinate of the window where the options start to be printed.
/// @param startY y-coordinate of the window where the options start to be printed.
/// @return Pointer to the list of choices.
char** menuTilesReadyToPlay(WINDOW* menu_win, int* n_choices, int* startX, int* startY);

/// @brief Menu for printing the who-starts menu of the game.
/// @param menu_win Pointer to the window where the menu is printed.
/// @param n_choices Number of choices of the menu.
/// @param startX x-coordinate of the window where the options start to be printed.
/// @param startY y-coordinate of the window where the options start to be printed.
/// @return Pointer to the list of choices.
char** menuWhoStarts(WINDOW* menu_win, int* n_choices, int* startX, int* startY);

/// @brief Function to perform the movement of all the menus of the game.
/// @param menu_win Pointer to the window where the menu is printed.
/// @param menu Menu of the game to be animated.
/// @param type Type of menu (1 (ordinary menus), 2 (TilesReadyToPlay menu) or 3 (numbers menu: print numbers for example when choosing the size of the board)).
/// @return The choice done during the menu, starting from 1.
int movementMenu(WINDOW* menu_win, char** menu(WINDOW*, int*, int*, int*), int type);

/// @brief Computes the number of rows and columns of a file
/// @param fp Pointer to the file to be examined.
/// @param nrows Pointer to the integer where the number of rows should be stored.
/// @param ncols Pointer to the integer where the number of columns should be stored.
void numRowsAndCols(FILE* fp, int* nrows, int* ncols);

/// @brief Function that prints a logo on the screen.
/// @param filename Name of the file where the logo is.
/// @param centerCol Column from which the logo should be centered.
void printLogo(char* filename, int centerCol);

/// @brief Function to print the menus depending on their type.
/// @param menu_win Pointer to the window where the menu is printed.
/// @param menu Menu to be printed.
/// @param type Type of menu (1 (ordinary menus), 2 (TilesReadyToPlay menu) or 3 (numbers menu: print numbers for example when choosing the size of the board)).
/// @param n_choices Number of choices of the menu to be printed.
/// @param highlight Current selected option, starting from 1.
void printMenu(WINDOW* menu_win, char** menu(WINDOW*, int*, int*, int*), int type, int* n_choices, int highlight);

/// @brief Function to draw a rectangle on the screen.
/// @param startX x-coordinate which the rectangle should be started to draw from.
/// @param startY y-coordinate which the rectangle should be started to draw from.
/// @param lenX width of the rectangle.
/// @param lenY height of the rectangle
void rectangle(int startX, int startY, int lenX, int lenY);

/// @brief Sets the dimensions of the minimum width of the terminal and the minimum height of the terminal
/// @param min_terminal_width Pointer to the parameter controlling the minimum width of the terminal
/// @param min_terminal_height Pointer to the parameter controlling the minimum height of the terminal
void setMinDimensions(int* min_terminal_width, int* min_terminal_height);

/// @brief Function to decide whether or not your function supports colors.
/// @return 1 if your terminal supports colors; 0, otherwise.
int supportsColors();

/// @brief Function to print the informative top comment on the screen.
void topRowComment();

/// @brief Function to upload the file of statistics.
/// @param i Result of the game ('0' (there was a draw), '1' (the winner was the computer) or '2' (the winner was the player))
void uploadFile(char i);

#endif
