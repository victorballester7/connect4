#define _GNU_SOURCE
#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
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

int main() {
  // char **board = {
  //     {'0', '0', '0', '0', '0', '0', '0'},
  //     {'0', '0', '0', '0', '0', '0', '0'},
  //     {'0', '0', '0', '0', '0', '0', '0'},
  //     {'0', '0', '0', '0', '2', '0', '0'},
  //     {'0', '0', '0', '1', '1', '0', '0'},
  //     {'1', '0', '0', '2', '2', '2', '0'}};
  // printBoard(board);
  // printf("%d\n", heuristicFunction(board));
  // setlocale(LC_ALL, "");
  // initscr();  // start ncurses mode.
  // clear();    // clear screen.
  // noecho();   // Don't echo() while doing getch().
  // cbreak();   // Line buffering disabled. pass on everything.
  printf("Num of cols: %i\n Num of rows: %i", COLS, LINES);
}
