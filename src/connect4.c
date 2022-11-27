#include "../include/connect4.h"

#include "../include/evaluation.h"
#include "../include/minimax.h"
#include "../include/setup.h"

char player_comp = '1';
extern int new_goodOne, new_one, new_zero, new_dsq, old_dsq, old_zero, old_one, old_goodOne;
extern int v_new[730], v_old[730];

extern int colorPlayer, colorComputer;

char playGame2(int match) {  // do the match. Returns if there is a draw, 1 if the computer wins and 2 if the player wins.
  // int i= presentation();
  char board[NROWS][NCOLS];
  memset(board, '0', NCOLS * NROWS);
  int choice;
  char lastPlayer;
  // int len = nProduct(NCOLS, DEPTH), v[len];
  // memset(v, 0, len);
  if (match == 0) {  // player vs computer
    lastPlayer = whoStarts();
    clean();
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
      addTile(board, choice, lastPlayer);
      // clean();
      if (is4InRow(board, choice)) {
        printBoard(board);
        return lastPlayer;
      }
      lastPlayer = otherPlayer(lastPlayer);
    }
  } else {  // computer vs computer
    while (!isFull(board)) {
      choice = computerPlay(board);
      if (choice < 0 || choice >= NCOLS || board[0][choice] != '0') {
        printf("The column enter is not valid! Play again.\n");
        continue;
      }
      addTile(board, choice, player_comp);
      // printf("Final move:\n");
      // printBoard(board);
      if (is4InRow(board, choice)) return player_comp;
      player_comp = otherPlayer(player_comp);
    }
    return '0';
  }
  return '0';
}

char playGame() {  // do the match. Returns if there is a draw, 1 if the computer wins and 2 if the player wins.
  clear();
  refresh();

  char board[NROWS][NCOLS];
  memset(board, '0', NCOLS * NROWS);
  int choice, startCol = 0, startRow = 0;  // startCol is the number of the col where we have done the 4-in-a-Row (if we did). And same with startRow.
  char lastPlayer = '2', winner = '0', direction = '0';

  lastPlayer = (movementMenu(NULL, printWhoStarts) == 1) ? '2' : '1';
  drawBoard();
  while (!isFull(board)) {
    if (lastPlayer == '2') {  // player's turn
      clearFirstLines(2);
      mvprintw(0, 0, "Where do you want to play? Use arrow keys to go left and right. Press enter to select a choice.");
      refresh();
      choice = movementMenu(NULL, printTilesReadyToPlay);
      choice--;
    } else {  // computer's turn
      clearFirstLines(2);
      mvprintw(0, 0, "The AI is thinking...");
      refresh();
      choice = computerPlay(board);
    }
    if (choice < 0 || choice >= NCOLS || board[0][choice] != '0') {
      printf("The column enter is not valid! Play again.\n");
      continue;
    }
    addTile(board, choice, lastPlayer);
    if (is4InRow(board, choice)) {
      clearFirstLines(2);
      refresh();
      winner = lastPlayer;
      startCol = choice;
      startRow = computeRow(board, startCol) + 1;
      direction = find4InRow(board, &startRow, &startCol);
      break;
    }
    lastPlayer = otherPlayer(lastPlayer);
  }

  return endOfGame(winner, startRow, startCol, direction);
}

char otherPlayer(char player) {
  return (player == '1') ? '2' : '1';
}

int computeNumChilds(char board[NROWS][NCOLS]) {
  int count = 0, j = 0;
  while (j < NCOLS)
    if (board[0][j++] == '0') count++;
  // printf("NumChilds: %i\n", count);
  return count;
}

int isFull(char board[NROWS][NCOLS]) {
  return (computeNumChilds(board) == 0) ? 1 : 0;
}

char whoStarts() {
  char start;
  printf("Do you want to start (y/n)?\n");
  scanf("%c", &start);
  if (start == 'y') return '2';
  return '1';
}

void addTile(char board[NROWS][NCOLS], int col, char player) {
  // add the tile into the workspace-board
  int row = computeRow(board, col);
  board[row][col] = player;

  // add the tile into the printed-board
  int color = (player == '1') ? colorComputer : colorPlayer;
  drawTile(row, col, color);
}

void printLine(int len) {  // print a line of dashes of length 'len'
  for (int j = 0; j < len - 1; j++)
    printf("--");
  printf("-\n");
}

