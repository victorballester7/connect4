#include "../include/connect4.h"

#include "../include/evaluation.h"
#include "../include/minimax.h"
#include "../include/setup.h"

extern int colorPlayer, colorComputer;
int NROWS = 6;  // Number of rows of the board
int NCOLS = 7;  // Number of columns of the board
int LAST_CHOICE;
// extern int new_goodOne, new_one, new_zero, new_dsq, old_dsq, old_zero, old_one, old_goodOne;
// extern int v_new[730], v_old[730];

int v1[729] = {400, 10000, 300, 20000, 1000000, 10000, 200, 200, 200, 30000, 1000000, 20000, 2000000, 100000000, 1000000, 10000, 10000, 10000, 100, 100, 100, 100, 100, 100, 100, 100, 100, 30000, 30000, 30000, 1000000, 1000000, 1000000, 20000, 20000, 20000, 2000000, 2000000, 2000000, 100000000, 100000000, 100000000, 1000000, 1000000, 1000000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 100, 10000, -2500, 10000, 1000000, -2500, -2500, -2500, -2500, 10000, 1000000, -2500, 1000000, 100000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 20000, 30000, 20000, 30000, 1000000, 20000, 20000, 20000, 20000, 1000000, 2000000, 1000000, 2000000, 100000000, 1000000, 1000000, 1000000, 1000000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 100, 10000, -2500, 10000, 1000000, -2500, -2500, -2500, -2500, 10000, 1000000, -2500, 1000000, 100000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 200, 10000, 100, 20000, 1000000, 10000, -2500, -2500, -2500, 20000, 1000000, 10000, 2000000, 100000000, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 10000, 10000, 10000, 1000000, 1000000, 1000000, -2500, -2500, -2500, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 100, 10000, -2500, 10000, 1000000, -2500, -2500, -2500, -2500, 10000, 1000000, -2500, 1000000, 100000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 10000, 30000, 10000, 30000, 1000000, 20000, 10000, 10000, 10000, 30000, 1000000, 20000, 2000000, 100000000, 1000000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 1000000, 1000000, 1000000, 2000000, 2000000, 2000000, 1000000, 1000000, 1000000, 2000000, 2000000, 2000000, 100000000, 100000000, 100000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 100, 10000, -2500, 10000, 1000000, -2500, -2500, -2500, -2500, 10000, 1000000, -2500, 1000000, 100000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 1000000, 1000000, 1000000, 1000000, 2000000, 1000000, 1000000, 1000000, 1000000, 1000000, 2000000, 1000000, 2000000, 100000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100, 10000, -2500, 10000, 1000000, -2500, -2500, -2500, -2500, 10000, 1000000, -2500, 1000000, 100000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 200, 10000, 100, 20000, 1000000, 10000, -2500, -2500, -2500, 20000, 1000000, 10000, 2000000, 100000000, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 10000, 10000, 10000, 1000000, 1000000, 1000000, -2500, -2500, -2500, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 100, 10000, -2500, 10000, 1000000, -2500, -2500, -2500, -2500, 10000, 1000000, -2500, 1000000, 100000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 300, 10000, 200, 20000, 1000000, 10000, 100, 100, 100, 30000, 1000000, 20000, 2000000, 100000000, 1000000, 10000, 10000, 10000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 20000, 20000, 20000, 1000000, 1000000, 1000000, 10000, 10000, 10000, 2000000, 2000000, 2000000, 100000000, 100000000, 100000000, 1000000, 1000000, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 100, 10000, -2500, 10000, 1000000, -2500, -2500, -2500, -2500, 10000, 1000000, -2500, 1000000, 100000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 10000, 20000, 10000, 20000, 1000000, 10000, 10000, 10000, 10000, 1000000, 2000000, 1000000, 2000000, 100000000, 1000000, 1000000, 1000000, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 100, 10000, -2500, 10000, 1000000, -2500, -2500, -2500, -2500, 10000, 1000000, -2500, 1000000, 100000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 200, 10000, 100, 20000, 1000000, 10000, -2500, -2500, -2500, 20000, 1000000, 10000, 2000000, 100000000, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 10000, 10000, 10000, 1000000, 1000000, 1000000, -2500, -2500, -2500, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 100, 10000, -2500, 10000, 1000000, -2500, -2500, -2500, -2500, 10000, 1000000, -2500, 1000000, 100000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500};

