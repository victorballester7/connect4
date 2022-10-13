#include "../include/connect4.h"

//#include <curses.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  // for sleep() function. In Windows use <windows.h>

//#include "graphics_colors.h"
#include "../include/minimax.h"

int main() {
  // char board[NROWS][NCOLS] = {
  //     {'0', '0', '0', '0', '0', '0'},
  //     {'0', '0', '0', '0', '0', '0'},
  //     {'0', '2', '0', '0', '0', '0'},
  //     {'0', '1', '2', '2', '0', '0'},
  //     {'0', '2', '1', '2', '0', '0'},
  //     {'2', '1', '1', '1', '2', '0'}};
  // // memset(board, '0', NCOLS * NROWS);
  // printBoard(board);
  // printf("%i,%i,%i,%i\n", consecutiveEast(board, 3, 2), consecutiveSouth(board, 3, 2), consecutiveSouthWest(board, 3, 2), consecutiveSouthEast(board, 3, 2));
  // sleep(1);  // 1 is in seconds
  // clear();
  // board[1][3] = '4';
  // printBoard(board);
  // drawBoard();
  srand(time(0));
  char i = playGame();

  if (i == '0')
    printf("DRAW!\n");
  else if (i == '1')
    printf("SORRY! YOU LOST!\n");
  else
    printf("CONGRATULATIONS! YOU WON!\n");
  uploadFile(i);
  return 0;
}

void uploadFile(char i) {
  FILE* fp;
  fp = fopen("../data/statistics.txt", "r+");
  int played, won, lost, tied;
  fscanf(fp, "Games played: %d\nGames won (by the computer): %d\nGames lost (by the computer): %d\nGames tied: %d\n", &played, &won, &lost, &tied);
  printf("%d,%d,%d,%d\n", played, won, lost, tied);
  rewind(fp);  // setting the file pointer at the beginning of the file.
  played++;
  if (i == '0')
    tied++;
  else if (i == '1')
    won++;
  else
    lost++;
  fprintf(fp, "Games played: %d\nGames won (by the computer): %d\nGames lost (by the computer): %d\nGames tied: %d\n", played, won, lost, tied);
  fclose(fp);
}

char playGame() {  // do the match. Returns if there is a draw, 1 if the computer wins and 2 if the player wins.
  // int i= presentation();
  char board[NROWS][NCOLS];
  memset(board, '0', NCOLS * NROWS);
  int choice;
  char lastPlayer = whoStarts();
  clear();
  while (!isFull(board)) {
    // printf("hola1\n");
    if (lastPlayer == '2') {  // player's turn
      printf("Where do you want to play in (number of the column starting on 1)?\n");
      scanf("%i", &choice);
      choice--;
      printf("choice meva: %i\n", choice);
    } else {  // computer's turn
      choice = computerPlay(board);
      printf("choice ordinador: %i\n", choice);

      // printf("Where do you want the computer to play in (number of the column starting on 1)?\n");
      // scanf("%i", &choice);
      // choice--;
    }
    if (choice < 0 || choice >= NCOLS) {
      printf("The column enter is not valid!, %c\n", lastPlayer);
      continue;
    }
    // clear();
    //  printf("hola2\n");
    addTile(board, choice, lastPlayer);
    // printf("hola3\n");
    printBoard(board);
    //  printf("hola4\n");
    if (is4InRow(board, choice)) break;
    //   printf("hola5\n");
    lastPlayer = otherPlayer(lastPlayer);
  }
  if (isFull(board)) lastPlayer = '0';
  return lastPlayer;
}

char otherPlayer(char player) {
  if (player == '1')
    return '2';
  else
    return '1';
}

int computeNumChilds(char board[NROWS][NCOLS]) {  // computes the number of columns that are still not full.
  int count = 0, j = 0;
  while (j < NCOLS)
    if (board[0][j++] == '0') count++;
  printf("NumChilds: %i\n", count);
  return count;
}