// void printBoard(char board[NROWS][NCOLS]) {
//   attron(COLOR_PAIR(3));
//   for (int j = 0; j < NCOLS; j++)
//     printw("-   ");
//   printw("-\n");
//   for (int i = 0; i < NROWS; i++) {
//     for (int j = 0; j < NCOLS; j++) {
//       attron(COLOR_PAIR(3));
//       printw("| ");
//       if (board[i][j] == '0')
//         printw("  ");
//       else if (board[i][j] == '1') {
//         attron(COLOR_PAIR(1));
//         printw("\u25A0 ");
//       } else {
//         attron(COLOR_PAIR(2));
//         printw("\u25CF ");
//       }
//     }
//     attron(COLOR_PAIR(3));
//     printw("|\n");
//     printLine(2 * NCOLS + 1);
//   }
//   for (int i = 0; i < NCOLS; i++) printf("| %i ", i + 1);
//   printf("|\n");
//   // for (int i = 0; i < NCOLS; i++) printf("--%i-", i + 1);
//   // printf("-\n");
//   refresh();

//   // getch();

//   endwin();
// }

void printBoard(char board[NROWS][NCOLS]) {
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
  // for (int i = 0; i < NCOLS; i++) printf("--%i-", i + 1);
  // printf("-\n");
  refresh();

  // getch();

  endwin();
}

void clean() {
  system("clear");
}

int sum(int v[], size_t n) {
  int sum = 0;
  for (int i = 0; i < n; i++) sum += v[i];
  return sum;
}

int isSameTileOnTheLeft(char board[NROWS][NCOLS], int row, int col) {
  char player = board[row][col];
  return (insideLimits(row, col - 1) && board[row][col - 1] == player) ? 1 : 0;
}

int isSameTileAbove(char board[NROWS][NCOLS], int row, int col) {
  char player = board[row][col];
  return (insideLimits(row - 1, col) && board[row - 1][col] == player) ? 1 : 0;
}

int isSameTileInTheNW(char board[NROWS][NCOLS], int row, int col) {
  char player = board[row][col];
  return (insideLimits(row - 1, col - 1) && board[row - 1][col - 1] == player) ? 1 : 0;
}

int isSameTileInTheSW(char board[NROWS][NCOLS], int row, int col) {
  char player = board[row][col];
  return (insideLimits(row + 1, col - 1) && board[row + 1][col - 1] == player) ? 1 : 0;
}