int v2[729] = {400, 300, 10000, 200, 200, 200, 20000, 10000, 1000000, 100, 100, 100, 100, 100, 100, 100, 100, 100, 30000, 20000, 1000000, 10000, 10000, 10000, 2000000, 1000000, 100000000, 100, -2500, 10000, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, 1000000, -2500, 100000000, 30000, 30000, 30000, 20000, 20000, 20000, 1000000, 1000000, 1000000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 2000000, 2000000, 2000000, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, 200, 100, 10000, -2500, -2500, -2500, 20000, 10000, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 20000, 10000, 1000000, -2500, -2500, -2500, 2000000, 1000000, 100000000, 100, -2500, 10000, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, 1000000, -2500, 100000000, 10000, 10000, 10000, -2500, -2500, -2500, 1000000, 1000000, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 1000000, 1000000, 1000000, -2500, -2500, -2500, 100000000, 100000000, 100000000, 20000, 20000, 30000, 20000, 20000, 20000, 30000, 20000, 1000000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 1000000, 1000000, 2000000, 1000000, 1000000, 1000000, 2000000, 1000000, 100000000, 100, -2500, 10000, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, 1000000, -2500, 100000000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 300, 200, 10000, 100, 100, 100, 20000, 10000, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 30000, 20000, 1000000, 10000, 10000, 10000, 2000000, 1000000, 100000000, 100, -2500, 10000, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, 1000000, -2500, 100000000, 20000, 20000, 20000, 10000, 10000, 10000, 1000000, 1000000, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 2000000, 2000000, 2000000, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, 200, 100, 10000, -2500, -2500, -2500, 20000, 10000, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 20000, 10000, 1000000, -2500, -2500, -2500, 2000000, 1000000, 100000000, 100, -2500, 10000, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, 1000000, -2500, 100000000, 10000, 10000, 10000, -2500, -2500, -2500, 1000000, 1000000, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 1000000, 1000000, 1000000, -2500, -2500, -2500, 100000000, 100000000, 100000000, 10000, 10000, 20000, 10000, 10000, 10000, 20000, 10000, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 1000000, 1000000, 2000000, 1000000, 1000000, 1000000, 2000000, 1000000, 100000000, 100, -2500, 10000, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, 1000000, -2500, 100000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 10000, 10000, 30000, 10000, 10000, 10000, 30000, 20000, 1000000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 30000, 20000, 1000000, 10000, 10000, 10000, 2000000, 1000000, 100000000, 100, -2500, 10000, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, 1000000, -2500, 100000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 2000000, 2000000, 2000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 2000000, 2000000, 2000000, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, 200, 100, 10000, -2500, -2500, -2500, 20000, 10000, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 20000, 10000, 1000000, -2500, -2500, -2500, 2000000, 1000000, 100000000, 100, -2500, 10000, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, 1000000, -2500, 100000000, 10000, 10000, 10000, -2500, -2500, -2500, 1000000, 1000000, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 1000000, 1000000, 1000000, -2500, -2500, -2500, 100000000, 100000000, 100000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 2000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 2000000, 1000000, 1000000, 1000000, 2000000, 1000000, 100000000, 100, -2500, 10000, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, -2500, 10000, -2500, 1000000, -2500, -2500, -2500, 1000000, -2500, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000};

void addTile(char** board, int col, char player) {
  // add the tile into the workspace-board
  int row = computeRow(board, col);
  board[row][col] = player;

  // add the tile into the printed-board
  int color = (player == '1') ? colorComputer : colorPlayer;
  for (int i = 0; i < row; i++) {
    drawTile(i, col, color);
    usleep(ANIMATION_INTERVAL);
    drawTile(i, col, 8);
  }
  drawTile(row, col, color);
}

