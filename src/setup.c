#include "../include/setup.h"

int colorPlayer = 1, colorComputer = 3;  // defines the default colors of the tiles for the match.

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
    printf("What do you want to do?\n1) Play a new game\n2) See statistics\n3) Change tiles color\n4) Exit");
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
        printf("Error entering the data. Exiting.");
        return 1;
    }
  } while (choice == 2);
}

int supportsColors() {
  if (has_colors() == FALSE) {
    endwin();
    puts("Your terminal does not support color");
    return 0;
  }
  start_color(); /* Start color 			*/
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_BLUE, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6, COLOR_CYAN, COLOR_BLACK);
  return 1;
}

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

void printLogo(char* filename, int centerCol) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error opening the file. Exiting.\n");
    return;
  }
  char line[500];
  int i = 1, nrows = 0, ncols = 0;
  const int MARGIN = 2;
  numRowsAndCols(fp, &nrows, &ncols);
  rewind(fp);  // reset file pointer to the beginning
  while (fgets(line, sizeof(line), fp)) {
    // mvprintw(i, 0, "%s", line);
    mvprintw(MARGIN + i, centerCol - ncols / 2, "%s", line);
    i++;
  }
  refresh();  // print the menu in the real screen
  fclose(fp);
}

WINDOW* createWindow(int height, int width, int startRow, int startCol) {
  WINDOW* localWin = newwin(height, width, startRow, startCol);
  keypad(localWin, TRUE);  // enable keypad for the window just created

  return localWin;
}

void destroy_win(WINDOW* localWin) {
  /* box(localWin, ' ', ' '); : This won't produce the desired
   * result of erasing the window. It will leave it's four corners
   * and so an ugly remnant of window.
   */
  wborder(localWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  /* The parameters taken are
   * 1. win: the window on which to operate
   * 2. ls: character to be used for the left side of the window
   * 3. rs: character to be used for the right side of the window
   * 4. ts: character to be used for the top side of the window
   * 5. bs: character to be used for the bottom side of the window
   * 6. tl: character to be used for the top left corner of the window
   * 7. tr: character to be used for the top right corner of the window
   * 8. bl: character to be used for the bottom left corner of the window
   * 9. br: character to be used for the bottom right corner of the window
   */
  wrefresh(localWin);
  delwin(localWin);
}

void drawBoard() {
}

char** printMenu(WINDOW* menu_win, int highlight, int* n_choices) {
  *n_choices = 4;
  char** choices = malloc((*n_choices) * sizeof(char*));
  choices[0] = "Play";
  choices[1] = "Statistics";
  choices[2] = "Settings";
  choices[3] = "Exit";

  int col = 2, row = 2;
  box(menu_win, 0, 0);
  for (int i = 0; i < *n_choices; i++, row++) {
    if (highlight == i + 1) {                           // Highlight the present choice
      wattron(menu_win, A_REVERSE);                     // reverse color font and background font ACTIVATED
      mvwprintw(menu_win, row, col, "%s", choices[i]);  // print current option in the abstract window
      wattroff(menu_win, A_REVERSE);                    // reverse color font and background font DEACTIVATED
    } else
      mvwprintw(menu_win, row, col, "%s", choices[i]);  // print current option in the abstract window
  }
  mvwprintw(menu_win, HEIGHT - 3, WIDTH - 27 - 1, "Current player's tile:");
  wattron(menu_win, COLOR_PAIR(colorPlayer));            // change color to COLOR_PAIR(i+1) ACTIVATED
  mvwprintw(menu_win, HEIGHT - 3, WIDTH - 2, "\u25CF");  // print the tiles
  wattroff(menu_win, COLOR_PAIR(colorPlayer));           // change color to COLOR_PAIR(i+1) DEACTIVATED
  mvwprintw(menu_win, HEIGHT - 2, WIDTH - 27 - 1, "Current computer's tile:");
  wattron(menu_win, COLOR_PAIR(colorComputer));          // change color to COLOR_PAIR(i+1) ACTIVATED
  mvwprintw(menu_win, HEIGHT - 2, WIDTH - 2, "\u25CF");  // print the tiles
  wattroff(menu_win, COLOR_PAIR(colorComputer));         // change color to COLOR_PAIR(i+1) DEACTIVATED
  wrefresh(menu_win);                                    // print the menu in the real screen
  return choices;
}

char** printStats(WINDOW* menu_win, int highlight, int* n_choices) {
  *n_choices = 1;
  char** choices = malloc((*n_choices) * sizeof(char*));
  choices[0] = "Go back";
  int col = 2, row = 2;
  char filename[30] = "data/statistics.txt";
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Error opening the file. Exiting.\n");
    return NULL;
  }
  int played, won, lost, tied;
  fscanf(fp, "Games played: %d\nGames won (by the computer): %d\nGames lost (by the computer): %d\nGames tied: %d\n", &played, &won, &lost, &tied);
  fclose(fp);

  box(menu_win, 0, 0);

  mvwprintw(menu_win, row, col, "Games played:\t\t\t%d", played);
  mvwprintw(menu_win, row + 1, col, "Win rate (by the computer): \t%.2lf %%", won * 100. / played);
  mvwprintw(menu_win, row + 2, col, "Loss rate (by the computer): \t%.2lf %%", lost * 100. / played);
  mvwprintw(menu_win, row + 3, col, "Tie rate:\t\t\t%.2lf %%", tied * 100. / played);
  // printf("Games played: %d\nWin rate (by the computer): %.2lf\nLose rate (by the computer): %.2lf\nTie rate: %.2lf\n", played, won * 100. / played, lost * 100. / played, tied * 100. / played);
  wattron(menu_win, A_REVERSE);  // reverse color font and background font ACTIVATED
  mvwprintw(menu_win, HEIGHT - 2, WIDTH - strlen(choices[0]) - 1, "%s", choices[0]);
  wattroff(menu_win, A_REVERSE);  // reverse color font and background font DEACTIVATED
  wrefresh(menu_win);             // print the menu in the real screen
  return choices;
}

