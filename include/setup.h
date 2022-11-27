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

#define TERMINAL_WIDTH 80
#define WIDTH 50
#define HEIGHT 11

#define INNERSPACE_X 3
#define INNERSPACE_Y 1
#define STARTBOARD_X (TERMINAL_WIDTH - (INNERSPACE_X + 1) * NCOLS + 1) / 2
#define STARTBOARD_Y 5
#define BLINKING_INTERVAL 400000  // in microseconds
#define BLINKING_TIMES 5

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
int movementMenu(WINDOW* menu_win, char** printMenu(WINDOW*, int, int*));
void numRowsAndCols(FILE* fp, int* nrows, int* ncols);
void printLogo(char* filename, int centerCol);
char** printWhoStarts(WINDOW* menu_win, int highlight, int* n_choices);
char** printEndingMenu(WINDOW* menu_win, int highlight, int* n_choices);
char** printTilesReadyToPlay(WINDOW* menu_win, int highlight, int* n_choices);
char** printMainMenu(WINDOW* menu_win, int highlight, int* n_choices);
char** printStats(WINDOW* menu_win, int highlight, int* n_choices);
char** printSettingsP1(WINDOW* menu_win, int highlight, int* n_choices);
char** printSettingsP2(WINDOW* menu_win, int highlight, int* n_choices);
char** printColors(WINDOW* menu_win, int highlight, int* n_choices, int col_extra);
void topRowComment();
void wclean(WINDOW* win);
void drawBoard();

#endif