int computeNumChilds(char** board) {
  int count = 0, j = 0;
  while (j < NCOLS)
    if (board[0][j++] == '0') count++;
  // printf("NumChilds: %i\n", count);
  return count;
}

char* consecutiveN_S(char** board, int row, int col) {  // returns the 7 positions around the position board[row][col] in the North-South direction. Character '9' means that cell is out of the board.
  char* consec = malloc(7 * sizeof(char));
  char player = board[row][col];
  for (int i = row - 3, k = 0; k < 6; i++, k++) {
    if (i == row) {
      k--;
      continue;
    }
    consec[k] = (insideLimits(i, col)) ? board[i][col] : otherPlayer(player);  // if it is not inside the limits, assign the value of the other player (thought as a boundary of doing 4-in-a-row)
  }
  return consec;
}

char* consecutiveNE_SW(char** board, int row, int col) {  // returns the 7 positions around the position board[row][col] in the NorthWest-SouthEast direction. Character '9' means that cell is out of the board.
  char* consec = malloc(7 * sizeof(char));
  char player = board[row][col];
  for (int i = row - 3, j = col + 3, k = 0; k < 6; i++, j--, k++) {
    if (j == col) {
      k--;
      continue;
    }
    consec[k] = (insideLimits(i, j)) ? board[i][j] : otherPlayer(player);  // if it is not inside the limits, assign the value of the other player (thought as a boundary of doing 4-in-a-row)
  }
  return consec;
}

char* consecutiveNW_SE(char** board, int row, int col) {  // returns the 7 positions around the position board[row][col] in the NorthEast-SouthWest direction. Character '9' means that cell is out of the board.
  char* consec = malloc(7 * sizeof(char));
  char player = board[row][col];
  for (int i = row - 3, j = col - 3, k = 0; k < 6; i++, j++, k++) {
    if (j == col) {
      k--;
      continue;
    }
    consec[k] = (insideLimits(i, j)) ? board[i][j] : otherPlayer(player);  // if it is not inside the limits, assign the value of the other player (thought as a boundary of doing 4-in-a-row)
  }
  return consec;
}

char* consecutiveW_E(char** board, int row, int col) {  // returns the 7 positions around the position board[row][col] in the West-East direction. Character '9' means that cell is out of the board.
  char* consec = malloc(7 * sizeof(char));
  char player = board[row][col];
  for (int j = col - 3, k = 0; k < 6; j++, k++) {
    if (j == col) {
      k--;
      continue;
    }
    consec[k] = (insideLimits(row, j)) ? board[row][j] : otherPlayer(player);  // if it is not inside the limits, assign the value of the other player (thought as a boundary of doing 4-in-a-row)
  }
  return consec;
}

int evaluateString(char* str, char player) {
  if (str == NULL) return 0;
  // The numbers equal to INF means that there is a 4-in-a-row.
  int i = stringToBase3(str);
  if (player == '2') {
    // printf("evaluatestring: %i\n", v2[i]);
    return v2[i];
  }
  // printf("evaluatestring: %i\n", v1[i]);
  return v1[i];
}