int heuristicFunction(char board[NROWS][NCOLS]) {
  char **strings = malloc(4 * sizeof(char*)), player;
  int totalValue = 0, values[4];  // defenseMode: the higher, the more defensive is the computer.
  int zeroRow1, zeroRow2, zeroCol1, zeroCol2, j;
  for (int col = 0; col < NCOLS; col++) {
    for (int row = computeRow(board, col) + 1; row < NROWS; row++) {  // avoid cases where the last tile is empty.
      player = board[row][col];

      for (int i = 0; i < 4; i++) {
        // we investigate the neighbourhood of the tile in [row,col]. If we do obtain a '0' or the same tile as player, we omit extracting the string, because it is irrelevant for the global mark.
        // i = 2 | i = 1  | x
        // --------------------
        // i = 0 | player | x
        // --------------------
        // i = 3 |   x    | x
        switch (i) {
          case 0:
            if (isSameTileOnTheLeft(board, row, col))
              strings[0] = NULL;
            else
              strings[0] = consecutiveW_E(board, row, col);  // horizontal string
            break;
          case 1:
            if (isSameTileAbove(board, row, col)) {
              // printf("I'm here TOP\n");
              strings[1] = NULL;
            } else
              strings[1] = consecutiveN_S(board, row, col);  // vertical string
            break;
          case 2:
            if (isSameTileInTheNW(board, row, col))
              strings[2] = NULL;
            else
              strings[2] = consecutiveNW_SE(board, row, col);  // first diagonal string
            break;
          case 3:
            if (isSameTileInTheSW(board, row, col))
              strings[3] = NULL;
            else
              strings[3] = consecutiveNE_SW(board, row, col);  // second diagonal string
            break;
          default:
            break;
        }
      }

      if (player == '1')
        for (int i = 0; i < 4; i++) values[i] = evaluateString(strings[i], '1');
      else  // player == '2'
        for (int i = 0; i < 4; i++) values[i] = evaluateString(strings[i], '2');

      zeroRow1 = row;
      zeroRow2 = row;
      zeroCol1 = col;
      zeroCol2 = col;
      for (int i = 0; i < 4; i++) {
        if (values[i] == 2 * GOODONE_VALUE) {
          // Here we distinguish the killing doubles (example 1: there is a doubleand you have nothing to do) and the avoidable doubles (example 2: there is a double but the match isn't done yet)
          // Examples:
          // 1                                2
          // |   |   |   |   |   |            |   |   |   |   |   |
          // |   |   | o | o |   |            |   | x | x | x |   |
          // |   | x | x | x |   |            |   | o | x | o |   |
          j = 1;
          switch (i) {
            case 0:
              while (board[row][col - j] != '0') j++;
              zeroRow1 = row;
              zeroCol1 = col - j;
              j = 1;
              while (board[row][col + j] != '0') j++;
              zeroRow1 = row;
              zeroCol2 = col + j;
              break;
            case 2:
              while (board[row - j][col - j] != '0') j++;
              zeroRow1 = row - j;
              zeroCol1 = col - j;
              j = 1;
              while (board[row + j][col + j] != '0') j++;
              zeroRow2 = row + j;
              zeroCol2 = col + j;
              break;
            case 3:
              while (board[row + j][col - j] != '0') j++;
              zeroRow1 = row + j;
              zeroCol1 = col - j;
              j = 1;
              while (board[row - j][col + j] != '0') j++;
              zeroRow2 = row - j;
              zeroCol2 = col + j;
              break;
            default:  // there cannot be vertical doubles (i.e. for i = 1)
              break;
          }
          if (!(insideLimits(zeroRow1 + 1, zeroCol1) && board[zeroRow1 + 1][zeroCol1] == '0' && insideLimits(zeroRow2 + 1, zeroCol2) && board[zeroRow2 + 1][zeroCol2] == '0'))
            values[i] = INF;
        }
      }
      // if (board[row][col] == '1')  // computer
      //   totalValue += (evaluateString(h, '1') + evaluateString(v, '1') + evaluateString(d1, '1') + evaluateString(d2, '1'));
      // else  // if board[row][col] == '2' // player
      //   totalValue -= defenseMode * (evaluateString(h, '2') + evaluateString(v, '2') + evaluateString(d1, '2') + evaluateString(d2, '2'));
      // printf("player: %c\n", player_comp);
      // printf("h = %s\nv = %s\nd1 = %s\nd2 = %s\n", h, v, d1, d2);
      if (player == '1' && player_comp == '1')  // computer
        totalValue += sum(values, 4);
      else if (player == '2' && player_comp == '1')  // if board[row][col] == '2' // player
        totalValue -= sum(values, 4);
      else if (player == '1' && player_comp == '2')  // computer
        totalValue -= sum(values, 4);
      else if (player == '2' && player_comp == '2')  // if board[row][col] == '2' // player
        totalValue += sum(values, 4);
      // for (int i = 0; i < 4; i++) printf("value %i: %i\n", i, values[i]);
      // if (player == '1')  // computer
      //   printf("value intermezzo: %i\n", sum(values, 4));
      // else
      //   printf("value intermezzo: -%i\n", sum(values, 4));
    }
  }
  free(strings);
  // printf("Heuristic function: %i\n", totalValue);
  return totalValue;
}

// int heuristicFunction(char board[NROWS][NCOLS]) {
//   int row;
//   char *h, *v, *d1, *d2;
//   int totalValue = 0, defenseMode = 1;  // defenseMode: the higher, the more defensive is the computer.
//   int count = 0;
//   for (int col = 0; col < NCOLS; col++) {
//     if ((row = computeRow(board, col) + 1) >= NROWS) continue;  // avoid cases where the last tile is empty.
//     h = consecutiveW_E(board, row, col);
//     v = consecutiveN_S(board, row, col);
//     d1 = consecutiveNW_SE(board, row, col);
//     d2 = consecutiveNE_SW(board, row, col);
//     // if (board[row][col] == '1')  // computer
//     //   totalValue += (evaluateString(h, '1') + evaluateString(v, '1') + evaluateString(d1, '1') + evaluateString(d2, '1'));
//     // else  // if board[row][col] == '2' // player
//     //   totalValue -= defenseMode * (evaluateString(h, '2') + evaluateString(v, '2') + evaluateString(d1, '2') + evaluateString(d2, '2'));
//     // printf("player: %c\n", player_comp);
//     // printf("h = %s\nv = %s\nd1 = %s\nd2 = %s\n", h, v, d1, d2);
//     if (board[row][col] == '1' && player_comp == '1')  // computer
//       totalValue += (evaluateString(h, '1') + evaluateString(v, '1') + evaluateString(d1, '1') + evaluateString(d2, '1'));
//     else if (board[row][col] == '2' && player_comp == '1')  // if board[row][col] == '2' // player
//       totalValue -= defenseMode * (evaluateString(h, '2') + evaluateString(v, '2') + evaluateString(d1, '2') + evaluateString(d2, '2'));
//     else if (board[row][col] == '1' && player_comp == '2')  // computer
//       totalValue -= (evaluateString(h, '1') + evaluateString(v, '1') + evaluateString(d1, '1') + evaluateString(d2, '1'));
//     else if (board[row][col] == '2' && player_comp == '2')  // if board[row][col] == '2' // player
//       totalValue += defenseMode * (evaluateString(h, '2') + evaluateString(v, '2') + evaluateString(d1, '2') + evaluateString(d2, '2'));
//     count++;
//   }
//   // printf("\n%i\n", totalValue / count);
//   return totalValue / count;
// }