int isFull(char board[NROWS][NCOLS]) {         // Return 1 if the board is full. Return 0 otherwise.
  if (computeNumChilds(board) == 0) return 1;  // is full
  return 0;                                    // is not full
}

char whoStarts() {
  char start;
  printf("Do you want to start (y/n)?\n");
  scanf("%c", &start);
  if (start == 'y') return '2';
  return '1';
}

void addTile(char board[NROWS][NCOLS], int col, char player) {  // add the new tile into the column col.
  int row = rowFirstEmpty(board, col);
  board[row][col] = player;
}

int presentation() {
  printf("Welcome to Connect4!\n");
  char choice;
  printf("What do you want to do?\n1) Play a new game\n2) See statistics\n3) Exit");
  scanf("%c", &choice);
  switch (choice) {
    case '1':
      return 0;
    // case '2':
    case '3':
      return 1;
    default:
      printf("Error entering the data. Exiting");
      return 1;
  }
}

void printLine(int len) {  // print a line of dashes of length 'len'
  for (int j = 0; j < len - 1; j++)
    printf("--");
  printf("-\n");
}

void printBoard(char board[NROWS][NCOLS]) {
  for (int j = 0; j < NCOLS; j++)
    printf("-   ");
  printf("-\n");
  for (int i = 0; i < NROWS; i++) {
    for (int j = 0; j < NCOLS; j++) {
      if (board[i][j] == '0')
        printf("|   ");
      else if (board[i][j] == '1')
        printf("| \u25A0 ");
      else
        printf("| \u25CF ");
    }
    printf("|\n");
    printLine(2 * NCOLS + 1);
  }
}

void clear() {
  system("clear");
}

double heuristicFunction(char board[NROWS][NCOLS], char player) {
  int row;
  char *h, *v, *d1, *d2;
  double totalValue = 0, defenseMode = 1;  // defenseMode: the higher, the more defensive is the computer.
  int count = 0;
  for (int col = 0; col < NCOLS; col++) {
    if ((row = rowFirstEmpty(board, col) + 1) >= NROWS) continue;  // avoid cases where the last tile is not the one of the player (i.e. avoid when it is empty or it is the one of the other player)
    h = consecutiveW_E(board, row, col);
    v = consecutiveN_S(board, row, col);
    d1 = consecutiveNW_SE(board, row, col);
    d2 = consecutiveNE_SW(board, row, col);
    if (board[row][col] == '1')  // computer
      totalValue += (evaluateString(h, '1') + evaluateString(v, '1') + evaluateString(d1, '1') + evaluateString(d2, '1')) / 4;
    else  // if board[row][col] == '2' // player
      totalValue -= defenseMode * (evaluateString(h, '2') + evaluateString(v, '2') + evaluateString(d1, '2') + evaluateString(d2, '2')) / 4;
    count++;
  }
  return totalValue / count;
}

int stringToBase3(char* str) {  // Convert a string of numbers in the set {0,1,2} to a number in base 3.
  int len = strlen(str), base3 = 0;
  for (int i = 0; i < len; i++) {
    if (str[i] == '1')
      base3 += (int)pow(3, i);
    else if (str[i] == '2')
      base3 += (int)2 * pow(3, i);
  }
  free(str);
  return base3;
}

char* exchangeOnesAndTwos(char* str) {  // exchange the '1' with '2' in the string 'str' and viceversa.
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if (str[i] == '1')
      str[i] = '2';
    else if (str[i] == '2')
      str[i] = '1';
  }
  return str;
}

char* removeCenterChar(char* str) {
  int len = strlen(str);  // assume len is odd.
  char* newStr = malloc(7 * sizeof(char));
  for (int i = 0; i < (len - 1) / 2; i++) newStr[i] = str[i];
  for (int i = (len + 1) / 2; i < len; i++) newStr[i - 1] = str[i];
  free(str);
  return newStr;
}

