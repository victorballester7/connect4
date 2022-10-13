#include <curses.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX INT_MAX

char* base10to3(int i);
int search(char str[], char c) {
  for (int i = 0; i < strlen(str); i++)
    if (str[i] == 'c') return i;
  return -1;
}

char* extractString(char* str, int n, int m) {
  char* newStr = malloc((m - n + 2) * sizeof(char));
  for (int i = n; i <= m; i++) newStr[i - n] = str[i];
  // str[m - n + 1] = '\0';  // end of the string
  return newStr;
}

char* removeCenterChar(char* str) {
  int len = strlen(str);  // assume len is odd.
  char* newStr = malloc(7 * sizeof(char));
  for (int i = 0; i < (len - 1) / 2; i++) newStr[i] = str[i];
  for (int i = (len + 1) / 2; i < len; i++) newStr[i - 1] = str[i];
  // free(str);
  return newStr;
}

int main(void) {
  // initscr();      // initialize screen
  // start_color();  // start color variables

  // init_pair(1, COLOR_BLACK, COLOR_RED);
  // init_pair(2, COLOR_BLACK, COLOR_GREEN);

  // attron(COLOR_PAIR(1));
  // printw("This should be printed in black with a red background!\n");
  // printw("\u25CF\n");

  // attron(COLOR_PAIR(2));
  // printw("And this in a green background!\n");
  // refresh();

  // getch();

  // endwin();
  // int i = MAX, j = i / 4;
  // int j = 5;
  // printf("%d, %d,%d,%d\n", i, i / 2, i / 4, 4 * j);
  // printf("%lf,%d\n", pow(j, 0), (int)pow(j, 0));
  // /* Print ASCII values from 0 to 255 */
  // // for (i = 0; i <= 255; i++) {
  // //   printf("ASCII value of character %c = %d\n", i, i);
  // //
  char str[8] = "1234456";
  printf("%s, %s\n", str, removeCenterChar(str));
  return 0;
}