char find4InRow(char** board, int* row, int* col) {
  char direction;
  int i;
  for (i = 0; i < 4; i++) {
    if (i == 0) {  // horizontal
      direction = 'h';
      char* h = consecutiveW_E(board, *row, *col);
      if (evaluateString(h, board[*row][*col]) == INF) {
        while (isSameTileOnTheLeft(board, *row, *col)) (*col)--;
        break;
      }
    } else if (i == 1) {  // vertical
      direction = 'v';
      char* v = consecutiveN_S(board, *row, *col);
      if (evaluateString(v, board[*row][*col]) == INF) break;
    } else if (i == 2) {  // NW - SE diagonal
      direction = 'd';
      char* d = consecutiveNW_SE(board, *row, *col);
      if (evaluateString(d, board[*row][*col]) == INF) {
        while (isSameTileInTheNW(board, *row, *col)) {
          (*row)--;
          (*col)--;
        }
        break;
      }
    } else {  // SW - NE diagonal
      direction = 'D';
      char* D = consecutiveNE_SW(board, *row, *col);
      if (evaluateString(D, board[*row][*col]) == INF) {
        while (isSameTileInTheSW(board, *row, *col)) {
          (*row)++;
          (*col)--;
        }
        break;
      }
    }
  }
  // At this point, *row and *col store the inital position of the 4-in-a-row and direction stores in which direction is made.
  return direction;
}

void getFirstLeftClosestZeroInGOODONE_VALUE(char** board, int direction, int* zeroRow, int* zeroCol) {
  int j = 1, row = *zeroRow, col = *zeroCol;
  // direction = 0 --> horizontal
  // direction = 1 --> vertical
  // direction = 2 --> NW - SE diagonal
  // direction = 3 --> SW - NE diagonal
  char player = board[row][col];
  char otherplayer = otherPlayer(player);
  char *h, *v, *d1, *d2;
  if (direction == 0) {
    while (insideLimits(row, col - j)) {
      if (board[row][col - j] == otherplayer)
        return;
      else if (board[row][col - j] == '0') {
        h = consecutiveW_E(board, row, col - j);
        if (evaluateString(h, player) != INF) return;
        *zeroRow = row;
        *zeroCol = col - j;
        return;
      }
      j++;
    }
  } else if (direction == 1) {
    while (insideLimits(row - j, col)) {
      if (board[row - j][col] == otherplayer)
        return;
      else if (board[row - j][col] == '0') {
        v = consecutiveN_S(board, row - j, col);
        if (evaluateString(v, player) != INF) return;
        *zeroRow = row - j;
        *zeroCol = col;
        return;
      }
      j++;
    }
  } else if (direction == 2) {
    while (insideLimits(row - j, col - j)) {
      if (board[row - j][col - j] == otherplayer)
        return;
      else if (board[row - j][col - j] == '0') {
        d1 = consecutiveNW_SE(board, row - j, col - j);
        if (evaluateString(d1, player) != INF) return;
        *zeroRow = row - j;
        *zeroCol = col - j;
        return;
      }
      j++;
    }
  } else if (direction == 3) {
    while (insideLimits(row + j, col - j)) {
      if (board[row + j][col - j] == otherplayer)
        return;
      else if (board[row + j][col - j] == '0') {
        d2 = consecutiveNE_SW(board, row + j, col - j);
        if (evaluateString(d2, player) != INF) return;
        *zeroRow = row + j;
        *zeroCol = col - j;
        return;
      }
      j++;
    }
  }
}

void getFirstRightClosestZeroInGOODONE_VALUE(char** board, int direction, int* zeroRow, int* zeroCol) {
  int j = 1, row = *zeroRow, col = *zeroCol;
  // direction = 0 --> horizontal
  // direction = 1 --> vertical
  // direction = 2 --> NW - SE diagonal
  // direction = 3 --> SW - NE diagonal
  char player = board[row][col];
  char otherplayer = otherPlayer(player);
  char *h, *v, *d1, *d2;
  if (direction == 0) {
    while (insideLimits(row, col + j)) {
      if (board[row][col + j] == otherplayer)
        return;
      else if (board[row][col + j] == '0') {
        h = consecutiveW_E(board, row, col + j);
        if (evaluateString(h, player) != INF) return;
        *zeroRow = row;
        *zeroCol = col + j;
        return;
      }
      j++;
    }
  } else if (direction == 1) {
    while (insideLimits(row + j, col)) {
      if (board[row + j][col] == otherplayer)
        return;
      else if (board[row + j][col] == '0') {
        v = consecutiveN_S(board, row + j, col);
        if (evaluateString(v, player) != INF) return;
        *zeroRow = row + j;
        *zeroCol = col;
        return;
      }
      j++;
    }
  } else if (direction == 2) {
    while (insideLimits(row + j, col + j)) {
      if (board[row + j][col + j] == otherplayer)
        return;
      else if (board[row + j][col + j] == '0') {
        d1 = consecutiveNW_SE(board, row + j, col + j);
        if (evaluateString(d1, player) != INF) return;
        *zeroRow = row + j;
        *zeroCol = col + j;
        return;
      }
      j++;
    }
  } else if (direction == 3) {
    while (insideLimits(row - j, col + j)) {
      if (board[row - j][col + j] == otherplayer)
        return;
      else if (board[row - j][col + j] == '0') {
        d2 = consecutiveNE_SW(board, row - j, col + j);
        if (evaluateString(d2, player) != INF) return;
        *zeroRow = row - j;
        *zeroCol = col + j;
        return;
      }
      j++;
    }
  }
}