double evaluateString(char* str, char player) {
  // The numbers greater than 1 mean that there is a 4-in-a-row.
  // double v[729] = {0.12, 0.25, 0.1, 0.3, 0.48, 0.28, 0.08, 0.08, 0.08, 0.25, 0.38, 0.23, 0.48, 5.46, 0.46, 0.21, 0.21, 0.21, 0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.3, 0.43, 0.28, 0.48, 0.66, 0.46, 0.26, 0.26, 0.26, 0.48, 0.61, 0.46, 5.46, 10.44, 5.44, 0.44, 0.44, 0.44, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 5.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.25, 0.38, 0.23, 0.43, 0.61, 0.41, 0.21, 0.21, 0.21, 0.38, 0.51, 0.36, 0.61, 5.59, 0.59, 0.34, 0.34, 0.34, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.48, 0.61, 0.46, 0.66, 0.84, 0.64, 0.44, 0.44, 0.44, 5.46, 5.59, 5.44, 10.44, 15.42, 10.42, 5.42, 5.42, 5.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 5.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.08, 0.21, 0.06, 0.26, 0.44, 0.24, 0, 0, 0, 0.21, 0.34, 0.19, 0.44, 5.42, 0.42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.26, 0.39, 0.24, 0.44, 0.62, 0.42, 0, 0, 0, 0.44, 0.57, 0.42, 5.42, 10.4, 5.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 5.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.25, 0.38, 0.23, 0.43, 0.61, 0.41, 0.21, 0.21, 0.21, 0.38, 0.51, 0.36, 0.61, 5.59, 0.59, 0.34, 0.34, 0.34, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.43, 0.56, 0.41, 0.61, 0.79, 0.59, 0.39, 0.39, 0.39, 0.61, 0.74, 0.59, 5.59, 10.57, 5.57, 0.57, 0.57, 0.57, 0.37, 0.37, 0.37, 0.37, 0.37, 0.37, 0.37, 0.37, 0.37, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 5.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.48, 0.61, 0.46, 0.66, 0.84, 0.64, 0.44, 0.44, 0.44, 0.61, 0.74, 0.59, 0.84, 5.82, 0.82, 0.57, 0.57, 0.57, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 5.46, 5.59, 5.44, 5.64, 5.82, 5.62, 5.42, 5.42, 5.42, 10.44, 10.57, 10.42, 15.42, 20.4, 15.4, 10.4, 10.4, 10.4, 5.4, 5.4, 5.4, 5.4, 5.4, 5.4, 5.4, 5.4, 5.4, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 5.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.08, 0.21, 0.06, 0.26, 0.44, 0.24, 0, 0, 0, 0.21, 0.34, 0.19, 0.44, 5.42, 0.42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.26, 0.39, 0.24, 0.44, 0.62, 0.42, 0, 0, 0, 0.44, 0.57, 0.42, 5.42, 10.4, 5.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 5.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.1, 0.23, 0.08, 0.28, 0.46, 0.26, 0.06, 0.06, 0.06, 0.23, 0.36, 0.21, 0.46, 5.44, 0.44, 0.19, 0.19, 0.19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.28, 0.41, 0.26, 0.46, 0.64, 0.44, 0.24, 0.24, 0.24, 0.46, 0.59, 0.44, 5.44, 10.42, 5.42, 0.42, 0.42, 0.42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 5.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.23, 0.36, 0.21, 0.41, 0.59, 0.39, 0.19, 0.19, 0.19, 0.36, 0.49, 0.34, 0.59, 5.57, 0.57, 0.32, 0.32, 0.32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.46, 0.59, 0.44, 0.64, 0.82, 0.62, 0.42, 0.42, 0.42, 5.44, 5.57, 5.42, 10.42, 15.4, 10.4, 5.4, 5.4, 5.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 5.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.08, 0.21, 0.06, 0.26, 0.44, 0.24, 0, 0, 0, 0.21, 0.34, 0.19, 0.44, 5.42, 0.42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.26, 0.39, 0.24, 0.44, 0.62, 0.42, 0, 0, 0, 0.44, 0.57, 0.42, 5.42, 10.4, 5.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 5.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  double v[729] = {0.12, 0.25, 0.1, 0.3, 0.48, 0.28, 0.08, 0.08, 0.08, 0.25, 0.38, 0.23, 0.48, 1.46, 0.46, 0.21, 0.21, 0.21, 0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.3, 0.43, 0.28, 0.48, 0.66, 0.46, 0.26, 0.26, 0.26, 0.48, 0.61, 0.46, 1.46, 2.44, 1.44, 0.44, 0.44, 0.44, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.25, 0.38, 0.23, 0.43, 0.61, 0.41, 0.21, 0.21, 0.21, 0.38, 0.51, 0.36, 0.61, 1.59, 0.59, 0.34, 0.34, 0.34, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.48, 0.61, 0.46, 0.66, 0.84, 0.64, 0.44, 0.44, 0.44, 1.46, 1.59, 1.44, 2.44, 3.42, 2.42, 1.42, 1.42, 1.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.08, 0.21, 0.06, 0.26, 0.44, 0.24, 0, 0, 0, 0.21, 0.34, 0.19, 0.44, 1.42, 0.42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.26, 0.39, 0.24, 0.44, 0.62, 0.42, 0, 0, 0, 0.44, 0.57, 0.42, 1.42, 2.4, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.25, 0.38, 0.23, 0.43, 0.61, 0.41, 0.21, 0.21, 0.21, 0.38, 0.51, 0.36, 0.61, 1.59, 0.59, 0.34, 0.34, 0.34, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.43, 0.56, 0.41, 0.61, 0.79, 0.59, 0.39, 0.39, 0.39, 0.61, 0.74, 0.59, 1.59, 2.57, 1.57, 0.57, 0.57, 0.57, 0.37, 0.37, 0.37, 0.37, 0.37, 0.37, 0.37, 0.37, 0.37, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.48, 0.61, 0.46, 0.66, 0.84, 0.64, 0.44, 0.44, 0.44, 0.61, 0.74, 0.59, 0.84, 1.82, 0.82, 0.57, 0.57, 0.57, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 0.42, 1.46, 1.59, 1.44, 1.64, 1.82, 1.62, 1.42, 1.42, 1.42, 2.44, 2.57, 2.42, 3.42, 4.4, 3.4, 2.4, 2.4, 2.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.08, 0.21, 0.06, 0.26, 0.44, 0.24, 0, 0, 0, 0.21, 0.34, 0.19, 0.44, 1.42, 0.42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.26, 0.39, 0.24, 0.44, 0.62, 0.42, 0, 0, 0, 0.44, 0.57, 0.42, 1.42, 2.4, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.1, 0.23, 0.08, 0.28, 0.46, 0.26, 0.06, 0.06, 0.06, 0.23, 0.36, 0.21, 0.46, 1.44, 0.44, 0.19, 0.19, 0.19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.28, 0.41, 0.26, 0.46, 0.64, 0.44, 0.24, 0.24, 0.24, 0.46, 0.59, 0.44, 1.44, 2.42, 1.42, 0.42, 0.42, 0.42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.23, 0.36, 0.21, 0.41, 0.59, 0.39, 0.19, 0.19, 0.19, 0.36, 0.49, 0.34, 0.59, 1.57, 0.57, 0.32, 0.32, 0.32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.46, 0.59, 0.44, 0.64, 0.82, 0.62, 0.42, 0.42, 0.42, 1.44, 1.57, 1.42, 2.42, 3.4, 2.4, 1.4, 1.4, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.08, 0.21, 0.06, 0.26, 0.44, 0.24, 0, 0, 0, 0.21, 0.34, 0.19, 0.44, 1.42, 0.42, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.26, 0.39, 0.24, 0.44, 0.62, 0.42, 0, 0, 0, 0.44, 0.57, 0.42, 1.42, 2.4, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.06, 0.19, 0, 0.24, 0.42, 0, 0, 0, 0, 0.19, 0.32, 0, 0.42, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  if (player == '2') str = exchangeOnesAndTwos(str);
  int i = stringToBase3(removeCenterChar(str));
  // printf("%lf  ", v[i]);
  return v[i];
}

