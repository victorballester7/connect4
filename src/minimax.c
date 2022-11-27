#include "../include/minimax.h"

int DEPTH = 3;  // Number of levels on the Minimax algorithm.
extern const int NROWS, NCOLS;

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
extern char player_comp;

void makePlay(char board[NROWS][NCOLS], int row, int col, int level) {
  // if (level % 2 == 0 )  // player's turn
  //   board[row][col] = '2';
  // else  // computer's turn
  //   board[row][col] = '1';
  if (level % 2 == 0 && player_comp == '1')  // player's turn
    board[row][col] = '2';
  else if (level % 2 == 1 && player_comp == '1')  // player's turn
    board[row][col] = '1';
  else if (level % 2 == 0 && player_comp == '2')  // computer's turn
    board[row][col] = '1';
  else if (level % 2 == 1 && player_comp == '2')  // computer's turn
    board[row][col] = '2';
}

Node *createFirstNode(char board[NROWS][NCOLS]) {  // Obs: It seems that is missing a parameter (professor message)
  Node *p = malloc(sizeof(Node));
  p->level = 0;
  p->alpha = -INF;
  p->beta = INF;
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
  p->alpha = father->alpha;
  p->beta = father->beta;
  copyBoard(p->board, father->board);
  int col = computeColumn(p->board, child_index);
  int row = computeRow(p->board, col);
  makePlay(p->board, row, col, p->level);
  // printBoard(p->board);
  p->value = 0;  // we give a default value of 0 in order to avoid problems.
  int i;
  if (!(i = is4InRow(p->board, col)) && p->level < DEPTH) {
    p->n_children = computeNumChilds(p->board);
    p->children = malloc(p->n_children * sizeof(Node *));
    if (p->children == NULL) {
      printf("Error allocating memory (children).\n");
      return p;
    }
  } else {  // is leaf or there is 4-in-a-row in this play
    p->n_children = 0;
    p->children = NULL;
    // assign  INF to p->value if there is 4-in-a-row by the computer
    // assign -INF to p->value if there is 4-in-a-row by the player
    if (i == 1) p->value = INF * ((p->level % 2 == 1) ? (1) : (-1));
  }

  // else if (p->level == DEPTH) {  // is leaf or there is 4-in-a-row in this play
  //   p->n_children = 0;
  //   p->children = NULL;
  // }

  // else {  // there is 4-in-a-row.
  //   // p->value = INF;
  //   p->n_children = 0;
  //   p->children = NULL;
  // }
  return p;
}

int create1Level(Node *father) {                  // create one level of the tree (i.e. including all its nodes)
  for (int i = 0; i < father->n_children; i++) {  // Obs: i is the number of the child; (in general) not the same as the number of the column to play in.
    father->children[i] = createNode(father, i);
    // if (father->level >= 1 && (father->children[i]->value == INF || father->children[i]->value == -INF)) {  // if there is 4-in-a-row in some child, don't create more trees and delete its brothers!! But only if the level of the father is greater than 1. Because if not, it may disturb the right column to play in.
    //   father->n_children = 1;
    //   *(father->children[0]) = *(father->children[i]);
    //   for (int j = 1; j <= i; j++) deleteNode(father->children[j]);
    //   break;
    // }
    if (father->children[i]->value == INF || father->children[i]->value == -INF) {  // if there is 4-in-a-row in some child, don't create more trees and delete its brothers!! But only if the level of the father is greater than 1. Because if not, it may disturb the right column to play in.
      if (father->level >= 1) {
        father->n_children = 1;
        *(father->children[0]) = *(father->children[i]);
        for (int j = 1; j <= i; j++) deleteNode(father->children[j]);
      } else {  // if father->level == 0
        father->n_children = i;
        for (int j = 0; j <= i; j++) deleteNode(father->children[j]);
      }
      return -father->children[i]->value;
    }
  }
  return 0;
}

