#include "../include/setup.h"

int colorPlayer = 1, colorComputer = 3;  // defines the default colors of the tiles for the match.
int STARTBOARD_X = 0;
extern int DEPTH, NROWS, NCOLS;

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
    // clearFirstLines(1);
    attron(COLOR_PAIR(9));
    mvprintw(1, 0, "Error opening the file. The new data cannot be uploaded to the file.");
    attroff(COLOR_PAIR(9));
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

void topRowComment() {
  clearFirstLines(1);
  mvprintw(0, 0, "Use arrow keys to go up and down. Press enter to select a choice.");  // printf in the abstract window
  refresh();                                                                            // Print it on to the real screen
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

void clearFirstLines(int n) {
  for (int i = 0; i < n; i++) {
    move(i, 0);
    clrtoeol();  // clear until the end of the line.
  }
}

void blinking(int startRow, int startCol, char direction, int color) {
  int blink_counter = 0;
  while (blink_counter++ < 2 * BLINKING_TIMES + 1) {
    if (direction == 'h') {
      for (int i = 0; i < 4; i++) {
        if (blink_counter % 2 == 0)
          drawTile(startRow, startCol + i, 7);  // 7 = BLACK
        else
          drawTile(startRow, startCol + i, color);
      }
    } else if (direction == 'v') {
      for (int i = 0; i < 4; i++) {
        if (blink_counter % 2 == 0)
          drawTile(startRow + i, startCol, 7);  // 7 = BLACK
        else
          drawTile(startRow + i, startCol, color);
      }
    } else if (direction == 'd') {
      for (int i = 0; i < 4; i++) {
        if (blink_counter % 2 == 0)
          drawTile(startRow + i, startCol + i, 7);  // 7 = BLACK
        else
          drawTile(startRow + i, startCol + i, color);
      }
    } else {  // else if (direction == 'D')
      for (int i = 0; i < 4; i++) {
        if (blink_counter % 2 == 0)
          drawTile(startRow - i, startCol + i, 7);  // 7 = BLACK
        else
          drawTile(startRow - i, startCol + i, color);
      }
    }
    refresh();
    usleep(BLINKING_INTERVAL);
  }
}

int endOfGame(char winner, int startRow, int startCol, char direction) {
  char* s = malloc(30 * sizeof(char));
  if (winner == '0')
    s = "DRAW!";
  else if (winner == '1')
    s = "SORRY! YOU'VE LOST!";
  else
    s = "CONGRATULATIONS! YOU'VE WON!";
  mvprintw(STARTBOARD_Y - 3, (COLS - strlen(s)) / 2 + 1, "%s", s);
  refresh();

  // blinking
  if (winner == '1' || winner == '2') {
    int color = (winner == '1') ? colorComputer : colorPlayer;
    blinking(startRow, startCol, direction, color);
  }
  topRowComment();
  return movementMenu(NULL, menuEndingMenu, 0);
}

int supportsColors() {
  if (has_colors() == FALSE) {
    endwin();
    puts("Your terminal does not support color");
    return 0;
  }
  start_color(); /* Start color 			*/
  // init_pair(1, COLOR_RED, COLOR_BLACK);
  // init_pair(2, COLOR_GREEN, COLOR_BLACK);
  // init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  // init_pair(4, COLOR_BLUE, COLOR_BLACK);
  // init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  // init_pair(6, COLOR_CYAN, COLOR_BLACK);
  // First color is the foreground color (e.g. for the text). The second one is the background color.
  init_pair(1, COLOR_RED, COLOR_RED);
  init_pair(2, COLOR_GREEN, COLOR_GREEN);
  init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(4, COLOR_WHITE, COLOR_WHITE);
  init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(6, COLOR_CYAN, COLOR_CYAN);
  init_pair(7, COLOR_BLACK, COLOR_BLACK);
  init_pair(8, COLOR_BLUE, COLOR_BLUE);
  init_pair(9, COLOR_RED, COLOR_BLACK);  // For errors
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
    // clearFirstLines(1);
    attron(COLOR_PAIR(9));
    mvprintw(1, 0, "Error opening the file. The logo cannot be shown.");
    attroff(COLOR_PAIR(9));
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

void drawTile(int row, int col, int color) {
  int startX = STARTBOARD_X + 1 + (INNERSPACE_X + 1) * col;
  int startY = STARTBOARD_Y + 1 + (INNERSPACE_Y + 1) * row;
  attron(COLOR_PAIR(color));  // change color to COLOR_PAIR(color) ACTIVATED
  for (int i = 0; i < INNERSPACE_Y; i++) {
    for (int j = 0; j < INNERSPACE_X; j++)
      mvprintw(startY + i, startX + j, " ");
  }
  attroff(COLOR_PAIR(color));  // change color to COLOR_PAIR (color) DEACTIVATED
}

void drawBoard() {
  // horizontal lines
  attron(COLOR_PAIR(8));
  for (int i = 0; i <= NROWS; i++) {
    if (i == 0)
      mvprintw(STARTBOARD_Y, STARTBOARD_X, "\u250F");  // Upper left corner
    else if (i == NROWS)
      mvprintw(STARTBOARD_Y + (INNERSPACE_Y + 1) * NROWS, STARTBOARD_X, "\u2517");  // Lower left corner
    else
      mvprintw(STARTBOARD_Y + (INNERSPACE_Y + 1) * i, STARTBOARD_X, "\u2523");  // Middle left corner
    for (int j = 0; j < NCOLS; j++) {
      if (i == 0 && j >= 1)
        mvprintw(STARTBOARD_Y + (INNERSPACE_Y + 1) * i, STARTBOARD_X + (INNERSPACE_X + 1) * j, "\u2533");  // Middle top corner
      else if (i == NROWS && j >= 1)
        mvprintw(STARTBOARD_Y + (INNERSPACE_Y + 1) * i, STARTBOARD_X + (INNERSPACE_X + 1) * j, "\u253B");  // Middle bottom corner
      else if (j >= 1)
        mvprintw(STARTBOARD_Y + (INNERSPACE_Y + 1) * i, STARTBOARD_X + (INNERSPACE_X + 1) * j, "\u254B");  // Middle middle corner

      for (int k = 1; k <= INNERSPACE_X; k++)
        mvprintw(STARTBOARD_Y + (INNERSPACE_Y + 1) * i, STARTBOARD_X + (INNERSPACE_X + 1) * j + k, "\u2501");
    }
    if (i == 0)
      mvprintw(STARTBOARD_Y, STARTBOARD_X + (INNERSPACE_X + 1) * NCOLS, "\u2513");  // Upper right corner
    else if (i == NROWS)
      mvprintw(STARTBOARD_Y + (INNERSPACE_Y + 1) * NROWS, STARTBOARD_X + (INNERSPACE_X + 1) * NCOLS, "\u251B");  // Lower right corner
    else
      mvprintw(STARTBOARD_Y + (INNERSPACE_Y + 1) * i, STARTBOARD_X + (INNERSPACE_X + 1) * NCOLS, "\u252B");  // Middle right corner
  }
  // vertical lines
  for (int i = 0; i < NROWS; i++) {
    for (int j = 0; j <= NCOLS; j++) {
      for (int k = 1; k <= INNERSPACE_Y; k++)
        mvprintw(STARTBOARD_Y + (INNERSPACE_Y + 1) * i + k, STARTBOARD_X + (INNERSPACE_X + 1) * j, "\u2503");
    }
  }
  attroff(COLOR_PAIR(8));
  refresh();
}

char** menuWhoStarts(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  *n_choices = 2;
  char** choices = malloc((*n_choices) * sizeof(char*));
  choices[0] = "Yes";
  choices[1] = "No";

  char s[22] = "Do you want to start?";
  mvprintw(0, 0, "%s", s);  // print current option in the abstract window
  *startX = strlen(s) + 2;
  *startY = 0;
  return choices;
}

char** menuEndingMenu(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  *n_choices = 3;
  char** choices = malloc((*n_choices) * sizeof(char*));
  choices[0] = "Play again";
  choices[1] = "Return to the main menu";
  choices[2] = "Exit";

  *startY = STARTBOARD_Y + NROWS * (INNERSPACE_Y + 1) + 2;
  char s[28] = "What do you want to do now?";
  mvprintw(*startY, 0, "%s", s);  // print current option in the abstract window
  *startX = strlen(s) + 2;

  return choices;
}

char** menuTilesReadyToPlay(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  *n_choices = NCOLS;
  char** choices = malloc((*n_choices) * sizeof(char*));
  for (int i = 0; i < *n_choices; i++) {
    choices[i] = malloc((INNERSPACE_X + 1) * sizeof(char));
    for (int j = 0; j < INNERSPACE_X; j++)
      choices[i][j] = ' ';
    choices[i][INNERSPACE_X] = '\0';
    // choices[i] = "aaa";
  }
  *startX = STARTBOARD_X + 1;
  *startY = STARTBOARD_Y - 1;
  return choices;
}

char** menuMainMenu(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  *n_choices = 4;
  char** choices = malloc((*n_choices) * sizeof(char*));
  choices[0] = "Play";
  choices[1] = "Statistics";
  choices[2] = "Settings";
  choices[3] = "Exit";

  *startX = 2;
  *startY = 2;
  box(menu_win, 0, 0);

  mvwprintw(menu_win, WIN_HEIGHT - 3, WIN_WIDTH - 27 - INNERSPACE_X, "Current player's tile:");
  wattron(menu_win, COLOR_PAIR(colorPlayer));                                         // change color to COLOR_PAIR(i+1) ACTIVATED
  mvwhline(menu_win, WIN_HEIGHT - 3, WIN_WIDTH - INNERSPACE_X - 1, 0, INNERSPACE_X);  // print the tiles
  // mvwprintw(menu_win, WIN_HEIGHT - 3, WIN_WIDTH - INNERSPACE_X - 1, "   ");     // print the tiles
  wattroff(menu_win, COLOR_PAIR(colorPlayer));  // change color to COLOR_PAIR(i+1) DEACTIVATED
  mvwprintw(menu_win, WIN_HEIGHT - 2, WIN_WIDTH - 27 - INNERSPACE_X, "Current computer's tile:");
  wattron(menu_win, COLOR_PAIR(colorComputer));                                       // change color to COLOR_PAIR(i+1) ACTIVATED
  mvwhline(menu_win, WIN_HEIGHT - 2, WIN_WIDTH - INNERSPACE_X - 1, 0, INNERSPACE_X);  // print the tiles
  wattroff(menu_win, COLOR_PAIR(colorComputer));                                      // change color to COLOR_PAIR(i+1) DEACTIVATED
  wrefresh(menu_win);                                                                 // print the menu in the real screen
  return choices;
}

char** menuStats(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  *n_choices = 1;
  char** choices = malloc((*n_choices) * sizeof(char*));
  choices[0] = "Go back";

  int col = 2, row = 2;
  char filename[30] = "data/statistics.txt";
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    clearFirstLines(2);
    attron(COLOR_PAIR(9));
    mvprintw(0, 0, "Error opening the file. The statistics cannot be shown properly. Press Enter to continue.");
    attroff(COLOR_PAIR(9));
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
  *startX = WIN_WIDTH - strlen(choices[0]) - 1;
  *startY = WIN_HEIGHT - 2;
  return choices;
}
char** menuDepth(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  box(menu_win, 0, 0);
  *n_choices = 9;
  char** choices = malloc((*n_choices) * sizeof(char*));
  for (int i = 0; i < *n_choices; i++) {
    choices[i] = malloc(3 * sizeof(char));
    sprintf(choices[i], "%d", i + 1);
  }

  int row = 2, col = 2;
  mvwprintw(menu_win, row, col, "The current depth of the algorithm is %i.", DEPTH);
  mvwprintw(menu_win, row + 1, col, "Move with the arrow keys to change it.");
  mvwprintw(menu_win, row + 3, col, "Depth:");

  *startX = col + 7 + 1;
  *startY = row + 3;

  return choices;
}

char** menuBoardSizeRows(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  return menuBoardSize(menu_win, n_choices, startX, startY, 0);
}
char** menuBoardSizeCols(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  int row_extra = 1;
  return menuBoardSize(menu_win, n_choices, startX, startY, row_extra);
}

char** menuBoardSize(WINDOW* menu_win, int* n_choices, int* startX, int* startY, int row_extra) {
  box(menu_win, 0, 0);
  *n_choices = 20;
  char** choices = malloc((*n_choices) * sizeof(char*));
  for (int i = 0; i < *n_choices; i++) {
    choices[i] = malloc(3 * sizeof(char));
    sprintf(choices[i], "%d", i + 1);
  }

  int row = 2, col = 2;
  mvwprintw(menu_win, row, col, "The size of the board is %i \u2715 %i.", NROWS, NCOLS);
  mvwprintw(menu_win, row + 1, col, "Move with the arrow keys to change it.");

  if (row_extra == 0)
    mvwprintw(menu_win, row, col, "Number of rows:");
  else
    mvwprintw(menu_win, row + row_extra, col, "Number of columns:");

  *startX = col + 19 + 1;
  *startY = row + row_extra;

  return choices;
}

char** menuSettings(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  box(menu_win, 0, 0);
  *n_choices = 4;
  char** choices = malloc((*n_choices) * sizeof(char*));
  choices[0] = "Change the depth of the algorithm";
  choices[1] = "Change the size of the board";
  choices[2] = "Change the colors of the tiles:";
  choices[3] = "Go back";

  *startX = 2;
  *startY = 2;

  return choices;
}

char** menuColorsP1(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  int col_extra = 0, col = 2;
  mvwprintw(menu_win, 1, col + col_extra, "Player's tile");
  return menuColors(menu_win, n_choices, startX, startY, col_extra);
}

char** menuColorsP2(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  int col_extra = WIN_WIDTH / 2, col = 2;
  mvwprintw(menu_win, 1, col + col_extra, "Computer's tile");
  return menuColors(menu_win, n_choices, startX, startY, col_extra);
}

char** menuColors(WINDOW* menu_win, int* n_choices, int* startX, int* startY, int col_extra) {
  box(menu_win, 0, 0);
  *n_choices = 6;
  char** choices = malloc((*n_choices) * sizeof(char*));
  choices[0] = "Red:";
  choices[1] = "Green:";
  choices[2] = "Yellow:";
  choices[3] = "White:";
  choices[4] = "Magenta:";
  choices[5] = "Cyan:";

  *startY = 3;
  *startX = 2 + col_extra;
  int maxCol = 12;  // MaxCol = a number smaller than WIDTH but larger than any length within choices.

  for (int i = 0; i < *n_choices; i++, (*startY)++) {
    wattron(menu_win, COLOR_PAIR(i + 1));                              // change color to COLOR_PAIR(i+1) ACTIVATED
    mvwhline(menu_win, *startY, maxCol + col_extra, 0, INNERSPACE_X);  // print the tiles
    wattroff(menu_win, COLOR_PAIR(i + 1));                             // change color to COLOR_PAIR(i+1) DEACTIVATED
  }
  *startY = 3;
  wrefresh(menu_win);  // print the menu in the real screen
  return choices;
}

void printMenu(WINDOW* menu_win, char** menu(WINDOW*, int*, int*, int*), int type, int* n_choices, int highlight) {
  int startX = 0, startY = 0;
  char** choices = menu(menu_win, n_choices, &startX, &startY);
  if (choices == NULL) return;
  if (type == 0) {
    for (int i = 0; i < *n_choices; i++, startY++) {
      if (menu_win == NULL) {
        if (highlight == i + 1) {                      // Highlight the present choice
          attron(A_REVERSE);                           // reverse color font and background font ACTIVATED
          mvprintw(startY, startX, "%s", choices[i]);  // print current option in the abstract window
          attroff(A_REVERSE);                          // reverse color font and background font DEACTIVATED
        } else
          mvprintw(startY, startX, "%s", choices[i]);  // print current option in the abstract window
      } else {
        if (highlight == i + 1) {                                 // Highlight the present choice
          wattron(menu_win, A_REVERSE);                           // reverse color font and background font ACTIVATED
          mvwprintw(menu_win, startY, startX, "%s", choices[i]);  // print current option in the abstract window
          wattroff(menu_win, A_REVERSE);                          // reverse color font and background font DEACTIVATED
        } else
          mvwprintw(menu_win, startY, startX, "%s", choices[i]);  // print current option in the abstract window
      }
    }
  } else if (type == 1) {  // menu for printing the tiles above the board
    for (int i = 0; i < *n_choices; i++, startX++) {
      if (highlight == i + 1) {                                         // Highlight the present choice
        attron(COLOR_PAIR(colorPlayer));                                // change color to COLOR_PAIR(i+1) ACTIVATED
        mvprintw(startY, startX + INNERSPACE_X * i, "%s", choices[i]);  // print the tiles
        attroff(COLOR_PAIR(colorPlayer));                               // change color to COLOR_PAIR(i+1) DEACTIVATED
      } else {
        attron(COLOR_PAIR(7));                                          // change color to COLOR_PAIR(i+1) ACTIVATED
        mvprintw(startY, startX + INNERSPACE_X * i, "%s", choices[i]);  // print the tiles
        attroff(COLOR_PAIR(7));                                         // change color to COLOR_PAIR(i+1) DEACTIVATED
      }
    }
  } else {                                                              // menu of numbers (i.e. for Depth settings and Board-size settings)
    mvwprintw(menu_win, startY, startX, "  ");                          // to clear the neighbourhood of the number where will be placed (because if there is a to digit number and we change it to a one-digit number... It will remain a digit of the first number!)
    mvwprintw(menu_win, startY, startX, "%s", choices[highlight - 1]);  // print current option in the abstract window}
  }
  if (type != 0) {
    for (int i = 0; i < *n_choices; i++) free(choices[i]);
  }
  free(choices);
}

int movementMenu(WINDOW* menu_win, char** menu(WINDOW*, int*, int*, int*), int type) {
  int choice = 0, highlight = 1, c, n_choices = 0;
  if (menu == menuColorsP2 && colorPlayer == 1)
    highlight = 2;
  else if (menu == menuTilesReadyToPlay)
    highlight = NCOLS / 2 + 1;
  else if (menu == menuDepth)
    highlight = DEPTH;
  printMenu(menu_win, menu, type, &n_choices, highlight);
  refresh();
  while (true) {
    c = (menu_win == NULL) ? getch() : wgetch(menu_win);
    switch (c) {
      case KEY_UP:
      case KEY_LEFT:
        if (highlight == 1)
          highlight = n_choices;
        else
          highlight--;
        break;
      case KEY_DOWN:
      case KEY_RIGHT:
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
    if (menu == menuColorsP2 && colorPlayer == highlight) {
      if (highlight == n_choices)
        highlight = 1;
      else
        highlight++;
    }
    printMenu(menu_win, menu, type, &n_choices, highlight);
    if (choice != 0) break;  // User did a choice come out of the infinite loop
  }

  if (menu != menuColorsP1) wclean(menu_win);
  return choice;
}

void wclean(WINDOW* menu_win) {
  wclear(menu_win);    // clear all content on the window
  wrefresh(menu_win);  // print the menu in the real screen
}