int stringToBase3(char* str) {  // Convert a string of numbers in the set {0,1,2} to a number in base 3. Also to optimize the function assume strlen(str) = 6.
  int len = 6, base3 = 0, v[6] = {1, 3, 9, 27, 81, 243};
  for (int i = 0; i < len; i++)
    base3 += (str[i] - 48) * v[len - 1 - i];
  // printf("%s: ", str);
  free(str);
  str = NULL;
  return base3;
}

char* exchangeOnesAndTwos(char* str) {  // exchange the '1' with '2' in the string 'str' and viceversa.
  int len = strlen(str);
  // printf("exchangeOnesTwos=%s ", str);
  for (int i = 0; i < len; i++)
    str[i] = (str[i] == '1') ? '2' : ((str[i] == '2') ? '1' : '0');
  // printf("%s\n", str);
  return str;
}

// char* removeCenterChar(char* str) {
//   int len = strlen(str);  // assume len is odd.
//   char* newStr = malloc(len * sizeof(char));
//   for (int i = 0; i < (len - 1) / 2; i++) newStr[i] = str[i];
//   for (int i = (len + 1) / 2; i < len; i++) newStr[i - 1] = str[i];
//   // printf("%s: ", str);
//   free(str);
//   str = NULL;
//   return newStr;
// }

