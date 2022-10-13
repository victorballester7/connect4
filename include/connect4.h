#ifndef __CONNECT4_H__
#define __CONNECT4_H__

#define NROWS 6  // Number of rows of the board
#define NCOLS 6  // Number of columns of the board
#define EPS 1e-5

void uploadFile(char i);
char playGame();
int computeNumChilds(char board[NROWS][NCOLS]);
int isFull(char board[NROWS][NCOLS]);
char otherPlayer(char player);
char whoStarts();
void addTile(char board[NROWS][NCOLS], int col, char player);
int presentation();
void printLine(int len);  // print a line of dashes of length 'len'
void printBoard(char board[NROWS][NCOLS]);
void clear();
double heuristicFunction(char board[NROWS][NCOLS], char player);
int insideLimits(int row, int col);
double evaluateString(char* s, char player);
char* consecutiveW_E(char board[NROWS][NCOLS], int row, int col);
char* consecutiveN_S(char board[NROWS][NCOLS], int row, int col);
char* consecutiveNW_SE(char board[NROWS][NCOLS], int row, int col);
char* consecutiveNE_SW(char board[NROWS][NCOLS], int row, int col);
char* removeCenterChar(char* str);
int is4InRow(char board[NROWS][NCOLS], int col);
// int consecutiveEast(char board[NROWS][NCOLS], int row, int col);
// int consecutiveSouth(char board[NROWS][NCOLS], int row, int col);
// int consecutiveSouthWest(char board[NROWS][NCOLS], int row, int col);
// int consecutiveSouthEast(char board[NROWS][NCOLS], int row, int col);
// int is4InRow(char board[NROWS][NCOLS], char player);
int rowFirstEmpty(char board[NROWS][NCOLS], int col);

#endif
