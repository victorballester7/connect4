// #include <curses.h>
// #include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
// #define MAX INT_MAX

#ifdef WINDOWS
#include <direct.h>
#define pwd _getcwd
#else
#include <unistd.h>
#define pwd getcwd
#endif
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

int stringToBase3(char* str) {  // Convert a string of numbers in the set {0,1,2} to a number in base 3.
  int len = 6, base3 = 0, v[6] = {1, 3, 9, 27, 81, 243};
  for (int i = 0; i < len; i++)
    base3 += (str[i] - 48) * v[len - 1 - i];
  return base3;
}
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

char* exchangeOnesAndTwos(char* str) {  // exchange the '1' with '2' in the string 'str' and viceversa.
  int len = strlen(str);
  for (int i = 0; i < len; i++)
    str[i] = (str[i] == '1') ? '2' : ((str[i] == '2') ? '1' : '0');
  return str;
}

#include <ncurses.h>
#include <stdio.h>

#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;

char* choices[] = {
    "Choice 1",
    "Choice 2",
    "Choice 3",
    "Choice 4",
    "Exit",
};
int n_choices = sizeof(choices) / sizeof(char*);
void print_menu(WINDOW* menu_win, int highlight);

int main() {
  WINDOW* menu_win;
  int highlight = 1;
  int choice = 0;
  int c;

  initscr();
  clear();
  noecho();
  cbreak(); /* Line buffering disabled. pass on everything */
  startx = (80 - WIDTH) / 2;
  starty = (24 - HEIGHT) / 2;

  menu_win = newwin(HEIGHT, WIDTH, starty, startx);
  keypad(menu_win, TRUE);
  mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
  refresh();
  print_menu(menu_win, highlight);
  while (1) {
    c = wgetch(menu_win);
    switch (c) {
      case KEY_UP:
        if (highlight == 1)
          highlight = n_choices;
        else
          --highlight;
        break;
      case KEY_DOWN:
        if (highlight == n_choices)
          highlight = 1;
        else
          ++highlight;
        break;
      case 10:
        choice = highlight;
        break;
      default:
        mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
        refresh();
        break;
    }
    print_menu(menu_win, highlight);
    if (choice != 0) /* User did a choice come out of the infinite loop */
      break;
  }
  mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
  clrtoeol();
  refresh();
  endwin();
  return 0;
}

void print_menu(WINDOW* menu_win, int highlight) {
  int x, y, i;

  x = 2;
  y = 2;
  box(menu_win, 0, 0);
  for (i = 0; i < n_choices; ++i) {
    if (highlight == i + 1) /* High light the present choice */
    {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%s", choices[i]);
      wattroff(menu_win, A_REVERSE);
    } else
      mvwprintw(menu_win, y, x, "%s", choices[i]);
    ++y;
  }
  wrefresh(menu_win);
}
