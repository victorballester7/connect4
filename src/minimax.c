#include "../include/minimax.h"

#include "../include/extra.h"
int DEPTH = 10;  // Number of levels on the Minimax algorithm.
extern int NROWS, NCOLS;

// int alphaBetaTree(Node *p) {
//   int eval, *v;
//   if (p->n_children == 0) {
//     p->value = heuristicFunction(p->board, whichPlayer(p->level));
//     return p->value;
//   }
//   if (p->level % 2 == 0) {  // computer's-turn level, i.e. maximizing level
//     p->value = -INF;
//     for (int i = 0; i < p->n_children; i++) {
//       v = order1Level(p);
//       p->children[i] = createNode(p, v[i]);
//       if (p->children[i]->value == INF) {  // if there is 4-in-a-row in some child, don't create more trees and delete its brothers!! But only if the level of the p is greater than 1. Because if not, it may disturb the right column to play in.
//         p->value = INF;
//         p->alpha = INF;
//         break;
//       }
//       p->children[i]->alpha = p->alpha;
//       p->children[i]->beta = p->beta;
//       eval = alphaBetaTree(p->children[i]);
//       p->value = MAX(p->value, eval);
//       p->alpha = MAX(p->alpha, p->value);
//       if (p->beta <= p->alpha) break;  // alpha pruning
//     }
//   } else {  // player's-turn level, i.e. minimizing level
//     p->value = INF;
//     for (int i = 0; i < p->n_children; i++) {
//       v = order1Level(p);
//       p->children[i] = createNode(p, v[i]);
//       if (p->children[i]->value == -INF) {  // if there is 4-in-a-row in some child, don't create more trees and delete its brothers!! But only if the level of the p is greater than 1. Because if not, it may disturb the right column to play in.
//         p->value = -INF;
//         p->beta = -INF;
//         break;
//       }
//       p->children[i]->alpha = p->alpha;
//       p->children[i]->beta = p->beta;
//       eval = alphaBetaTree(p->children[i]);
//       p->value = MIN(p->value, eval);
//       p->beta = MIN(p->beta, p->value);
//       if (p->beta <= p->alpha) break;  // beta pruning
//     }
//   }
//   if (p->level == 1) printf("Real column: %i, Value: %i\n", p->colToPlay, p->value);
//   // if (p->value == -64500 || p->value == -39500 || p->value == -40600) {
//   //   printf("Level %i: Value %i\n", p->level, p->value);
//   // }
//   // printBoard(p->board)
//   if (p->level == 0) {
//     int choice = makeChoice(p);
//     delete1Level(p);
//     return choice;
//   }
//   delete1Level(p);
//   return p->value;
// }

int alphaBetaTree(Node *p) {
  int eval;
  if (p->n_children == 0) {
    p->value = heuristicFunction(p->board, whichPlayer(p->level));
    return p->value;
  }
  if ((eval = create1Level(p, true)) != 0) {
    if (p->level == 0) return p->colToPlay;
    return eval;
  }
  if (p->level % 2 == 0) {  // computer's-turn level, i.e. maximizing level
    p->value = -INF;
    for (int i = 0; i < p->n_children; i++) {
      p->children[i]->alpha = p->alpha;
      p->children[i]->beta = p->beta;
      eval = alphaBetaTree(p->children[i]);
      p->value = MAX(p->value, eval);
      p->alpha = MAX(p->alpha, p->value);
      if (p->beta <= p->alpha) break;  // alpha pruning
    }
  } else {  // player's-turn level, i.e. minimizing level
    p->value = INF;
    for (int i = 0; i < p->n_children; i++) {
      p->children[i]->alpha = p->alpha;
      p->children[i]->beta = p->beta;
      eval = alphaBetaTree(p->children[i]);
      p->value = MIN(p->value, eval);
      p->beta = MIN(p->beta, p->value);
      if (p->beta <= p->alpha) break;  // beta pruning
    }
  }
  // if (p->level == 1) printf("Real column: %i, Value: %i\n", p->colToPlay, p->value);
  // if (p->value == INF) {
  //   printf("Level %i: Value %i\n", p->level, p->value);
  //   printBoard(p->board);
  // }
  if (p->level == 0) {
    int choice = makeChoice(p);
    delete1Level(p);
    return choice;
  }
  delete1Level(p);
  return p->value;
}