char** printSettingsP1(WINDOW* menu_win, int highlight, int* n_choices) {
  int col_extra = 0, col = 2;
  mvwprintw(menu_win, 1, col + col_extra, "Player's tile");
  return printColors(menu_win, highlight, n_choices, col_extra);
}

char** printSettingsP2(WINDOW* menu_win, int highlight, int* n_choices) {
  int col_extra = WIDTH / 2, col = 2;
  mvwprintw(menu_win, 1, col + col_extra, "Computer's tile");
  return printColors(menu_win, highlight, n_choices, col_extra);
}

char** printColors(WINDOW* menu_win, int highlight, int* n_choices, int col_extra) {
  box(menu_win, 0, 0);
  *n_choices = 6;
  char** choices = malloc((*n_choices) * sizeof(char*));
  choices[0] = "Red:";
  choices[1] = "Green:";
  choices[2] = "Yellow:";
  choices[3] = "Blue:";
  choices[4] = "Magenta:";
  choices[5] = "Cyan:";

  int row = 3, col = 2, maxCol = 12;  // MaxCol = a number smaller than WIDTH but larger than any length within choices.

  for (int i = 0; i < *n_choices; i++, row++) {
    if (highlight == i + 1) {                                       // Highlight the present choice
      wattron(menu_win, A_REVERSE);                                 // reverse color font and background font ACTIVATED
      mvwprintw(menu_win, row, col + col_extra, "%s", choices[i]);  // print current option in the abstract window
      wattroff(menu_win, A_REVERSE);                                // reverse color font and background font DEACTIVATED
    } else
      mvwprintw(menu_win, row, col + col_extra, "%s", choices[i]);  // print current option in the abstract window
    wattron(menu_win, COLOR_PAIR(i + 1));                           // change color to COLOR_PAIR(i+1) ACTIVATED
    mvwprintw(menu_win, row, maxCol + col_extra, "\u25CF");         // print the tiles
    wattroff(menu_win, COLOR_PAIR(i + 1));                          // change color to COLOR_PAIR(i+1) DEACTIVATED
  }
  wrefresh(menu_win);  // print the menu in the real screen
  return choices;
}

int movementMenu(WINDOW* menu_win, char** printMenu(WINDOW*, int, int*)) {
  int choice = 0, highlight = 1, c, n_choices;
  if (printMenu == printSettingsP2 && colorPlayer == 1) highlight = 2;
  char** choices = printMenu(menu_win, highlight, &n_choices);
  while (true) {
    c = wgetch(menu_win);
    switch (c) {
      case KEY_UP:
        if (highlight == 1)
          highlight = n_choices;
        else
          highlight--;
        break;
      case KEY_DOWN:
        if (highlight == n_choices)
          highlight = 1;
        else
          highlight++;
        break;
      case 10:  // press enter
        choice = highlight;
        break;
      default:
        mvprintw(24, 0, "Please, press enter to select the your choice");
        refresh();
        break;
    }
    if (printMenu == printSettingsP2 && colorPlayer == highlight) {
      if (highlight == n_choices)
        highlight = 1;
      else
        highlight++;
    }
    printMenu(menu_win, highlight, &n_choices);
    if (choice != 0) break;  // User did a choice come out of the infinite loop
  }
  if (printMenu != printSettingsP1) {
    wclear(menu_win);    // clear all content on the window
    wrefresh(menu_win);  // print the menu in the real screen
  }
  free(choices);
  return choice;
}
