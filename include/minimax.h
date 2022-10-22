#ifndef __MINIMAX_H__
#define __MINIMAX_H__

#include "connect4.h"  //doen't matter if you put always first the connect.h

#define DEPTH 2                              // Number of levels on the Minimax algorithm.
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))  // minimum of two values
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))  // maximum of two values

/// @brief Node of a tree.
typedef struct node {
  int level;                 // level of the node (starting at 0).
  struct node **children;    // children of the node.
  int n_children;            // number of children of the node.
  char board[NROWS][NCOLS];  // board filled with 0 (if the cell is empty), 1 (if it is the computer's tile) or 2 (if it is the player's tile).
  int value;                 // value assigned to the node for the Minimax algorithm.
} Node;

/// @brief Translates the index of the child into the actual column of the board.
/// @param board Board of the game.
/// @param i Index of the child (i.e. the i-th child).
/// @return The column of the board corresponding to the child i, or -1 if not founded.
int computeColumn(char board[NROWS][NCOLS], int i);

/// @brief Searches for the first (in fact the last if they are ordered from 0 to NROWS - 1) empty row in the column 'col'
/// @param board Board of the game.
/// @param col Number of the column.
/// @return The first (in fact the last if they are ordered from 0 to NROWS - 1) empty row in the column 'col', or -1 if not founded
int computeRow(char board[NROWS][NCOLS], int col);

/// @brief The computer does the play.
/// @param board Board of the game.
/// @return The column in which the computer wants to play.
int computerPlay(char board[NROWS][NCOLS]);

/// @brief Creates 1 level of nodes that are children of the node 'father'
/// @param father A node from which we want to create children.
void create1Level(Node *father);

/// @brief Creates the root node of the tree.
/// @param board Board of the game.
/// @return A pointer to the node root.
Node *createFirstNode(char board[NROWS][NCOLS]);

/// @brief Creates a node (different from the root) of the tree.
/// @param father The father of the node to be created.
/// @param child_index The number of child that we want to create.
/// @return A pointer to the node created.
Node *createNode(Node *father, int child_index);

/// @brief Create the tree for the Minimax algorithm, does the Minimax algorithm and deletes all the nodes except for the first one.
/// @param p Node root of the tree.
void createTree(Node *p);

/// @brief Deletes all children of the node 'father'.
/// @param father  The father of the children to be deleted.
void delete1Level(Node *father);

/// @brief Delete the node 'p'.
/// @param p A node of the tree.
void deleteNode(Node *p);

/// @brief Add the new tile to the board of the game.
/// @param board Board of the game.
/// @param row Row to play in.
/// @param col Column to play in.
/// @param level Level of the tree in which we are doing the play.
void makePlay(char board[NROWS][NCOLS], int row, int col, int level);

/// @brief Copies the board 'src' to the board 'dest'.
/// @param dest Board copied from 'src'.
/// @param src Board to copy to 'dest'.
void copyBoard(char dest[NROWS][NCOLS], char src[NROWS][NCOLS]);

/// @brief Decides which column does the computer have to play in.
/// @param p The node in which we are making the choice.
/// @return The number of the column in which the computer has to play.
int makeChoice(Node *p);

/// @brief Implements the Minimax algorithm.
/// @param p The node in which we are doing the Minimax algorithm.
/// @return The value that gives the Minimax algorithm.
int minimax(Node *p);

char whichPlayer(int level);

// void deleteTree(Node *p);
// void printTree(Node *p);

#endif