// int eval;
// if ((eval = create1Level(p, false)) != 0) {  // if the next play is 4-in-a-row
//   if (p->level == 0) return p->colToPlay;    // if we are in the root
// } else {
//   for (int i = 0; i < p->n_children; i++) {
//     if (p->children[i] == NULL) continue;
//     if (p->children[i]->n_children == 0) {
//       p->children[i]
//           ->value = heuristicFunction(p->children[i]->board, whichPlayer(p->children[i]->level));
//       // printf("LEVEL: %i.", p->level);
//       // printf("NumChildren: %i/%i. value: %i\n", i, p->n_children, p->children[i]->value);
//       // printBoard(p->children[i]->board);
//       continue;
//     }  // if a child is a leaf, continue (continue instead of break because we have to assign values on each iteration).
//     createTree(p->children[i]);
//   }
// }

int computeColumn(char **board, int i) {  // computes the i-th column that is still not full.
  int count = 0;
  for (int j = 0; j < NCOLS; j++) {
    if (board[0][j] == '0') {
      if (count == i) return j;
      count++;
    }
  }
  return -1;
}

int computeRow(char **board, int col) {  // computes the first empty row in the i-th column that is still not full.
  int k = NROWS - 1;
  if (col == -1) return -1;
  while (k >= 0 && board[k][col] != '0') k--;
  return k;
}

int computerPlay(char **board) {
  Node *root = createFirstNode(board);
  // printf("------------------------");
  // int choice = createTree(root);  // convert the p->value of the root node into the column the computer wants to play in.
  int choice = alphaBetaTree(root);
  deleteNode(root);
  return choice;
}

void copyBoard(char **dest, char **src) {  // copies the 'dest' board to the 'src' board.
  for (int i = 0; i < NROWS; i++) {
    for (int j = 0; j < NCOLS; j++)
      dest[i][j] = src[i][j];
  }
}

// void copyNode(Node *dest, Node *src) {
//   dest->level = src->level;
//   for (int j = 0; j < src->n_children; j++) *(dest->children[j]) = *(src->children[j]);
//   dest->n_children = src->n_children;
//   for (int j = 0; j < NROWS; j++) *(dest->board[j]) = *(src->board[j]);
//   dest->value = src->value;
//   dest->alpha = src->alpha;
//   dest->beta = src->beta;
//   dest->colToPlay = src->colToPlay;
// }

