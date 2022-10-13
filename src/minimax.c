#include "../include/minimax.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // for sleep() function. In Windows use <windows.h>

#include "../include/connect4.h"
// #define NROWS 8  // Number of rows of the board
// #define NCOLS 8  // Number of columns of the board
// #define DEPTH 2  // Number of levels on the Minimax algorithm.
// #define EPS 1e-5

void copyBoard(char dest[NROWS][NCOLS], char src[NROWS][NCOLS]) {  // copies the 'dest' board to the 'src' board.
  for (int i = 0; i < NROWS; i++) {
    for (int j = 0; j < NCOLS; j++)
      dest[i][j] = src[i][j];
  }
}

int computeColumn(char board[NROWS][NCOLS], int i) {  // computes the i-th column that is still not full.
  int count = 0;
  for (int j = 0; j < NCOLS; j++) {
    if (board[0][j] == '0') {
      if (count == i) return j;
      count++;
    }
  }
  return -1;
}

int computeRow(char board[NROWS][NCOLS], int i) {  // computes the first empty row in the i-th column that is still not full.
  int j = computeColumn(board, i), k = NROWS - 1;
  if (j == -1) return -1;
  while (board[k][j] != '0') k--;
  return k;
}

void doPlay(char board[NROWS][NCOLS], int row, int col, int level) {
  if (level % 2 == 0)  // player's turn
    board[row][col] = '2';
  else  // computer's turn
    board[row][col] = '1';
}

Node *createFirstNode(char board[NROWS][NCOLS]) {  // Obs: It seems that is missing a parameter (professor message)
  Node *p = malloc(sizeof(Node));
  copyBoard(p->board, board);
  p->n_childs = computeNumChilds(p->board);
  p->childs = malloc(p->n_childs * sizeof(Node *));
  return p;
}

char whichPlayer(int level) {  // level of the root is 0.
  if (level % 2 == 0)          // player's turn
    return '2';
  else  // computer's turn
    return '1';
}

Node *createNode(Node *father, int child_index, int child_level) {  // Obs: It seems that is missing a parameter (professor message)
  Node *p = malloc(sizeof(Node));
  copyBoard(p->board, father->board);
  int col = computeColumn(p->board, child_index);
  int row = computeRow(p->board, child_index);
  doPlay(p->board, row, col, child_level);
  if (child_level < DEPTH && !is4InRow(p->board, col)) {
    p->n_childs = computeNumChilds(p->board);
    p->childs = malloc(p->n_childs * sizeof(Node *));
  } else {  // is leaf
    p->n_childs = 0;
    p->childs = NULL;
  }
  return p;
}

void create1Level(Node *father, int child_level) {
  for (int i = 0; i < father->n_childs; i++)  // Obs: i is the number of the child (in general) not the same as the number of the column to play
    father->childs[i] = createNode(father, i, child_level);
}

double minimax(Node *p, int p_level) {
  if (p->n_childs == 0) return heuristicFunction(p->board, whichPlayer(p_level));
  double m = p->childs[0]->value;
  for (int i = 1; i < p->n_childs; i++) {
    if (p_level % 2 == 0)  // player's turn level
      m = fmax(m, p->childs[i]->value);
    else  // computer's turn level
      m = fmin(m, p->childs[i]->value);
  }
  return m;
}

// This function supposes that we have just created a root node and its child array has been also created.
void createTree(Node *p, int p_level) {  // p_level is the level of the node p.
  // if (p_level == 0) p->value = 444;
  // printf("hola");
  create1Level(p, p_level + 1);
  for (int i = 0; i < p->n_childs; i++) {
    // printf("child number %i:\n", i);
    if (p_level + 1 == DEPTH) {
      p->childs[i]->value = heuristicFunction(p->childs[i]->board, whichPlayer(p_level + 1));
      // printf("child %i: %lf\n", i, p->childs[i]->value);
      // printBoard(p->childs[i]->board);
      continue;
    }  // if a child is a leaf, continue (continue instead of break because we have to assign values on each iteration).
    createTree(p->childs[i], p_level + 1);
  }
  p->value = minimax(p, p_level);
  // printf("value father LEVEL %i: %lf\n", p_level, p->value);
}

int doMinimax(Node *p) {  // returns the best column to play in.
  int i = -1;
  while (fabs(p->value - p->childs[++i]->value) > EPS) continue;
  return i;
}

void deleteNode(Node *p) {  // delete node p.
  free(p);
}

// don't need it
void delete1Level(Node *father) {  // delete level of the childs of father.
  for (int i = 0; i < father->n_childs; i++)
    deleteNode(father->childs[i]);
}

void deleteTree(Node *p, int p_level) {
  // for (int i = 0; i < p->n_childs; i++) {
  //   if (p_level + 1 == DEPTH) {
  //     delete1Level(p);
  //     exit(0);
  //   }  // if it is a leaf, continue.
  //   deleteTree(p->childs[i], p_level + 1);
  // }
  // delete1Level(p);
  // if (p_level == 0) deleteNode(p);  // last deleteNode of the root node.
  for (int i = 0; i < p->n_childs; i++) {
    if (p_level + 1 == DEPTH) {
      deleteNode(p->childs[i]);
      continue;
    }  // if it is a leaf, continue.
    deleteTree(p->childs[i], p_level + 1);
  }
  deleteNode(p);
}

void printTree(Node *p, int p_level) {
  if (p_level == 0) printf("%g ", p->value);
  for (int i = 0; i < p->n_childs; i++) {
    if (p_level + 1 == DEPTH) continue;  // if it is a leaf, continue.
    printTree(p->childs[i], p_level + 1);
  }
}

int computerPlay(char board[NROWS][NCOLS]) {
  Node *root = createFirstNode(board);
  createTree(root, 0);
  int choice = doMinimax(root);
  deleteTree(root, 0);
  return choice;
}

// int main() {
//   char board[NROWS][NCOLS];
//   memset(board, '0', NCOLS * NROWS);
//   printBoard(board);
//   sleep(1);  // 1 is in seconds
//   clear();
//   board[1][3] = '4';
//   printBoard(board);
//   return 0;
// }

// int main() {
//   // = {{'0', '0', '1', '0'}, {'0', '0', '0', '0'}, {'0', '0', '0', '0'}, {'0', '0', '0', '1'}}
//   srand(2);  // only once in all the code

//   char matrix[NROWS][NCOLS];
//   memset(matrix, '0', NROWS * NCOLS);  // initializes to '0' all elements of a matrix.
//   Node *root = createFirstNode(matrix);
//   createTree(root, 0);
//   printTree(root, 0);
//   printf("%i\n", doMinimax(root));
//   deleteTree(root, 0);
//   //  int m = 4, n = 4;
//   //  doPlay(matrix, 2, 1, 1);
//   //  doPlay(matrix, 1, 3, 2);
//   //  for (int i = 0; i < m; i++) {
//   //    for (int j = 0; j < n; j++) {
//   //      // if (matrix[i][j] == '0')
//   //      printf("%c ", matrix[i][j]);
//   //    }
//   printf("\n");
//   //  }
//   //  printf("%i\n", computeNumChilds(matrix));
//   return 0;
// }
