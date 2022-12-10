#include "../include/minimax.h"

#include "../include/extra.h"
int DEPTH = 10;  // Number of levels on the Minimax algorithm.
extern int NROWS, NCOLS;

int alphaBetaTree(Node *p) {
  int eval;
  if (p->n_children == 0) {
    p->value = heuristicFunction(p->board, whichPlayer(p->level));
    return p->value;
  }
  // printBoard(p->board);
  if ((eval = create1Level(p)) != 0) {
    if (p->level == 0) return computeColumn(p->board, p->n_children);
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
  if (p->level == 0) {
    int choice = makeChoice(p);
    delete1Level(p);
    return choice;
  }
  delete1Level(p);
  return p->value;
}

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

int create1Level(Node *father) {                  // create one level of the tree (i.e. including all its nodes)
  for (int i = 0; i < father->n_children; i++) {  // Obs: i is the number of the child; (in general) not the same as the number of the column to play in.
    // printBoard(father->board);
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
        // **(father->children[0]->board) = **(father->children[i]->board);
        // father->children[0]->level = father->children[i]->level;
        father->children[0]->alpha = father->children[i]->alpha;
        father->children[0]->beta = father->children[i]->beta;
        father->children[0]->value = father->children[i]->value;
        father->children[0]->n_children = father->children[i]->n_children;
        for (int j = 0; j < NROWS; j++) *(father->children[0]->board[j]) = *(father->children[i]->board[j]);
        for (int j = 1; j <= i; j++) deleteNode(father->children[j]);
        father->value = father->children[0]->value;
        return father->value;
      } else {                   // if father->level == 0
        father->n_children = i;  // we store the index of the important child and delete all of them.
        for (int j = 0; j <= i; j++) deleteNode(father->children[j]);
        return 1;
      }
    }
  }
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

Node *createNode(Node *father, int child_index) {
  Node *p = malloc(sizeof(Node));
  if (p == NULL) {
    attron(COLOR_PAIR(9));
    mvprintw(LINES - 1, 0, "Error allocating memory (node).\n");
    attroff(COLOR_PAIR(9));
    // printf("Error allocating memory (node).\n");
    return NULL;
  }
  p->level = father->level + 1;
  // p->board = (char **)malloc(NROWS * sizeof(char *));
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
  int col = computeColumn(p->board, child_index);
  int row = computeRow(p->board, col);
  makePlay(p->board, row, col, p->level);
  p->value = 0;  // we give a default value of 0 in order to avoid problems.
  int i;
  if (!(i = is4InRow(p->board, col)) && p->level < DEPTH) {
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
    if (i == 1) p->value = INF * ((p->level % 2 == 1) ? (1) : (-1));
  }
  return p;
}

// This function supposes that we have just created a root node and its child array has been also created.
int createTree(Node *p) {
  int eval;
  if ((eval = create1Level(p)) != 0) {  // if the next play is 4-in-a-row
    if (p->level == 0)                  // if we are in the root
      return computeColumn(p->board, p->n_children);
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
  // if (p->board != NULL) {
  for (int i = 0; i < NROWS; i++)
    free(p->board[i]);
  // Seems to be a double free
  free(p->board);
  //   p->board = NULL;
  // }
  free(p);
}

int makeChoice(Node *p) {  // returns the best column to play in.
  int i = -1;
  while (p->children[++i]->value != p->value) continue;
  return computeColumn(p->board, i);
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

char whichPlayer(int level) {           // level = level of the tree (keeping in mind that the level of the root is 0).
  return (level % 2 == 0) ? '2' : '1';  // '2' = player's turn, '1' = computer's turn
}