int create1Level(Node *father, bool alphaBeta) {  // create one level of the tree (i.e. including all its nodes)
  int *v;                                         // this contains the columns to play for each child (child i => column v[i])
  if (alphaBeta)
    v = order1Level(father);
  else {
    v = malloc(father->n_children * sizeof(int));
    for (int i = 0; i < father->n_children; i++) v[i] = computeColumn(father->board, i);
  }

  // printBoard(father->board);
  // printf("v: ");
  // for (int i = 0; i < father->n_children; i++) {
  //   printf("%i ", v[i]);
  // }
  // printf("\n");

  for (int i = 0; i < father->n_children; i++) {  // Obs: i is the number of the child; (in general) not the same as the number of the column to play in.
    // printBoard(father->board);
    father->children[i] = createNode(father, v[i]);

    // if (father->level >= 1 && (father->children[i]->value == INF || father->children[i]->value == -INF)) {  // if there is 4-in-a-row in some child, don't create more trees and delete its brothers!! But only if the level of the father is greater than 1. Because if not, it may disturb the right column to play in.
    //   father->n_children = 1;
    //   *(father->children[0]) = *(father->children[i]);
    //   for (int j = 1; j <= i; j++) deleteNode(father->children[j]);
    //   break;
    // }
    if (father->children[i]->value >= INF / 2 || father->children[i]->value <= -INF / 2) {  // if there is 4-in-a-row in some child, don't create more trees and delete its brothers!! But only if the level of the father is greater than 1. Because if not, it may disturb the right column to play in.
      if (father->level >= 1) {
        father->n_children = 1;
        // **(father->children[0]->board) = **(father->children[i]->board);
        // father->children[0]->level = father->children[i]->level;
        father->children[0]->alpha = father->children[i]->alpha;
        father->children[0]->beta = father->children[i]->beta;
        father->children[0]->value = father->children[i]->value;
        father->children[0]->n_children = father->children[i]->n_children;
        for (int j = 0; j < NROWS; j++) *(father->children[0]->board[j]) = *(father->children[i]->board[j]);
        // copyNode(father->children[0], father->children[i]);
        for (int j = 1; j <= i; j++) deleteNode(father->children[j]);
        father->value = father->children[0]->value;
        free(v);
        return father->value;  // = +/- INF
      } else {                 // if father->level == 0 ==> father->children[i]->value == INF
        // we store the index of the important child and delete all of them.
        father->value = i;  // this doesn't make any sense but, we reuse a variable to store the component i-th.
        father->colToPlay = v[i];
        for (int j = 0; j <= i; j++) deleteNode(father->children[j]);
        free(v);
        return 1;
      }
    }
  }
  free(v);
  return 0;
}

Node *createFirstNode(char **board) {
  Node *p = malloc(sizeof(Node));
  p->level = 0;
  p->alpha = -INF;
  p->beta = INF;
  p->board = (char **)malloc(NROWS * sizeof(char *));
  for (int i = 0; i < NROWS; i++)
    p->board[i] = (char *)malloc(NCOLS * sizeof(char));
  copyBoard(p->board, board);
  p->n_children = computeNumChilds(p->board);
  p->children = malloc(p->n_children * sizeof(Node *));
  return p;
}

// Node *createNode(Node *father, int child_index) {
//   Node *p = malloc(sizeof(Node));
//   if (p == NULL) {
//     attron(COLOR_PAIR(9));
//     mvprintw(LINES - 1, 0, "Error allocating memory (node).\n");
//     attroff(COLOR_PAIR(9));
//     // printf("Error allocating memory (node).\n");
//     return NULL;
//   }
//   p->level = father->level + 1;
//   // p->board = (char **)malloc(NROWS * sizeof(char *));
//   p->board = (char **)malloc(NROWS * sizeof(char *));
//   if (p->board == NULL) {
//     attron(COLOR_PAIR(9));
//     mvprintw(LINES - 1, 0, "Error allocating memory (board node).\n");
//     attroff(COLOR_PAIR(9));
//     // printf("Error allocating memory (node).\n");
//     return NULL;
//   }
//   for (int i = 0; i < NROWS; i++) {
//     p->board[i] = (char *)malloc(NCOLS * sizeof(char));
//     if (p->board[i] == NULL) {
//       attron(COLOR_PAIR(9));
//       mvprintw(LINES - 1, 0, "Error allocating memory (board node).\n");
//       attroff(COLOR_PAIR(9));
//       // printf("Error allocating memory (node).\n");
//       return NULL;
//     }
//   }
//   copyBoard(p->board, father->board);
//   int col = computeColumn(p->board, child_index);
//   int row = computeRow(p->board, col);
//   makePlay(p->board, row, col, p->level);
//   p->value = 0;  // we give a default value of 0 in order to avoid problems.
//   int i;
//   if (!(i = is4InRow(p->board, col)) && p->level < DEPTH) {
//     p->n_children = computeNumChilds(p->board);
//     p->children = malloc(p->n_children * sizeof(Node *));
//     if (p->children == NULL) {
//       attron(COLOR_PAIR(9));
//       mvprintw(LINES - 1, 0, "Error allocating memory (children).\n");
//       attroff(COLOR_PAIR(9));
//       return p;
//     }
//   } else {  // is leaf or there is 4-in-a-row in this play
//     p->n_children = 0;
//     p->children = NULL;
//     // assign  INF to p->value if there is 4-in-a-row by the computer
//     // assign -INF to p->value if there is 4-in-a-row by the player
//     if (i == 1) p->value = INF * ((p->level % 2 == 1) ? (1) : (-1));
//   }
//   return p;
// }

