#include "../include/extra.h"

#include "../include/connect4.h"
#include "../include/minimax.h"

extern int colorPlayer, colorComputer, NROWS, NCOLS;

char playGame2() {  // do the match. Returns if there is a draw, 1 if the computer wins and 2 if the player wins.
  // int i= presentation();
  char** board = malloc(NROWS * sizeof(char*));
  for (int i = 0; i < NROWS; i++) {
    board[i] = malloc(NCOLS * sizeof(char));
    memset(board[i], '0', NCOLS);
  }
  int choice;
  char lastPlayer;
  // int len = nProduct(NCOLS, DEPTH), v[len];
  // memset(v, 0, len);
  lastPlayer = whoStarts();
  system("clear");
  while (!isFull(board)) {
    if (lastPlayer == '2') {  // player's turn
      printf("Where do you want to play in (the number of the column starts on 1)?\n");
      printBoard(board);
      scanf("%i", &choice);
      choice--;
    } else {  // computer's turn
      choice = computerPlay(board);
    }
    if (choice < 0 || choice >= NCOLS || board[0][choice] != '0') {
      printf("The column enter is not valid! Play again.\n");
      continue;
    }
    addTile2(board, choice, lastPlayer);
    // clean();
    if (is4InRow(board, choice)) {
      printBoard(board);
      return lastPlayer;
    }
    lastPlayer = otherPlayer(lastPlayer);
  }

  return '0';
}
char whoStarts() {
  char start;
  printf("Do you want to start (y/n)?\n");
  scanf("%c", &start);
  if (start == 'y') return '2';
  return '1';
}
void addTile2(char** board, int col, char player) {
  // add the tile into the workspace-board
  int row = computeRow(board, col);
  board[row][col] = player;
}
void printLine(int len) {  // print a line of dashes of length 'len'
  for (int j = 0; j < len - 1; j++)
    printf("--");
  printf("-\n");
}
void printBoard(char** board) {
  for (int j = 0; j < NCOLS; j++)
    printf("-   ");
  printf("-\n");
  for (int i = 0; i < NROWS; i++) {
    for (int j = 0; j < NCOLS; j++) {
      printf("| ");
      if (board[i][j] == '0')
        printf("  ");
      else if (board[i][j] == '1') {
        printf("x ");
        // printf("\u25A0 ");
      } else {
        printf("\u25CF ");
      }
    }
    printf("|\n");
    printLine(2 * NCOLS + 1);
  }
  for (int i = 0; i < NCOLS; i++) printf("| %i ", i + 1);
  printf("|\n");
}
