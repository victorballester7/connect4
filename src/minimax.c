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

int computeRow(char board[NROWS][NCOLS], int col) {  // computes the first empty row in the i-th column that is still not full.
  int k = NROWS - 1;
  if (col == -1) return -1;
  while (k >= 0 && board[k][col] != '0') k--;
  return k;
}

void makePlay(char board[NROWS][NCOLS], int row, int col, int level) {
  if (level % 2 == 0)  // player's turn
    board[row][col] = '2';
  else  // computer's turn
    board[row][col] = '1';
}

Node *createFirstNode(char board[NROWS][NCOLS]) {  // Obs: It seems that is missing a parameter (professor message)
  Node *p = malloc(sizeof(Node));
  p->level = 0;
  copyBoard(p->board, board);
  p->n_children = computeNumChilds(p->board);
  p->children = malloc(p->n_children * sizeof(Node *));
  return p;
}

char whichPlayer(int level) {           // level = level of the tree (keeping in mind that the level of the root is 0).
  return (level % 2 == 0) ? '2' : '1';  // '2' = player's turn, '1' = computer's turn
}

Node *createNode(Node *father, int child_index) {  // Obs: It seems that is missing a parameter (professor message)
  Node *p = malloc(sizeof(Node));
  if (p == NULL) {
    printf("Error allocating memory (node).\n");
    return p;
  }
  p->level = father->level + 1;
  copyBoard(p->board, father->board);
  int col = computeColumn(p->board, child_index);
  int row = computeRow(p->board, col);
  makePlay(p->board, row, col, p->level);
  if (p->level < DEPTH && !is4InRow(p->board, col)) {
    p->n_children = computeNumChilds(p->board);
    p->children = malloc(p->n_children * sizeof(Node *));
    p->value = 0;  // we give a default value of 0 in order to avoid problems.
    if (p->children == NULL) {
      printf("Error allocating memory (children).\n");
      return p;
    }
  } else {  // is leaf or there is 4-in-a-row in this play
    p->n_children = 0;
    p->children = NULL;
    // assign  THRESHOLD_PUNCT to p->value if there is 4-in-a-row by the computer
    // assign -THRESHOLD_PUNCT to p->value if there is 4-in-a-row by the player
    if (p->level < DEPTH) p->value = THRESHOLD_PUNCT * ((p->level % 2 == 1) ? (1) : (-1));
  }

  // else if (p->level == DEPTH) {  // is leaf or there is 4-in-a-row in this play
  //   p->n_children = 0;
  //   p->children = NULL;
  // }

  // else {  // there is 4-in-a-row.
  //   // p->value = THRESHOLD_PUNCT;
  //   p->n_children = 0;
  //   p->children = NULL;
  // }
  return p;
}

void create1Level(Node *father) {                 // create one level of the tree (i.e. including all its nodes)
  for (int i = 0; i < father->n_children; i++) {  // Obs: i is the number of the child; (in general) not the same as the number of the column to play in.
    father->children[i] = createNode(father, i);
    if (father->level >= 1 && (father->children[i]->value == THRESHOLD_PUNCT || father->children[i]->value == -THRESHOLD_PUNCT)) {  // if there is 4-in-a-row in some child, don't create more trees and delete its brothers!! But only if the level of the father is greater than 1. Because if not, it may disturb the right column to play in.
      father->n_children = 1;
      *(father->children[0]) = *(father->children[i]);
      for (int j = 1; j <= i; j++) deleteNode(father->children[j]);
      break;
    }
  }
}

int minimax(Node *p) {  // do the minimax algorithm
  // static int i = 0;
  // if (p->n_children == 0) {  // possibly not accessed
  //   printf("esto es prueba\n");
  //   return heuristicFunction(p->board, whichPlayer(p->level));
  // }
  // i++;
  // printf("%i-minimaxHoLA\n", i);
  int m = p->children[0]->value;
  for (int i = 1; i < p->n_children; i++) {
    if (p->level % 2 == 0)  // player's turn level
      m = MAX(m, p->children[i]->value);
    else  // computer's turn level
      m = MIN(m, p->children[i]->value);
  }
  // printf("minimax: %d\n", m);
  return m;
}

// This function supposes that we have just created a root node and its child array has been also created.
void createTree(Node *p) {
  // printf("LEVEL: %i\n", p->level);
  create1Level(p);
  // if (p->n_children <= 1) {
  //   printBoard(p->board);
  // }
  for (int i = 0; i < p->n_children; i++) {
    if (p->children[i]->n_children == 0) {
      // printf("NumChildren: %i/%i", i, p->n_children);
      // printf("LEVEL: %i\n", p->level);
      p->children[i]->value = heuristicFunction(p->children[i]->board);
      continue;
    }  // if a child is a leaf, continue (continue instead of break because we have to assign values on each iteration).
    createTree(p->children[i]);
  }
  p->value = minimax(p);
  delete1Level(p);
}

int makeChoice(Node *p) {  // returns the best column to play in.
  int i = -1;
  while (p->children[++i]->value != p->value) continue;
  return computeColumn(p->board, i);
}

void deleteNode(Node *p) {  // delete node p.
  // if (p->children != 0) {
  //   free(p->children);
  //   p->children = NULL;
  // }
  free(p);
  p = NULL;
}

void delete1Level(Node *father) {  // delete level of the children of father.
  for (int i = 0; i < father->n_children; i++)
    deleteNode(father->children[i]);
}

// void printTree(Node *p) {
//   if (p->level == 0) printf("%g ", p->value);
//   for (int i = 0; i < p->n_children; i++) {
//     if (p->children[i]->level == DEPTH) continue;  // if it is a leaf, continue.
//     printTree(p->children[i]);
//   }
// }

int computerPlay(char board[NROWS][NCOLS]) {
  Node *root = createFirstNode(board);
  createTree(root);
  int choice = makeChoice(root);
  deleteNode(root);
  return choice;
}