Node *createNode(Node *father, int col) {
  Node *p = malloc(sizeof(Node));
  if (p == NULL) {
    attron(COLOR_PAIR(9));
    mvprintw(LINES - 1, 0, "Error allocating memory (node).\n");
    attroff(COLOR_PAIR(9));
    // printf("Error allocating memory (node).\n");
    return NULL;
  }
  p->level = father->level + 1;
  p->board = (char **)malloc(NROWS * sizeof(char *));
  if (p->board == NULL) {
    attron(COLOR_PAIR(9));
    mvprintw(LINES - 1, 0, "Error allocating memory (board node).\n");
    attroff(COLOR_PAIR(9));
    // printf("Error allocating memory (node).\n");
    return NULL;
  }
  for (int i = 0; i < NROWS; i++) {
    p->board[i] = (char *)malloc(NCOLS * sizeof(char));
    if (p->board[i] == NULL) {
      attron(COLOR_PAIR(9));
      mvprintw(LINES - 1, 0, "Error allocating memory (board node).\n");
      attroff(COLOR_PAIR(9));
      // printf("Error allocating memory (node).\n");
      return NULL;
    }
  }
  copyBoard(p->board, father->board);
  int row = computeRow(p->board, col);
  p->colToPlay = col;
  makePlay(p->board, row, p->colToPlay, p->level);
  p->value = 0;  // we give a default value of 0 in order to avoid problems.
  int i;
  if (!(i = is4InRow(p->board, p->colToPlay)) && p->level < DEPTH) {
    p->n_children = computeNumChilds(p->board);
    p->children = malloc(p->n_children * sizeof(Node *));
    if (p->children == NULL) {
      attron(COLOR_PAIR(9));
      mvprintw(LINES - 1, 0, "Error allocating memory (children).\n");
      attroff(COLOR_PAIR(9));
      return p;
    }
  } else {  // is leaf or there is 4-in-a-row in this play
    p->n_children = 0;
    p->children = NULL;
    // assign  INF to p->value if there is 4-in-a-row by the computer
    // assign -INF to p->value if there is 4-in-a-row by the player
    if (i == 1) {
      if (p->level % 2 == 1)
        p->value = INF - p->level;
      else
        p->value = -INF + p->level;
    }
  }
  return p;
}

// This function supposes that we have just created a root node and its child array has been also created.
int **createSmallTree(Node *p) {
  int **v;
  int eval;
  if (p->level == 0) {
    v = malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++)
      v[i] = malloc(p->n_children * sizeof(int));
  }
  if ((eval = create1Level(p, false)) != 0) {  // if the next play is 4-in-a-row
    if (p->level == 0) {                       // if we are in the root
      for (int i = 0; i < p->n_children; i++) {
        if (i == p->value) {
          v[0][i] = p->colToPlay;
          v[1][i] = INF;
        } else {
          v[0][i] = computeColumn(p->board, i);
          v[1][i] = 0;
        }
      }
      return v;
    }
  } else {
    for (int i = 0; i < p->n_children; i++) {
      if (p->children[i] == NULL) continue;
      if (p->children[i]->n_children == 0) {
        p->children[i]
            ->value = heuristicFunction(p->children[i]->board, whichPlayer(p->children[i]->level));
        // printf("LEVEL: %i.", p->level);
        // printf("NumChildren: %i/%i. value: %i\n", i, p->n_children, p->children[i]->value);
        // printBoard(p->children[i]->board);
        continue;
      }  // if a child is a leaf, continue (continue instead of break because we have to assign values on each iteration).
      createSmallTree(p->children[i]);
    }
  }
  // printBoard(p->board);

  // printf("LEVEL %i: value: %i\n", p->level, p->value);

  if (p->level == 0) {
    for (int i = 0; i < p->n_children; i++) {
      v[0][i] = p->children[i]->colToPlay;
      v[1][i] = p->children[i]->value;
    }
  } else
    p->value = minimax(p);
  delete1Level(p);

  return v;
}