int heuristicFunction(char** board, char currentPlayer) {
  char **strings = malloc(4 * sizeof(char*)), playerTile;
  int totalValue = 0, values[4];  // defenseMode: the higher, the more defensive is the computer.
  int zeroRow1, zeroRow2, zeroCol1, zeroCol2;
  for (int col = 0; col < NCOLS; col++) {
    for (int row = computeRow(board, col) + 1; row < NROWS; row++) {  // avoid cases where the last tile is empty.
      playerTile = board[row][col];

      strings[0] = consecutiveW_E(board, row, col);    // horizontal string
      strings[1] = consecutiveN_S(board, row, col);    // vertical string
      strings[2] = consecutiveNW_SE(board, row, col);  // first diagonal string
      strings[3] = consecutiveNE_SW(board, row, col);  // second diagonal string

      if (playerTile == '1')
        for (int i = 0; i < 4; i++) values[i] = evaluateString(strings[i], '1');
      else  // playerTile == '2'
        for (int i = 0; i < 4; i++) values[i] = evaluateString(strings[i], '2');

      // Here we will distinguish the killing doubles (example 1: there is a doubleand you have nothing to do) and the avoidable doubles (example 2: there is a double but the match isn't done yet)
      // Examples:
      // 1                                2
      // |   |   |   |   |   |            |   |   |   |   |   |
      // |   |   | o | o |   |            |   | x | x | x |   |
      // |   | x | x | x |   |            |   | o | x | o |   |
      for (int i = 0; i < 4; i++) {
        zeroRow1 = row;  // row of the first zero in the doubles
        zeroRow2 = row;  // row of the second zero in the doubles
        zeroCol1 = col;  // column of the first zero in the doubles
        zeroCol2 = col;  // column of the second zero in the doubles
        if (values[i] == 2 * GOODONE_VALUE) {
          getFirstLeftClosestZeroInGOODONE_VALUE(board, i, &zeroRow1, &zeroCol1);
          getFirstRightClosestZeroInGOODONE_VALUE(board, i, &zeroRow2, &zeroCol2);
          if (!((insideLimits(zeroRow1 + 1, zeroCol1) && board[zeroRow1 + 1][zeroCol1] == '0') || (insideLimits(zeroRow2 + 1, zeroCol2) && board[zeroRow2 + 1][zeroCol2] == '0')))
            values[i] = INF;
        } else if (values[i] == GOODONE_VALUE) {
          getFirstLeftClosestZeroInGOODONE_VALUE(board, i, &zeroRow1, &zeroCol1);
          if (zeroRow1 == row && zeroCol1 == col)
            getFirstRightClosestZeroInGOODONE_VALUE(board, i, &zeroRow1, &zeroCol1);
          // Now, zeroRow1 and zeroCol1 contain the position of the 0 avoiding the 4-in-a-row.
          if (!(insideLimits(zeroRow1 + 1, zeroCol1) && board[zeroRow1 + 1][zeroCol1] == '0') && playerTile != currentPlayer)
            values[i] = INF;
        }
      }
      if (playerTile == '1')  // computer
        totalValue += sum(values, 4);
      else if (playerTile == '2')  // if board[row][col] == '2' // player
        totalValue -= sum(values, 4);
      // for (int i = 0; i < 4; i++) printf("position: (%i,%i)value %i: %i\n", row, col, i, values[i]);
      // if (playerTile == '1')  // computer
      //   printf("value intermezzo: %i\n", sum(values, 4));
      // else
      //   printf("value intermezzo: %i\n", -sum(values, 4));
    }
  }
  free(strings);
  // printf("Heuristic function: %i\n", totalValue);
  return totalValue;
}

