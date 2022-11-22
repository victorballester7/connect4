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

#define WIDTH 50
#define HEIGHT 11

char* fileNameCreation();
void uploadFile(char i);
int presentation();
WINDOW* createWindow(int height, int width, int startRow, int startCol);
void destroy_win(WINDOW* localWin);
int movementMenu(WINDOW* menu_win, char** printMenu(WINDOW*, int, int*));
void numRowsAndCols(FILE* fp, int* nrows, int* ncols);
void printLogo(char* filename, int centerCol);
char** printMenu(WINDOW* menu_win, int highlight, int* n_choices);
char** printStats(WINDOW* menu_win, int highlight, int* n_choices);
char** printSettingsP1(WINDOW* menu_win, int highlight, int* n_choices);
char** printSettingsP2(WINDOW* menu_win, int highlight, int* n_choices);
char** printColors(WINDOW* menu_win, int highlight, int* n_choices, int col_extra);

#endif