int evaluateString(char* str, char player) {
  if (str == NULL) return 0;
  // The numbers equal to 10000 mean that there is a 4-in-a-row.
  // int v1[729] = {4, 16, 3, 18, 80, 16, 2, 2, 2, 20, 80, 18, 90, 10000, 80, 16, 16, 16, 1, 1, 1, 1, 1, 1, 1, 1, 1, 20, 20, 20, 80, 80, 80, 18, 18, 18, 90, 90, 90, 10000, 10000, 10000, 80, 80, 80, 16, 16, 16, 16, 16, 16, 16, 16, 16, 1, 16, -10, 16, 80, -10, -10, -10, -10, 16, 80, -10, 80, 10000, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 18, 20, 18, 20, 80, 18, 18, 18, 18, 80, 90, 80, 90, 10000, 80, 80, 80, 80, 16, 16, 16, 16, 16, 16, 16, 16, 16, 90, 90, 90, 90, 90, 90, 90, 90, 90, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 80, 80, 80, 80, 80, 80, 80, 80, 80, 1, 16, -10, 16, 80, -10, -10, -10, -10, 16, 80, -10, 80, 10000, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 2, 16, 1, 18, 80, 16, -10, -10, -10, 18, 80, 16, 90, 10000, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 16, 16, 16, 80, 80, 80, -10, -10, -10, 80, 80, 80, 10000, 10000, 10000, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 1, 16, -10, 16, 80, -10, -10, -10, -10, 16, 80, -10, 80, 10000, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 16, 20, 16, 20, 80, 18, 16, 16, 16, 20, 80, 18, 90, 10000, 80, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 80, 80, 80, 90, 90, 90, 80, 80, 80, 90, 90, 90, 10000, 10000, 10000, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 1, 16, -10, 16, 80, -10, -10, -10, -10, 16, 80, -10, 80, 10000, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 80, 80, 80, 80, 90, 80, 80, 80, 80, 80, 90, 80, 90, 10000, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 1, 16, -10, 16, 80, -10, -10, -10, -10, 16, 80, -10, 80, 10000, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 2, 16, 1, 18, 80, 16, -10, -10, -10, 18, 80, 16, 90, 10000, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 16, 16, 16, 80, 80, 80, -10, -10, -10, 80, 80, 80, 10000, 10000, 10000, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 1, 16, -10, 16, 80, -10, -10, -10, -10, 16, 80, -10, 80, 10000, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 3, 16, 2, 18, 80, 16, 1, 1, 1, 20, 80, 18, 90, 10000, 80, 16, 16, 16, -10, -10, -10, -10, -10, -10, -10, -10, -10, 18, 18, 18, 80, 80, 80, 16, 16, 16, 90, 90, 90, 10000, 10000, 10000, 80, 80, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 1, 16, -10, 16, 80, -10, -10, -10, -10, 16, 80, -10, 80, 10000, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 16, 18, 16, 18, 80, 16, 16, 16, 16, 80, 90, 80, 90, 10000, 80, 80, 80, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 80, 80, 80, 80, 80, 80, 80, 80, 80, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, -10, -10, -10, -10, -10, -10, -10, -10, -10, 1, 16, -10, 16, 80, -10, -10, -10, -10, 16, 80, -10, 80, 10000, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 2, 16, 1, 18, 80, 16, -10, -10, -10, 18, 80, 16, 90, 10000, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 16, 16, 16, 80, 80, 80, -10, -10, -10, 80, 80, 80, 10000, 10000, 10000, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, 1, 16, -10, 16, 80, -10, -10, -10, -10, 16, 80, -10, 80, 10000, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10};

  // int v2[729] = {4, 3, 16, 2, 2, 2, 18, 16, 80, 1, 1, 1, 1, 1, 1, 1, 1, 1, 20, 18, 80, 16, 16, 16, 90, 80, 10000, 1, -10, 16, -10, -10, -10, 16, -10, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 16, -10, 80, -10, -10, -10, 80, -10, 10000, 20, 20, 20, 18, 18, 18, 80, 80, 80, 16, 16, 16, 16, 16, 16, 16, 16, 16, 90, 90, 90, 80, 80, 80, 10000, 10000, 10000, 2, 1, 16, -10, -10, -10, 18, 16, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 18, 16, 80, -10, -10, -10, 90, 80, 10000, 1, -10, 16, -10, -10, -10, 16, -10, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 16, -10, 80, -10, -10, -10, 80, -10, 10000, 16, 16, 16, -10, -10, -10, 80, 80, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 80, 80, 80, -10, -10, -10, 10000, 10000, 10000, 18, 18, 20, 18, 18, 18, 20, 18, 80, 16, 16, 16, 16, 16, 16, 16, 16, 16, 80, 80, 90, 80, 80, 80, 90, 80, 10000, 1, -10, 16, -10, -10, -10, 16, -10, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 16, -10, 80, -10, -10, -10, 80, -10, 10000, 90, 90, 90, 90, 90, 90, 90, 90, 90, 80, 80, 80, 80, 80, 80, 80, 80, 80, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 3, 2, 16, 1, 1, 1, 18, 16, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 20, 18, 80, 16, 16, 16, 90, 80, 10000, 1, -10, 16, -10, -10, -10, 16, -10, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 16, -10, 80, -10, -10, -10, 80, -10, 10000, 18, 18, 18, 16, 16, 16, 80, 80, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 90, 90, 90, 80, 80, 80, 10000, 10000, 10000, 2, 1, 16, -10, -10, -10, 18, 16, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 18, 16, 80, -10, -10, -10, 90, 80, 10000, 1, -10, 16, -10, -10, -10, 16, -10, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 16, -10, 80, -10, -10, -10, 80, -10, 10000, 16, 16, 16, -10, -10, -10, 80, 80, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 80, 80, 80, -10, -10, -10, 10000, 10000, 10000, 16, 16, 18, 16, 16, 16, 18, 16, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 80, 80, 90, 80, 80, 80, 90, 80, 10000, 1, -10, 16, -10, -10, -10, 16, -10, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 16, -10, 80, -10, -10, -10, 80, -10, 10000, 80, 80, 80, 80, 80, 80, 80, 80, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 16, 16, 20, 16, 16, 16, 20, 18, 80, 16, 16, 16, 16, 16, 16, 16, 16, 16, 20, 18, 80, 16, 16, 16, 90, 80, 10000, 1, -10, 16, -10, -10, -10, 16, -10, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 16, -10, 80, -10, -10, -10, 80, -10, 10000, 80, 80, 80, 80, 80, 80, 90, 90, 90, 80, 80, 80, 80, 80, 80, 80, 80, 80, 90, 90, 90, 80, 80, 80, 10000, 10000, 10000, 2, 1, 16, -10, -10, -10, 18, 16, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 18, 16, 80, -10, -10, -10, 90, 80, 10000, 1, -10, 16, -10, -10, -10, 16, -10, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 16, -10, 80, -10, -10, -10, 80, -10, 10000, 16, 16, 16, -10, -10, -10, 80, 80, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 80, 80, 80, -10, -10, -10, 10000, 10000, 10000, 80, 80, 80, 80, 80, 80, 80, 80, 90, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 90, 80, 80, 80, 90, 80, 10000, 1, -10, 16, -10, -10, -10, 16, -10, 80, -10, -10, -10, -10, -10, -10, -10, -10, -10, 16, -10, 80, -10, -10, -10, 80, -10, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000};
  int v1[729] = {400, 10000, 300, 20000, 1000000, 10000, 200, 200, 200, 30000, 1000000, 20000, 2000000, 100000000, 1000000, 10000, 10000, 10000, 100, 100, 100, 100, 100, 100, 100, 100, 100, 30000, 30000, 30000, 1000000, 1000000, 1000000, 20000, 20000, 20000, 2000000, 2000000, 2000000, 100000000, 100000000, 100000000, 1000000, 1000000, 1000000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 100, 10000, -10000, 10000, 1000000, -10000, -10000, -10000, -10000, 10000, 1000000, -10000, 1000000, 100000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 20000, 30000, 20000, 30000, 1000000, 20000, 20000, 20000, 20000, 1000000, 2000000, 1000000, 2000000, 100000000, 1000000, 1000000, 1000000, 1000000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 100, 10000, -10000, 10000, 1000000, -10000, -10000, -10000, -10000, 10000, 1000000, -10000, 1000000, 100000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 200, 10000, 100, 20000, 1000000, 10000, -10000, -10000, -10000, 20000, 1000000, 10000, 2000000, 100000000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 10000, 10000, 10000, 1000000, 1000000, 1000000, -10000, -10000, -10000, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 100, 10000, -10000, 10000, 1000000, -10000, -10000, -10000, -10000, 10000, 1000000, -10000, 1000000, 100000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 10000, 30000, 10000, 30000, 1000000, 20000, 10000, 10000, 10000, 30000, 1000000, 20000, 2000000, 100000000, 1000000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 1000000, 1000000, 1000000, 2000000, 2000000, 2000000, 1000000, 1000000, 1000000, 2000000, 2000000, 2000000, 100000000, 100000000, 100000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 100, 10000, -10000, 10000, 1000000, -10000, -10000, -10000, -10000, 10000, 1000000, -10000, 1000000, 100000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 1000000, 1000000, 1000000, 1000000, 2000000, 1000000, 1000000, 1000000, 1000000, 1000000, 2000000, 1000000, 2000000, 100000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100, 10000, -10000, 10000, 1000000, -10000, -10000, -10000, -10000, 10000, 1000000, -10000, 1000000, 100000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 200, 10000, 100, 20000, 1000000, 10000, -10000, -10000, -10000, 20000, 1000000, 10000, 2000000, 100000000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 10000, 10000, 10000, 1000000, 1000000, 1000000, -10000, -10000, -10000, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 100, 10000, -10000, 10000, 1000000, -10000, -10000, -10000, -10000, 10000, 1000000, -10000, 1000000, 100000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 300, 10000, 200, 20000, 1000000, 10000, 100, 100, 100, 30000, 1000000, 20000, 2000000, 100000000, 1000000, 10000, 10000, 10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 20000, 20000, 20000, 1000000, 1000000, 1000000, 10000, 10000, 10000, 2000000, 2000000, 2000000, 100000000, 100000000, 100000000, 1000000, 1000000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 100, 10000, -10000, 10000, 1000000, -10000, -10000, -10000, -10000, 10000, 1000000, -10000, 1000000, 100000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 10000, 20000, 10000, 20000, 1000000, 10000, 10000, 10000, 10000, 1000000, 2000000, 1000000, 2000000, 100000000, 1000000, 1000000, 1000000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 100, 10000, -10000, 10000, 1000000, -10000, -10000, -10000, -10000, 10000, 1000000, -10000, 1000000, 100000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 200, 10000, 100, 20000, 1000000, 10000, -10000, -10000, -10000, 20000, 1000000, 10000, 2000000, 100000000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 10000, 10000, 10000, 1000000, 1000000, 1000000, -10000, -10000, -10000, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 100, 10000, -10000, 10000, 1000000, -10000, -10000, -10000, -10000, 10000, 1000000, -10000, 1000000, 100000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000};

  int v2[729] = {400, 300, 10000, 200, 200, 200, 20000, 10000, 1000000, 100, 100, 100, 100, 100, 100, 100, 100, 100, 30000, 20000, 1000000, 10000, 10000, 10000, 2000000, 1000000, 100000000, 100, -10000, 10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, 1000000, -10000, 100000000, 30000, 30000, 30000, 20000, 20000, 20000, 1000000, 1000000, 1000000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 2000000, 2000000, 2000000, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, 200, 100, 10000, -10000, -10000, -10000, 20000, 10000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 20000, 10000, 1000000, -10000, -10000, -10000, 2000000, 1000000, 100000000, 100, -10000, 10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, 1000000, -10000, 100000000, 10000, 10000, 10000, -10000, -10000, -10000, 1000000, 1000000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 1000000, 1000000, 1000000, -10000, -10000, -10000, 100000000, 100000000, 100000000, 20000, 20000, 30000, 20000, 20000, 20000, 30000, 20000, 1000000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 1000000, 1000000, 2000000, 1000000, 1000000, 1000000, 2000000, 1000000, 100000000, 100, -10000, 10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, 1000000, -10000, 100000000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 2000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 300, 200, 10000, 100, 100, 100, 20000, 10000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 30000, 20000, 1000000, 10000, 10000, 10000, 2000000, 1000000, 100000000, 100, -10000, 10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, 1000000, -10000, 100000000, 20000, 20000, 20000, 10000, 10000, 10000, 1000000, 1000000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 2000000, 2000000, 2000000, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, 200, 100, 10000, -10000, -10000, -10000, 20000, 10000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 20000, 10000, 1000000, -10000, -10000, -10000, 2000000, 1000000, 100000000, 100, -10000, 10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, 1000000, -10000, 100000000, 10000, 10000, 10000, -10000, -10000, -10000, 1000000, 1000000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 1000000, 1000000, 1000000, -10000, -10000, -10000, 100000000, 100000000, 100000000, 10000, 10000, 20000, 10000, 10000, 10000, 20000, 10000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 1000000, 1000000, 2000000, 1000000, 1000000, 1000000, 2000000, 1000000, 100000000, 100, -10000, 10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, 1000000, -10000, 100000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 10000, 10000, 30000, 10000, 10000, 10000, 30000, 20000, 1000000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 30000, 20000, 1000000, 10000, 10000, 10000, 2000000, 1000000, 100000000, 100, -10000, 10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, 1000000, -10000, 100000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 2000000, 2000000, 2000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 2000000, 2000000, 2000000, 1000000, 1000000, 1000000, 100000000, 100000000, 100000000, 200, 100, 10000, -10000, -10000, -10000, 20000, 10000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 20000, 10000, 1000000, -10000, -10000, -10000, 2000000, 1000000, 100000000, 100, -10000, 10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, 1000000, -10000, 100000000, 10000, 10000, 10000, -10000, -10000, -10000, 1000000, 1000000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 1000000, 1000000, 1000000, -10000, -10000, -10000, 100000000, 100000000, 100000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 2000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 1000000, 2000000, 1000000, 1000000, 1000000, 2000000, 1000000, 100000000, 100, -10000, 10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, -10000, 10000, -10000, 1000000, -10000, -10000, -10000, 1000000, -10000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000, 100000000};
  // if (player_comp == '2') {
  //   if (player == '2') str = exchangeOnesAndTwos(str);
  //   int i = stringToBase3(str);
  //   // printf("evaluatestring: %i\n", v_new[i]);
  //   return v_new[i];
  // } else {
  //   if (player == '2') str = exchangeOnesAndTwos(str);
  //   int i = stringToBase3(str);
  //   // printf("evaluatestring: %i\n", v_old[i]);
  //   return v_old[i];
  // }

  int i = stringToBase3(str);
  if (player == '2') {
    // printf("evaluatestring: %i\n", v2[i]);
    return v2[i];
  }
  // printf("evaluatestring: %i\n", v1[i]);
  return v1[i];
  // if (player == '2') str = exchangeOnesAndTwos(str);
  // int i = stringToBase3(str);
  // // printf("%i\n", v[i]);
  // return v1[i];
}

