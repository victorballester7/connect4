#ifndef __MINIMAX_H__
#define __MINIMAX_H__

// for sleep() function. In Windows use <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // for sleep() function. In Windows use <windows.h>

#include "../include/connect4.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))  // minimum of two values
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))  // maximum of two values

/// @brief Node of a tree.
typedef struct node {
  int level;               // level of the node (starting at 0).
  struct node **children;  // children of the node.
  int n_children;          // number of children of the node.
  // char **board;  // board filled with 0 (if the cell is empty), 1 (if it is the computer's tile) or 2 (if it is the player's tile).
  char **board;  // board filled with 0 (if the cell is empty), 1 (if it is the computer's tile) or 2 (if it is the player's tile).
  int value;     // value assigned to the node for the Minimax algorithm.
  int alpha;
  int beta;
  int colToPlay;
} Node;

/// @brief Creates the tree, does the minimax with the implementation of the alpha-beta pruning and deletes the tree except for the root node.
/// @param p A node from which start the tree (the root).
/// @return Returns the value of the node p obtained from the Alpha-Beta algorithm.
int alphaBetaTree(Node *p);

/// @brief Translates the index of the child into the actual column of the board.
/// @param board Board of the game.
/// @param i Index of the child (i.e. the i-th child).
/// @return The column of the board corresponding to the child i, or -1 if not founded.
int computeColumn(char **board, int i);

/// @brief Searches for the first (in fact the last if they are ordered from 0 to NROWS - 1) empty row in the column 'col'.
/// @param board Board of the game.
/// @param col Number of the column.
/// @return The first (in fact the last if they are ordered from 0 to NROWS - 1) empty row in the column 'col', or -1 if not founded.
int computeRow(char **board, int col);

/// @brief The computer does the play.
/// @param board Board of the game.
/// @return The column in which the computer wants to play.
int computerPlay(char **board);

/// @brief Copies the board 'src' to the board 'dest'.
/// @param dest Board copied from 'src'.
/// @param src Board to copy to 'dest'.
void copyBoard(char **dest, char **src);

// /// @brief Copy the contents of the struct Node from src to dest.
// /// @param dest Node to be written.
// /// @param src Node to be copied.
// void copyNode(Node *dest, Node *src);

/// @brief Creates 1 level of nodes that are children of the node 'father'
/// @param father A node from which we want to create children.
/// @param alphaBeta True if the algorithm where this function is passed is the alphaBeta and False if not.
/// @return -1 if there is no 4-in-a-row, and the column (>=0) if it is.
int create1Level(Node *father, bool alphaBeta);

/// @brief Creates the root node of the tree.
/// @param board Board of the game.
/// @return A pointer to the node root.
Node *createFirstNode(char **board);

/// @brief Creates a node (different from the root) of the tree.
/// @param father The father of the node to be created.
/// @param col The number of col where the play has to be done.
/// @return A pointer to the node created.
Node *createNode(Node *father, int col);

/// @brief Create the tree for the Minimax algorithm, does the Minimax algorithm and deletes all the nodes except for the first one.
/// @param p Node root of the tree.
/// @return A matrix with the values of the children of p and the columns to play with which they are linked.
int **createSmallTree(Node *p);

/// @brief Create the tree for the Minimax algorithm, does the Minimax algorithm and deletes all the nodes except for the first one.
/// @param p Node root of the tree.
/// @return The value of the choice of the column, or 0.
int createTree(Node *p);

/// @brief Deletes all children of the node 'father'.
/// @param father  The father of the children to be deleted.
void delete1Level(Node *father);

/// @brief Delete the node 'p'.
/// @param p A node of the tree.
void deleteNode(Node *p);

/// @brief Decides which column does the computer have to play in.
/// @param p The node in which we are making the choice.
/// @return The number of the column in which the computer has to play.
int makeChoice(Node *p);

/// @brief Add the new tile to the board of the game.
/// @param board Board of the game.
/// @param row Row to play in.
/// @param col Column to play in.
/// @param level Level of the tree in which we are doing the play.
void makePlay(char **board, int row, int col, int level);

/// @brief Implements the Minimax algorithm.
/// @param p The node in which we are doing the Minimax algorithm.
/// @return The value that gives the Minimax algorithm.
int minimax(Node *p);

/// @brief Orders the children of the father from best to worst if the children are 'computer's turn' or from worst to best if the children are 'player's turn'.
/// @param father Father of the children to be ordered.
/// @return A vector whose i-th component is the ordered position of the i-th child.
int *order1Level(Node *father);

/// @brief A function converting the level of the algorithm to the player that is playing at that time of the match
/// @param level Level of the algorithm
/// @return '1' for the computer, '2' for the player
char whichPlayer(int level);

// int *ordering1Level(Node *father);

#endif
