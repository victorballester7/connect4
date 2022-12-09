#ifndef __EXTRA_H__
#define __EXTRA_H__

#include <limits.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

char whoStarts();
void printLine(int len);
void addTile2(char **board, int col, char player);
char playGame2();
void printBoard(char **board);
#endif