int insideLimits(int row, int col) {
  if (row < 0 || row >= NROWS || col < 0 || col >= NCOLS)
    return 0;  // outside limits of the board
  else
    return 1;  // inside limits of the board
}

char* consecutiveW_E(char board[NROWS][NCOLS], int row, int col) {  // returns the 7 positions around the position board[row][col] in the West-East direction. Character '9' means that cell is out of the board.
  char* consec = malloc(8 * sizeof(char));
  char player = board[row][col];
  for (int j = col - 3, k = 0; k < 7; j++, k++) {
    if (insideLimits(row, j)) {
      consec[k] = board[row][j];
    } else
      consec[k] = otherPlayer(player);  // out of the board
  }
  return consec;
}

char* consecutiveN_S(char board[NROWS][NCOLS], int row, int col) {  // returns the 7 positions around the position board[row][col] in the North-South direction. Character '9' means that cell is out of the board.
  char* consec = malloc(8 * sizeof(char));
  char player = board[row][col];
  for (int i = row - 3, k = 0; k < 7; i++, k++) {
    if (insideLimits(i, col))
      consec[k] = board[i][col];
    else
      consec[k] = otherPlayer(player);  // out of the board
  }
  return consec;
}

char* consecutiveNW_SE(char board[NROWS][NCOLS], int row, int col) {  // returns the 7 positions around the position board[row][col] in the NorthEast-SouthWest direction. Character '9' means that cell is out of the board.
  char* consec = malloc(8 * sizeof(char));
  char player = board[row][col];
  for (int i = row - 3, j = col - 3, k = 0; k < 7; i++, j++, k++) {
    if (insideLimits(i, j))
      consec[k] = board[i][j];
    else
      consec[k] = otherPlayer(player);  // out of the board
  }
  return consec;
}