// This function supposes that we have just created a root node and its child array has been also created.
int createTree(Node *p) {
  int eval;
  if ((eval = create1Level(p, false)) != 0) {  // if the next play is 4-in-a-row
    if (p->level == 0) return p->colToPlay;    // if we are in the root
  } else {
    for (int i = 0; i < p->n_children; i++) {
      if (p->children[i] == NULL) continue;
      if (p->children[i]->n_children == 0) {
        p->children[i]
            ->value = heuristicFunction(p->children[i]->board, whichPlayer(p->children[i]->level));
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

  if (p->level == 0) {
    int choice = makeChoice(p);
    delete1Level(p);
    return choice;
  }
  delete1Level(p);

  return 0;
}

void delete1Level(Node *father) {  // delete level of the children of father.
  for (int i = 0; i < father->n_children; i++)
    deleteNode(father->children[i]);
}

void deleteNode(Node *p) {  // delete node p.
  free(p->children);
  for (int i = 0; i < NROWS; i++) free(p->board[i]);
  free(p->board);
  free(p);
}

int makeChoice(Node *p) {  // returns the best column to play in.
  int i = -1;
  while (p->children[++i]->value != p->value) continue;
  return p->children[i]->colToPlay;
}

void makePlay(char **board, int row, int col, int level) {
  // if (level % 2 == 0 )  // player's turn
  //   board[row][col] = '2';
  // else  // computer's turn
  //   board[row][col] = '1';
  if (level % 2 == 0)  // player's turn
    board[row][col] = '2';
  else  // player's turn
    board[row][col] = '1';
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

// int *order1Level(Node *father, bool alphaBeta) {
//   int *u = malloc(father->n_children * sizeof(int));
//   int middle = father->n_children / 2;
//   if (father->n_children % 2 == 1) {
//     for (int i = 0; i <= middle; i++) {
//       if (i == 0)
//         u[0] = computeColumn(father->board, middle);
//       else {
//         u[2 * i - 1] = computeColumn(father->board, middle - i);
//         u[2 * i] = computeColumn(father->board, middle + i);
//       }
//     }
//   } else {
//     for (int i = 0; i < middle; i++) {
//       if (i == 0) {
//         u[0] = computeColumn(father->board, middle - 1);
//         u[1] = computeColumn(father->board, middle);
//       } else {
//         u[2 * i] = computeColumn(father->board, middle - i - 1);
//         u[2 * i + 1] = computeColumn(father->board, middle + i);
//       }
//     }
//   }
//   return u;
// }

// int *order1Level(Node *father, bool alphaBeta) {
//   int col, row, j, h;
//   int *u = malloc(father->n_children * sizeof(int));
//   if (!alphaBeta) {
//     for (int i = 0; i < father->n_children; i++) u[i] = computeColumn(father->board, i);
//     return u;
//   }
//   int **v = malloc(2 * sizeof(int *));
//   for (int i = 0; i < 2; i++)
//     v[i] = malloc(father->n_children * sizeof(int));
//   char **board = (char **)malloc(NROWS * sizeof(char *));
//   for (int i = 0; i < NROWS; i++) {
//     board[i] = (char *)malloc(NCOLS * sizeof(char));
//   }
//   copyBoard(board, father->board);
//   char player = otherPlayer(whichPlayer(father->level));
//   // int DEPTH_AUX = DEPTH;
//   // DEPTH = 2;
//   // v = createSmallTree(father, father->level);
//   // int row1, row2;
//   // for (int i = 1; i < father->n_children; i++) {
//   //   row1 = v[0][i];
//   //   row2 = v[1][i];
//   //   j = -1;
//   //   if (player == '1')  // we order from best (+) to worst (-)
//   //     while (++j < i && v[1][j] >= v[1][i]) continue;
//   //   else  // we order from worst (-) to best (+)
//   //     while (++j < i && v[1][j] <= v[1][i]) continue;
//   //   for (int k = i - 1; k >= j; k--) {
//   //     v[0][k + 1] = v[0][k];
//   //     v[1][k + 1] = v[1][k];
//   //   }
//   //   v[0][j] = row1;
//   //   v[1][j] = row2;
//   // }
//   // DEPTH = DEPTH_AUX;
//   for (int i = 0; i < father->n_children; i++) {
//     if (i >= 1) board[row][col] = '0';
//     col = computeColumn(board, i);
//     row = computeRow(board, col);
//     board[row][col] = player;
//     if (i >= 1) {
//       h = heuristicFunction(board, player);
//       j = -1;
//       if (player == '1')  // we order from best (+) to worst (-)
//         while (++j < i && v[1][j] >= h) continue;
//       else  // we order from worst (-) to best (+)
//         while (++j < i && v[1][j] <= h) continue;
//       for (int k = i - 1; k >= j; k--) {
//         v[0][k + 1] = v[0][k];
//         v[1][k + 1] = v[1][k];
//       }
//       v[0][j] = col;
//       v[1][j] = h;
//     } else {
//       v[0][i] = col;
//       v[1][i] = heuristicFunction(board, player);
//     }
//   }
//   for (int i = 0; i < NROWS; i++) free(board[i]);
//   free(board);
//   for (int i = 0; i < father->n_children; i++) u[i] = v[0][i];
//   free(v[0]);
//   free(v[1]);
//   free(v);
//   return u;
// }

int *order1Level(Node *father) {
  int *u = malloc(father->n_children * sizeof(int));
  int numTiles = 0;
  for (int i = 0; i < NROWS; i++) {
    for (int j = 0; j < NCOLS; j++)
      numTiles += father->board[i][j] / 49;  // we divide by 49 because '0' = 48 and '0' is not a tile ==> it shouldn't contribute to the sum whereas '1' = 49 and '2' = 50 should do it.
  }
  if (numTiles < 6) {
    int middle = father->n_children / 2;
    if (father->n_children % 2 == 1) {
      for (int i = 0; i <= middle; i++) {
        if (i == 0)
          u[0] = computeColumn(father->board, middle);
        else {
          u[2 * i - 1] = computeColumn(father->board, middle - i);
          u[2 * i] = computeColumn(father->board, middle + i);
        }
      }
    } else {
      for (int i = 0; i < middle; i++) {
        if (i == 0) {
          u[0] = computeColumn(father->board, middle - 1);
          u[1] = computeColumn(father->board, middle);
        } else {
          u[2 * i] = computeColumn(father->board, middle - i - 1);
          u[2 * i + 1] = computeColumn(father->board, middle + i);
        }
      }
    }
    return u;
  }
  int col, row, j, h;
  int *v = malloc(father->n_children * sizeof(int));
  char **board = (char **)malloc(NROWS * sizeof(char *));
  for (int i = 0; i < NROWS; i++) {
    board[i] = (char *)malloc(NCOLS * sizeof(char));
  }
  copyBoard(board, father->board);
  char player = otherPlayer(whichPlayer(father->level));
  for (int i = 0; i < father->n_children; i++) {
    if (i >= 1) board[row][col] = '0';
    col = computeColumn(board, i);
    row = computeRow(board, col);
    board[row][col] = player;
    if (i >= 1) {
      h = heuristicFunction(board, player);
      j = -1;
      if (player == '1')  // we order u from best (+) to worst (-) depending on the values of v
        while (++j < i && v[j] >= h) continue;
      else  // we order u from worst (-) to best (+) depending on the values of v
        while (++j < i && v[j] <= h) continue;
      for (int k = i - 1; k >= j; k--) {
        u[k + 1] = u[k];
        v[k + 1] = v[k];
      }
      u[j] = col;
      v[j] = h;
    } else {
      u[i] = col;
      v[i] = heuristicFunction(board, player);
    }
  }
  for (int i = 0; i < NROWS; i++) free(board[i]);
  free(board);
  free(v);
  return u;
  // int j;
  // int **v = malloc(2 * sizeof(int *));
  // for (int i = 0; i < 2; i++)
  //   v[i] = malloc(father->n_children * sizeof(int));
  // char player = otherPlayer(whichPlayer(father->level));
  // int DEPTH_AUX = DEPTH;
  // DEPTH = 1;
  // Node *p = createFirstNode(father->board);
  // v = createSmallTree(p);
  // int row1, row2;
  // for (int i = 1; i < p->n_children; i++) {
  //   row1 = v[0][i];
  //   row2 = v[1][i];
  //   j = -1;
  //   if (player == '1')  // we order from best (+) to worst (-)
  //     while (++j < i && v[1][j] >= v[1][i]) continue;
  //   else  // we order from worst (-) to best (+)
  //     while (++j < i && v[1][j] <= v[1][i]) continue;
  //   for (int k = i - 1; k >= j; k--) {
  //     v[0][k + 1] = v[0][k];
  //     v[1][k + 1] = v[1][k];
  //   }
  //   v[0][j] = row1;
  //   v[1][j] = row2;
  // }
  // DEPTH = DEPTH_AUX;
  // for (int i = 0; i < p->n_children; i++) u[i] = v[0][i];
  // deleteNode(p);
  // free(v[0]);
  // free(v[1]);
  // free(v);
  // return u;
}

// int *order1Level(Node *father) {
//   int col, row, j, h;
//   int *u = malloc(father->n_children * sizeof(int));
//   int *v = malloc(father->n_children * sizeof(int));
//   char **board = (char **)malloc(NROWS * sizeof(char *));
//   for (int i = 0; i < NROWS; i++) {
//     board[i] = (char *)malloc(NCOLS * sizeof(char));
//   }
//   copyBoard(board, father->board);
//   char player = otherPlayer(whichPlayer(father->level));
//   for (int i = 0; i < father->n_children; i++) {
//     if (i >= 1) board[row][col] = '0';
//     col = computeColumn(board, i);
//     row = computeRow(board, col);
//     board[row][col] = player;
//     if (i >= 1) {
//       h = heuristicFunction(board, player);
//       j = -1;
//       if (player == '1')  // we order u from best (+) to worst (-) depending on the values of v
//         while (++j < i && v[j] >= h) continue;
//       else  // we order u from worst (-) to best (+) depending on the values of v
//         while (++j < i && v[j] <= h) continue;
//       for (int k = i - 1; k >= j; k--) {
//         u[k + 1] = u[k];
//         v[k + 1] = v[k];
//       }
//       u[j] = col;
//       v[j] = h;
//     } else {
//       u[i] = col;
//       v[i] = heuristicFunction(board, player);
//     }
//   }
//   for (int i = 0; i < NROWS; i++) free(board[i]);
//   free(board);
//   free(v);
//   return u;
// }

char whichPlayer(int level) {           // level = level of the tree (keeping in mind that the level of the root is 0).
  return (level % 2 == 0) ? '2' : '1';  // '2' = player's turn, '1' = computer's turn
}
