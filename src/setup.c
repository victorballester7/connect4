#include "../include/setup.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* fileNameCreation() {
  char *fileName = malloc(25 * sizeof(char)), cwd[1024];  // cwd = current working directory
  pwd(cwd, sizeof(cwd));
  strcpy(fileName, (strcmp(cwd + (strlen(cwd) - 4), "/bin")) ? "data/statistics.txt" : "../data/statistics.txt");  // to prevent error when compiling with 'make run' from outside of the directory /bin or from inside of the directory 'bin'.
  return fileName;
}

void uploadFile(char i) {
  FILE* fp;
  char* fileName = fileNameCreation();
  fp = fopen(fileName, "r+");
  if (fp == NULL) {
    printf("Error opening the file. Exiting.\n");
    return;
  }
  int played, won, lost, tied;
  fscanf(fp, "Games played: %d\nGames won (by the computer): %d\nGames lost (by the computer): %d\nGames tied: %d\n", &played, &won, &lost, &tied);
  rewind(fp);  // setting the file pointer at the beginning of the file.
  played++;
  (i == '0') ? (tied++) : ((i == '1') ? won++ : lost++);
  fprintf(fp, "Games played: %d\nGames won (by the computer): %d\nGames lost (by the computer): %d\nGames tied: %d\n", played, won, lost, tied);
  fclose(fp);
  free(fileName);
  fileName = NULL;
}

int presentation() {
  printf("Welcome to Connect4!\n");
  int choice;
  do {
    printf("What do you want to do?\n1) Play a new game\n2) See statistics\n3) Change tile color\n4) Exit");
    scanf("%i", &choice);
    switch (choice) {
      case 1:
        return 0;
      case 2: {
        FILE* fp;
        char* fileName = fileNameCreation();
        fp = fopen(fileName, "r");
        if (fp == NULL) {
          printf("Error opening the file. Exiting.\n");
          return 1;
        }
        int played, won, lost, tied;
        fscanf(fp, "Games played: %d\nGames won (by the computer): %d\nGames lost (by the computer): %d\nGames tied: %d\n", &played, &won, &lost, &tied);
        fclose(fp);
        free(fileName);
        fileName = NULL;
        printf("Games played: %d\nWin rate (by the computer): %.2lf\nLose rate (by the computer): %.2lf\nTie rate: %.2lf\n", played, won * 100. / played, lost * 100. / played, tied * 100. / played);
      }
      case 3:
        return 2;
      case 4:
        return 1;
      default:
        printf("Error entering the data. Exiting");
        return 1;
    }
  } while (choice == 2);
}
