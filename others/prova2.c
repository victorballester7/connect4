#define _GNU_SOURCE
#include <menu.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>  // added for exit() function
#include <string.h>
#include <sys/types.h>

// void fail(char *msg) {
//   endwin();
//   puts(msg);
//   exit(EXIT_FAILURE);
// }

// int nProduct(int n, int times) {
//   int i = 0, result = 1;
//   while (i++ < times) result *= n;
//   return result;
// }

void uploadFile() {
  FILE* fp;
  char* fileName = "resources/logo1.txt";
  size_t size;
  ssize_t nread;
  char* line;
  fp = fopen(fileName, "r");
  if (fp == NULL) {
    printf("Error opening the file. Exiting.\n");
    return;
  }
  char s[500];
  // printf("%s", s);
  while (fgets(s, sizeof(s), fp)) {
    printf("%s", s);
  }

  // while ((nread = getline(&line, &size, fp)) != -1) {
  //   printf("%s", line);
  // }
  fclose(fp);
}
int main() {
  /* Commandline argument currently unused */
  // printf("%d %d %d\n", nProduct(0, 10), nProduct(2, 0), nProduct(3, 3));
  uploadFile();
}