int insideLimits(int row, int col) {  // Returns 0 if, the position (row, col) is outside limits of the board and 1 otherwise
  return (row < 0 || row >= NROWS || col < 0 || col >= NCOLS) ? 0 : 1;
}

// char* consecutiveW_E(char board[NROWS][NCOLS], int row, int col) {  // returns the 7 positions around the position board[row][col] in the West-East direction. Character '9' means that cell is out of the board.
//   char* consec = malloc(8 * sizeof(char));
//   char player = board[row][col];
//   for (int j = col - 3, k = 0; k < 7; j++, k++)
//     consec[k] = (insideLimits(row, j)) ? board[row][j] : otherPlayer(player);  // if it is not inside the limits, assign the value of the other player (thought as a boundary of doing 4-in-a-row)
//   return consec;
// }

// char* consecutiveN_S(char board[NROWS][NCOLS], int row, int col) {  // returns the 7 positions around the position board[row][col] in the North-South direction. Character '9' means that cell is out of the board.
//   char* consec = malloc(8 * sizeof(char));
//   char player = board[row][col];
//   for (int i = row - 3, k = 0; k < 7; i++, k++)
//     consec[k] = (insideLimits(i, col)) ? board[i][col] : otherPlayer(player);  // if it is not inside the limits, assign the value of the other player (thought as a boundary of doing 4-in-a-row)
//   return consec;
// }

