#define _GNU_SOURCE
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/connect4.h"
#include "../include/extra.h"
#include "../include/minimax.h"
#include "../include/setup.h"
// void fail(char *msg) {
//   endwin();
//   puts(msg);
//   exit(EXIT_FAILURE);
// }

// int nProduct(int n, int times) {
//   int i = 0, result = 1;
//   while (i++ < times) result *= n;
//   return result;
// }

// int sum(int v[], size_t n) {
//   int sum = 0;
//   for (int i = 0; i < n; i++) sum += v[i];
//   return sum;
// }
extern int NCOLS, NROWS;

int main() {
  NCOLS = 8;
  NROWS = 8;
  char **board = (char **)malloc(NROWS * sizeof(char *));
  for (int i = 0; i < NROWS; i++) {
    board[i] = (char *)malloc(NCOLS * sizeof(char));
  }
  board[0] = "00000000";
  board[1] = "00000000";
  board[2] = "00000000";
  board[3] = "00021020";
  board[4] = "00011010";
  board[5] = "00012020";
  board[6] = "11122120";
  board[7] = "22211120";
  printBoard(board);
  int sum = 0;
  for (int i = 0; i < NROWS; i++) {
    for (int j = 0; j < NCOLS; j++)
      sum += board[i][j] / 49;
  }
  printf("total sum: %i\n", sum);
  // printf("1 - %d\n", heuristicFunction(board, '2'));

  // board[5] = "02012020";
  // board[7] = "02211120";
  // printBoard(board);
  // printf("2 - %d\n", heuristicFunction(board, '2'));

  // board[5] = "00212020";
  // printBoard(board);
  // printf("3 - %d\n", heuristicFunction(board, '2'));

  // board[5] = "00012020";
  // board[2] = "00020000";
  // printBoard(board);
  // printf("4 - %d\n", heuristicFunction(board, '2'));

  // board[2] = "00002000";
  // printBoard(board);
  // printf("7 - %d\n", heuristicFunction(board, '2'));

  // board[2] = "00000000";
  // board[5] = "00012220";
  // printBoard(board);
  // printf("5 - %d\n", heuristicFunction(board, '2'));

  // board[5] = "00012020";
  // board[2] = "00000020";
  // printBoard(board);
  // printf("6 - %d\n", heuristicFunction(board, '2'));

  // board[5] = "00012020";
  // board[7] = "02211122";
  // printBoard(board);
  // printf("8 - %d\n", heuristicFunction(board, '2'));

  // for (int i = 1; i < 7; i++) {
  //   board[row][col] = '0';
  //   col = computeColumn(board, i);
  //   row = computeRow(board, row);
  //   board[row][col] = player;
  //   printBoard(board);
  //   printf("1 - %d\n", heuristicFunction(board, player));
  // }
  // printf("%d\n", heuristicFunction(board, '2'));
  // setlocale(LC_ALL, "");
  // initscr();  // start ncurses mode.
  // clear();    // clear screen.
  // noecho();   // Don't echo() while doing getch().
  // cbreak();   // Line buffering disabled. pass on everything.
  // printf("Num of cols: %i\n Num of rows: %i", COLS, LINES);
}