char* consecutiveNE_SW(char board[NROWS][NCOLS], int row, int col) {  // returns the 7 positions around the position board[row][col] in the NorthWest-SouthEast direction. Character '9' means that cell is out of the board.
  char* consec = malloc(8 * sizeof(char));
  char player = board[row][col];
  for (int i = row - 3, j = col + 3, k = 0; k < 7; i++, j--, k++) {
    if (insideLimits(i, j))
      consec[k] = board[i][j];
    else
      consec[k] = otherPlayer(player);  // out of the board
  }
  return consec;
}

int is4InRow(char board[NROWS][NCOLS], int col) {  // check whether there was 4-in-a-row or not in the last move in the column 'col'. Return 1 if there was 4-in-a-row. Return 0 otherwise.
  int row = rowFirstEmpty(board, col) + 1;
  char* h = consecutiveW_E(board, row, col);
  char* v = consecutiveN_S(board, row, col);
  char* d1 = consecutiveNW_SE(board, row, col);
  char* d2 = consecutiveNE_SW(board, row, col);
  // printBoard(board);
  printf("%i,%i--%s,%s,%s,%s\n", row, col, h, v, d1, d2);
  if (evaluateString(h, board[row][col]) > 1 || evaluateString(v, board[row][col]) > 1 || evaluateString(d1, board[row][col]) > 1 || evaluateString(d2, board[row][col]) > 1) {
    printf("\n");
    return 1;
  }
  printf("\n");
  return 0;
}

int rowFirstEmpty(char board[NROWS][NCOLS], int col) {  // returns the row of the first empty cell in the column 'col'.
  int row = 0;
  while (board[row][col] == '0' && row < NROWS) row++;
  return row - 1;
}
