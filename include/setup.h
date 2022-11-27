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

#define INNERSPACE_X 3
#define INNERSPACE_Y 1
#define STARTBOARD_Y 5
// Since STARTBOARD_X depends on the width of the screen, it cannot be declared at the beginning of the program because the screen of ncurses hasn't been initialized yet.
#define BLINKING_INTERVAL 400000  // in microseconds
#define BLINKING_TIMES 5

void defineConstants();
void blinking(int startRow, int startCol, char direction, int color);
void drawTile(int row, int col, int color);
void find4inRow(int* startRow, int* startCol, char* direction);
int endOfGame(char winner, int startRow, int startCol, char direction);
void clearFirstLines(int n);
char* fileNameCreation();
void uploadFile(char i);
int presentation();
WINDOW* createWindow(int height, int width, int startRow, int startCol);
void destroy_win(WINDOW* localWin);
int movementMenu(WINDOW* menu_win, char** menu(WINDOW*, int*, int*, int*), int type);
void printMenu(WINDOW* menu_win, char** menu(WINDOW*, int*, int*, int*), int type, int* n_choices, int highlight);
void numRowsAndCols(FILE* fp, int* nrows, int* ncols);
void printLogo(char* filename, int centerCol);

char** menuWhoStarts(WINDOW* menu_win, int* n_choices, int* startX, int* startY);
char** menuEndingMenu(WINDOW* menu_win, int* n_choices, int* startX, int* startY);
char** menuTilesReadyToPlay(WINDOW* menu_win, int* n_choices, int* startX, int* startY);
char** menuMainMenu(WINDOW* menu_win, int* n_choices, int* startX, int* startY);
char** menuStats(WINDOW* menu_win, int* n_choices, int* startX, int* startY);
char** menuDepth(WINDOW* menu_win, int* n_choices, int* startX, int* startY);
char** menuBoardSizeRows(WINDOW* menu_win, int* n_choices, int* startX, int* startY);
char** menuBoardSizeCols(WINDOW* menu_win, int* n_choices, int* startX, int* startY);
char** menuBoardSize(WINDOW* menu_win, int* n_choices, int* startX, int* startY, int row_extra);
char** menuSettings(WINDOW* menu_win, int* n_choices, int* startX, int* startY);
char** menuColorsP1(WINDOW* menu_win, int* n_choices, int* startX, int* startY);
char** menuColorsP2(WINDOW* menu_win, int* n_choices, int* startX, int* startY);
char** menuColors(WINDOW* menu_win, int* n_choices, int* startX, int* startY, int col_extra);
void topRowComment();
void wclean(WINDOW* win);
void drawBoard();

#endif
