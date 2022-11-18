#include <menu.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>  // added for exit() function
#include <string.h>

void fail(char *msg) {
  endwin();
  puts(msg);
  exit(EXIT_FAILURE);
}

int nProduct(int n, int times) {
  int i = 0, result = 1;
  while (i++ < times) result *= n;
  return result;
}

int main(int argc, char **argv) {
  /* Commandline argument currently unused */
  printf("%d %d %d\n", nProduct(0, 10), nProduct(2, 0), nProduct(3, 3));
}