// int create1Level2(Node *father, int *v) {         // create one level of the tree (i.e. including all its nodes)
//   for (int i = 0; i < father->n_children; i++) {  // Obs: i is the number of the child; (in general) not the same as the number of the column to play in.
//     father->children[i] = createNode(father, i);
//     // if (father->level >= 1 && (father->children[i]->value == INF || father->children[i]->value == -INF)) {  // if there is 4-in-a-row in some child, don't create more trees and delete its brothers!! But only if the level of the father is greater than 1. Because if not, it may disturb the right column to play in.
//     //   father->n_children = 1;
//     //   *(father->children[0]) = *(father->children[i]);
//     //   for (int j = 1; j <= i; j++) deleteNode(father->children[j]);
//     //   break;
//     // }
//     if (father->children[i]->value == INF || father->children[i]->value == -INF) {  // if there is 4-in-a-row in some child, don't create more trees and delete its brothers!! But only if the level of the father is greater than 1. Because if not, it may disturb the right column to play in.
//       if (father->level >= 1) {
//         father->n_children = 1;
//         *(father->children[0]) = *(father->children[i]);
//         for (int j = 1; j <= i; j++) deleteNode(father->children[j]);
//       } else {
//         father->n_children = i;
//         for (int j = 0; j <= i; j++) deleteNode(father->children[j]);
//       }
//       return -father->children[i]->value;
//     }
//   }
//   return -1;
// }

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
int createTree(Node *p) {
  // printf("LEVEL: %i\n", p->level);
  // create1Level(p);
  // // if (p->n_children <= 1) {
  // //   printBoard(p->board);
  // // }
  int eval;
  if ((eval = create1Level(p)) != 0) {  // if we are in the root and the next play is 4-in-a-row
    if (p->level == 0)
      return computeColumn(p->board, p->n_children);
  } else {
    for (int i = 0; i < p->n_children; i++) {
      if (p->children[i]->n_children == 0) {
        p->children[i]
            ->value = heuristicFunction(p->children[i]->board);
        // printf("LEVEL: %i.", p->level);
        // printf("NumChildren: %i/%i. value: %i\n", i, p->n_children, p->children[i]->value);
        // printBoard(p->children[i]->board);
        continue;
      }  // if a child is a leaf, continue (continue instead of break because we have to assign values on each iteration).
      createTree(p->children[i]);
    }
  }
  // printBoard(p->board);
  p->value = minimax(p);
  // printf("LEVEL %i: value: %i\n", p->level, p->value);
  delete1Level(p);
  if (p->level == 0) return makeChoice(p);
  return 0;  // printf("VALUE LEVEL %i: %i\n", p->level, p->value);
}

int alphaBetaTree(Node *p) {
  int eval;
  if (p->n_children == 0) {
    p->value = heuristicFunction(p->board);
    return p->value;
  }
  // printf("Hola1\n");
  if ((eval = create1Level(p)) != -1) {
    if (p->level == 0) return computeColumn(p->board, p->n_children);
    return eval;
  }
  // printf("Hola2\n");
  if (p->level % 2 == 0) {  // computer's-play leve, i.e. maximizing level
    p->value = -INF;
    for (int i = 0; i < p->n_children; i++) {
      eval = alphaBetaTree(p->children[i]);
      p->value = MAX(p->value, eval);
      p->alpha = MAX(p->alpha, p->value);
      if (p->beta <= p->alpha) break;  // alpha pruning
    }
  } else {  // player's-play leve, i.e. minimizing level
    p->value = INF;
    for (int i = 0; i < p->n_children; i++) {
      eval = alphaBetaTree(p->children[i]);
      p->value = MIN(p->value, eval);
      p->beta = MIN(p->beta, p->value);
      if (p->beta <= p->alpha) break;  // beta pruning
    }
  }
  if (p->level == 0) {
    print1Level(p);
    printf("hola\n");
    printf("value of root: %d", p->value);
  }
  delete1Level(p);
  if (p->level == 0) return makeChoice(p);
  return p->value;
}

// int nProduct(int n, int times) {
//   int i = 0, result = 1;
//   while (i++ < times) result *= n;
//   return result;
// }

// int alphaBetaTree(Node *p) {
//   // static int v[nProduct(NCOLS,DEPTH)];

//   int eval;
//   if (p->n_children == 0) {
//     p->value = heuristicFunction(p->board);
//     return p->value;
//   }
//   // printf("Hola1\n");
//   if ((eval = create1Level2(p)) != -1) {
//     if (p->level == 0) return computeColumn(p->board, p->n_children);
//     return eval;
//   }
//   // printf("Hola2\n");
//   if (p->level % 2 == 0) {  // computer's-play leve, i.e. maximizing level
//     p->value = -INF;
//     for (int i = 0; i < p->n_children; i++) {
//       eval = alphaBetaTree(p->children[i]);
//       p->value = MAX(p->value, eval);
//       p->alpha = MAX(p->alpha, p->value);
//       if (p->beta <= p->alpha) break;  // alpha pruning
//     }
//   } else {  // player's-play leve, i.e. minimizing level
//     p->value = INF;
//     for (int i = 0; i < p->n_children; i++) {
//       eval = alphaBetaTree(p->children[i]);
//       p->value = MIN(p->value, eval);
//       p->beta = MIN(p->beta, p->value);
//       if (p->beta <= p->alpha) break;  // beta pruning
//     }
//   }
//   if (p->level == 0) {
//     print1Level(p);
//     // printf("hola\n");
//     // printf("value of root: %d", p->value);
//   }
//   delete1Level(p);
//   if (p->level == 0) return makeChoice(p);
//   return p->value;
// }

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

void print1Level(Node *father) {                  // create one level of the tree (i.e. including all its nodes)
  for (int i = 0; i < father->n_children; i++) {  // Obs: i is the number of the child; (in general) not the same as the number of the column to play in.
    printf("child %i (level %d): %d\n", i, father->level + 1, father->children[i]->value);
  }
}

int computerPlay(char board[NROWS][NCOLS]) {
  Node *root = createFirstNode(board);
  // printf("------------------------");
  int choice = createTree(root);  // convert the p->value of the root node into the column the computer wants to play in.
  // int choice = alphaBetaTree(root);
  deleteNode(root);
  return choice;
}
