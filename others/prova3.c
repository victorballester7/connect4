#include <stdio.h>
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))  // maximum of two values
void numRowsAndCols(FILE* fp, int* nrows, int* ncols) {
  char c;
  int aux_ncols = 0;
  while (!feof(fp)) {
    c = fgetc(fp);
    if (c == '\n') {
      (*nrows)++;
      (*ncols) = MAX(*ncols, aux_ncols);
      aux_ncols = 0;
      continue;
    }
    aux_ncols++;
  }
}

int main() {
  FILE* fp = fopen("resources/logo1.txt", "r");
  if (fp == NULL) {
    printf("Error opening the file. Exiting.\n");
    return 0;
  }
  int r = 0, c = 0;
  numLines(fp, &r, &c);
  printf("El nombre de lines es %i i cols = %i.\n", r, c);
  return 0;
}