// char* consecutiveNW_SE(char board[NROWS][NCOLS], int row, int col) {  // returns the 7 positions around the position board[row][col] in the NorthEast-SouthWest direction. Character '9' means that cell is out of the board.
//   char* consec = malloc(8 * sizeof(char));
//   char player = board[row][col];
//   for (int i = row - 3, j = col - 3, k = 0; k < 7; i++, j++, k++)
//     consec[k] = (insideLimits(i, j)) ? board[i][j] : otherPlayer(player);  // if it is not inside the limits, assign the value of the other player (thought as a boundary of doing 4-in-a-row)
//   return consec;
// }

// char* consecutiveNE_SW(char board[NROWS][NCOLS], int row, int col) {  // returns the 7 positions around the position board[row][col] in the NorthWest-SouthEast direction. Character '9' means that cell is out of the board.
//   char* consec = malloc(8 * sizeof(char));
//   char player = board[row][col];
//   for (int i = row - 3, j = col + 3, k = 0; k < 7; i++, j--, k++)
//     consec[k] = (insideLimits(i, j)) ? board[i][j] : otherPlayer(player);  // if it is not inside the limits, assign the value of the other player (thought as a boundary of doing 4-in-a-row)
//   return consec;
// }

char* consecutiveW_E(char board[NROWS][NCOLS], int row, int col) {  // returns the 7 positions around the position board[row][col] in the West-East direction. Character '9' means that cell is out of the board.
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

char* consecutiveN_S(char board[NROWS][NCOLS], int row, int col) {  // returns the 7 positions around the position board[row][col] in the North-South direction. Character '9' means that cell is out of the board.
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

char* consecutiveNW_SE(char board[NROWS][NCOLS], int row, int col) {  // returns the 7 positions around the position board[row][col] in the NorthEast-SouthWest direction. Character '9' means that cell is out of the board.
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

char* consecutiveNE_SW(char board[NROWS][NCOLS], int row, int col) {  // returns the 7 positions around the position board[row][col] in the NorthWest-SouthEast direction. Character '9' means that cell is out of the board.
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

int is4InRow(char board[NROWS][NCOLS], int col) {  // check whether there was 4-in-a-row or not in the last move in the column 'col'. Return 1 if there was 4-in-a-row. Return 0 otherwise.
  // printf("-----4-in-a-row---------\n");
  int row = computeRow(board, col) + 1;
  char* h = consecutiveW_E(board, row, col);
  char* v = consecutiveN_S(board, row, col);
  char* d1 = consecutiveNW_SE(board, row, col);
  char* d2 = consecutiveNE_SW(board, row, col);
  // printf("\n%s %s %s %s\n", h, v, d1, d2);
  return (evaluateString(h, board[row][col]) == INF || evaluateString(v, board[row][col]) == INF || evaluateString(d1, board[row][col]) == INF || evaluateString(d2, board[row][col]) == INF) ? 1 : 0;
}
// }
// addTile(board, choice, lastPlayer);
// if (is4InRow(board, choice)) {
//   winner = lastPlayer;
//   col4inRow = choice;
//   break;
// }
// lastPlayer = otherPlayer(lastPlayer);
// }

// return endOfGame(winner);
// }

char find4InRow(char board[NROWS][NCOLS], int* row, int* col) {
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