// int heuristicFunction(char** board, char currentPlayer) {
//   char **strings = malloc(4 * sizeof(char*)), playerTile;
//   int totalValue = 0, values[4];  // defenseMode: the higher, the more defensive is the computer.
//   int zeroRow1, zeroRow2, zeroCol1, zeroCol2;
//   for (int col = 0; col < NCOLS; col++) {
//     for (int row = computeRow(board, col) + 1; row < NROWS; row++) {  // avoid cases where the last tile is empty.
//       playerTile = board[row][col];

//       // for (int i = 0; i < 4; i++) {
//       //   // we investigate the neighbourhood of the tile in [row,col]. If we do obtain a '0' or the same tile as playerTile, we omit extracting the string, because it is irrelevant for the global mark.
//       //   // i = 2 | i = 1  | x
//       //   // --------------------
//       //   // i = 0 | playerTile | x
//       //   // --------------------
//       //   // i = 3 |   x    | x
//       //   switch (i) {
//       //     case 0:
//       //       if (isSameTileOnTheLeft(board, row, col))
//       //         strings[0] = NULL;
//       //       else
//       //         strings[0] = consecutiveW_E(board, row, col);  // horizontal string
//       //       break;
//       //     case 1:
//       //       if (isSameTileAbove(board, row, col)) {
//       //         // printf("I'm here TOP\n");
//       //         strings[1] = NULL;
//       //       } else
//       //         strings[1] = consecutiveN_S(board, row, col);  // vertical string
//       //       break;
//       //     case 2:
//       //       if (isSameTileInTheNW(board, row, col))
//       //         strings[2] = NULL;
//       //       else
//       //         strings[2] = consecutiveNW_SE(board, row, col);  // first diagonal string
//       //       break;
//       //     case 3:
//       //       if (isSameTileInTheSW(board, row, col))
//       //         strings[3] = NULL;
//       //       else
//       //         strings[3] = consecutiveNE_SW(board, row, col);  // second diagonal string
//       //       break;
//       //     default:
//       //       break;
//       //   }
//       // }
//       strings[0] = consecutiveW_E(board, row, col);    // horizontal string
//       strings[1] = consecutiveN_S(board, row, col);    // vertical string
//       strings[2] = consecutiveNW_SE(board, row, col);  // first diagonal string
//       strings[3] = consecutiveNE_SW(board, row, col);  // second diagonal string

//       if (playerTile == '1')
//         for (int i = 0; i < 4; i++) values[i] = evaluateString(strings[i], '1');
//       else  // playerTile == '2'
//         for (int i = 0; i < 4; i++) values[i] = evaluateString(strings[i], '2');

