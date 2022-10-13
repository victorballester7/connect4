#ifndef __MINIMAX_H__
#define __MINIMAX_H__

#include "connect4.h"  //doen't matter if you put always first the connect.h

#define DEPTH 6  // Number of levels on the Minimax algorithm.
#define MAX INT_MAX

typedef struct node {
  struct node **childs;      // childs of the node.
  int n_childs;              // number of child of the node.
  char board[NROWS][NCOLS];  // board filled with 0 (if the cell is empty), 1 (if it is the computer's tile) or 2 (if it is the player's tile).
  double value;              // value assigned to the node for the Minimax algorithm.
} Node;

void copyBoard(char dest[NROWS][NCOLS], char src[NROWS][NCOLS]);  // copies the 'dest' board to the 'src' board.
int computeColumn(char board[NROWS][NCOLS], int i);
int computeRow(char board[NROWS][NCOLS], int i);
void doPlay(char board[NROWS][NCOLS], int row, int col, int level);
Node *createFirstNode(char board[NROWS][NCOLS]);
Node *createNode(Node *father, int child_index, int child_level);
void create1Level(Node *father, int child_level);
double minimax(Node *p, int p_level);
// This function supposes that we have just created a root node and its child array has been also created.
// p_level is the level of the node p.
void createTree(Node *p, int p_level);
int doMinimax(Node *p);           // returns the best column to play in.
void deleteNode(Node *p);         // delete node p.
void delete1Level(Node *father);  // delete level of the childs of father.
void deleteTree(Node *p, int p_level);
void printTree(Node *p, int p_level);
int computerPlay(char board[NROWS][NCOLS]);

#endif