//       // Here we will distinguish the killing doubles (example 1: there is a doubleand you have nothing to do) and the avoidable doubles (example 2: there is a double but the match isn't done yet)
//       // Examples:
//       // 1                                2
//       // |   |   |   |   |   |            |   |   |   |   |   |
//       // |   |   | o | o |   |            |   | x | x | x |   |
//       // |   | x | x | x |   |            |   | o | x | o |   |
//       for (int i = 0; i < 4; i++) {
//         zeroRow1 = row;  // row of the first zero in the doubles
//         zeroRow2 = row;  // row of the second zero in the doubles
//         zeroCol1 = col;  // column of the first zero in the doubles
//         zeroCol2 = col;  // column of the second zero in the doubles
//         if (values[i] == 2 * GOODONE_VALUE) {
//           getFirstLeftClosestZeroInGOODONE_VALUE(board, i, &zeroRow1, &zeroCol1);
//           getFirstRightClosestZeroInGOODONE_VALUE(board, i, &zeroRow2, &zeroCol2);
//           if (!((insideLimits(zeroRow1 + 1, zeroCol1) && board[zeroRow1 + 1][zeroCol1] == '0') || (insideLimits(zeroRow2 + 1, zeroCol2) && board[zeroRow2 + 1][zeroCol2] == '0')))
//             values[i] = INF;
//         } else if (values[i] == GOODONE_VALUE) {
//           getFirstLeftClosestZeroInGOODONE_VALUE(board, i, &zeroRow1, &zeroCol1);
//           if (zeroRow1 == row && zeroCol1 == col)
//             getFirstRightClosestZeroInGOODONE_VALUE(board, i, &zeroRow1, &zeroCol1);
//           // Now, zeroRow1 and zeroCol1 contain the position of the 0 avoiding the 4-in-a-row.
//           if (!(insideLimits(zeroRow1 + 1, zeroCol1) && board[zeroRow1 + 1][zeroCol1] == '0') && playerTile != currentPlayer)
//             values[i] = INF;
//         }
//       }
//       // if (board[row][col] == '1')  // computer
//       //   totalValue += (evaluateString(h, '1') + evaluateString(v, '1') + evaluateString(d1, '1') + evaluateString(d2, '1'));
//       // else  // if board[row][col] == '2' // player
//       //   totalValue -= defenseMode * (evaluateString(h, '2') + evaluateString(v, '2') + evaluateString(d1, '2') + evaluateString(d2, '2'));
//       // printf("player: %c\n", player_comp);
//       // printf("h = %s\nv = %s\nd1 = %s\nd2 = %s\n", h, v, d1, d2);
//       if (playerTile == '1')  // computer
//         totalValue += sum(values, 4);
//       else if (playerTile == '2')  // if board[row][col] == '2' // player
//         totalValue -= sum(values, 4);
//       // for (int i = 0; i < 4; i++) printf("value %i: %i\n", i, values[i]);
//       // if (playerTile == '1')  // computer
//       //   printf("value intermezzo: %i\n", sum(values, 4));
//       // else
//       //   printf("value intermezzo: %i\n", -sum(values, 4));
//     }
//   }
//   free(strings);
//   // printf("Heuristic function: %i\n", totalValue);
//   return totalValue;
// }

int insideLimits(int row, int col) {  // Returns 0 if, the position (row, col) is outside limits of the board and 1 otherwise
  return (row < 0 || row >= NROWS || col < 0 || col >= NCOLS) ? 0 : 1;
}

int is4InRow(char** board, int col) {  // check whether there was 4-in-a-row or not in the last move in the column 'col'. Return 1 if there was 4-in-a-row. Return 0 otherwise.
  // printf("-----4-in-a-row---------\n");
  int row = computeRow(board, col) + 1;
  char *h, *v, *d1, *d2;
  h = consecutiveW_E(board, row, col);
  if (evaluateString(h, board[row][col]) == INF)
    return 1;
  v = consecutiveN_S(board, row, col);
  if (evaluateString(v, board[row][col]) == INF)
    return 1;
  d1 = consecutiveNW_SE(board, row, col);
  if (evaluateString(d1, board[row][col]) == INF)
    return 1;
  d2 = consecutiveNE_SW(board, row, col);
  if (evaluateString(d2, board[row][col]) == INF)
    return 1;
  return 0;
  // char* h = consecutiveW_E(board, row, col);
  // char* v = consecutiveN_S(board, row, col);
  // char* d1 = consecutiveNW_SE(board, row, col);
  // char* d2 = consecutiveNE_SW(board, row, col);
  // // printf("\n%s %s %s %s\n", h, v, d1, d2);
  // return (evaluateString(h, board[row][col]) == INF || evaluateString(v, board[row][col]) == INF || evaluateString(d1, board[row][col]) == INF || evaluateString(d2, board[row][col]) == INF) ? 1 : 0;
}

int isFull(char** board) {
  return (computeNumChilds(board) == 0) ? 1 : 0;
}

int isSameTileInTheNW(char** board, int row, int col) {
  char player = board[row][col];
  return (insideLimits(row - 1, col - 1) && board[row - 1][col - 1] == player) ? 1 : 0;
}

int isSameTileInTheSW(char** board, int row, int col) {
  char player = board[row][col];
  return (insideLimits(row + 1, col - 1) && board[row + 1][col - 1] == player) ? 1 : 0;
}

int isSameTileAbove(char** board, int row, int col) {
  char player = board[row][col];
  return (insideLimits(row - 1, col) && board[row - 1][col] == player) ? 1 : 0;
}

int isSameTileOnTheLeft(char** board, int row, int col) {
  char player = board[row][col];
  return (insideLimits(row, col - 1) && board[row][col - 1] == player) ? 1 : 0;
}

char otherPlayer(char player) {
  return (player == '1') ? '2' : '1';
}

char playGame() {  // do the match. Returns if there is a draw, 1 if the computer wins and 2 if the player wins.
  clear();
  refresh();

  char** board = (char**)malloc(NROWS * sizeof(char*));
  for (int i = 0; i < NROWS; i++) {
    board[i] = (char*)malloc(NCOLS * sizeof(char));
    memset(board[i], '0', NCOLS);
  }
  int choice, startCol = 0, startRow = 0;  // startCol is the number of the col where we have done the 4-in-a-Row (if we did). And same with startRow.
  char lastPlayer = '2', winner = '0', direction = '0';

  lastPlayer = (movementMenu(NULL, menuWhoStarts, 0) == 1) ? '2' : '1';
  drawBoard();
  clearLine(2);  // If not clear it, a "No" appears there.
  LAST_CHOICE = NCOLS / 2 + 1;
  while (!isFull(board)) {
    clearFirst3Lines();
    if (lastPlayer == '2') {  // player's turn
      mvprintw(0, 0, "Where do you want to play? Use arrow keys to go left and right. Press enter to select a choice.");
      refresh();
      choice = movementMenu(NULL, menuTilesReadyToPlay, 1);
      LAST_CHOICE = choice;
      choice--;
    } else {  // computer's turn
      mvprintw(0, 0, "The AI is thinking...");
      refresh();
      choice = computerPlay(board);
    }
    if (choice < 0 || choice >= NCOLS || board[0][choice] != '0') {
      attron(COLOR_PAIR(9));
      mvprintw(LINES - 1, 0, "The column enter is not valid! Play again.\n");
      attroff(COLOR_PAIR(9));
      continue;
    }
    addTile(board, choice, lastPlayer);
    if (is4InRow(board, choice)) {
      clearFirst3Lines();
      refresh();
      winner = lastPlayer;
      startCol = choice;
      startRow = computeRow(board, startCol) + 1;
      direction = find4InRow(board, &startRow, &startCol);
      break;
    }
    lastPlayer = otherPlayer(lastPlayer);
  }
  for (int i = 0; i < NROWS; i++) free(board[i]);
  free(board);
  return endOfMatch(winner, startRow, startCol, direction);
}

int stringToBase3(char* str) {  // Convert a string of numbers in the set {0,1,2} to a number in base 3. Also to optimize the function assume strlen(str) = 6.
  int len = 6, base3 = 0, v[6] = {1, 3, 9, 27, 81, 243};
  for (int i = 0; i < len; i++)
    base3 += (str[i] - 48) * v[len - 1 - i];
  free(str);
  return base3;
}

int sum(int v[], size_t n) {
  int sum = 0;
  for (int i = 0; i < n; i++) sum += v[i];
  return sum;
}
