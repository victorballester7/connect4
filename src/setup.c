#include "../include/setup.h"

int colorPlayer = 1, colorComputer = 3;  // defines the default colors of the tiles for the match.
int STARTBOARD_X = 0;
extern int DEPTH, NROWS, NCOLS, LAST_CHOICE;

void blinking(int startRow, int startCol, char direction, int color) {
  int blink_counter = 0;
  while (blink_counter++ < 2 * BLINKING_TIMES + 1) {
    if (direction == 'h') {
      for (int i = 0; i < 4; i++) {
        if (blink_counter % 2 == 0)
          drawTile(startRow, startCol + i, 8);  // 7 = BLACK
        else
          drawTile(startRow, startCol + i, color);
      }
    } else if (direction == 'v') {
      for (int i = 0; i < 4; i++) {
        if (blink_counter % 2 == 0)
          drawTile(startRow + i, startCol, 8);  // 7 = BLACK
        else
          drawTile(startRow + i, startCol, color);
      }
    } else if (direction == 'd') {
      for (int i = 0; i < 4; i++) {
        if (blink_counter % 2 == 0)
          drawTile(startRow + i, startCol + i, 8);  // 7 = BLACK
        else
          drawTile(startRow + i, startCol + i, color);
      }
    } else {  // else if (direction == 'D')
      for (int i = 0; i < 4; i++) {
        if (blink_counter % 2 == 0)
          drawTile(startRow - i, startCol + i, 8);  // 7 = BLACK
        else
          drawTile(startRow - i, startCol + i, color);
      }
    }
    refresh();
    usleep(BLINKING_INTERVAL);
  }
}

void clearFirst2Lines() {
  clearLine(0);
  clearLine(1);
}

void clearLine(int n) {
  move(n, 0);  // move cursor to the beginning of the line
  clrtoeol();  // clear until the end of the line.
}

WINDOW* createWindow(int height, int width, int startRow, int startCol) {
  WINDOW* win = newwin(height, width, startRow, startCol);
  keypad(win, TRUE);  // enable keypad for the window just created

  return win;
}

void destroy_win(WINDOW* win) {
  /* box(win, ' ', ' '); : This won't produce the desired
   * result of erasing the window. It will leave it's four corners
   * and so an ugly remnant of window.
   */
  wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
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
  wrefresh(win);
  delwin(win);
}

void drawBoard() {
  // horizontal lines
  attron(COLOR_PAIR(7));
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
        mvprintw(STARTBOARD_Y + (INNERSPACE_Y + 1) * i, STARTBOARD_X + (INNERSPACE_X + 1) * j + k, "\u2501");  // horizontal lines
    }
    if (i == 0)
      mvprintw(STARTBOARD_Y, STARTBOARD_X + (INNERSPACE_X + 1) * NCOLS, "\u2513");  // Upper right corner
    else if (i == NROWS)
      mvprintw(STARTBOARD_Y + (INNERSPACE_Y + 1) * NROWS, STARTBOARD_X + (INNERSPACE_X + 1) * NCOLS, "\u251B");  // Lower right corner
    else
      mvprintw(STARTBOARD_Y + (INNERSPACE_Y + 1) * i, STARTBOARD_X + (INNERSPACE_X + 1) * NCOLS, "\u252B");  // Middle right corner
  }
  for (int i = 0; i < NROWS; i++) {
    for (int j = 0; j <= NCOLS; j++) {
      for (int k = 1; k <= INNERSPACE_Y; k++)
        mvprintw(STARTBOARD_Y + (INNERSPACE_Y + 1) * i + k, STARTBOARD_X + (INNERSPACE_X + 1) * j, "\u2503");  // vertical lines
    }
  }
  attroff(COLOR_PAIR(7));
  refresh();
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
  refresh();
}

void ending() {
  clrtoeol();  // erase the current line to the right of the cursor, inclusive, to the end of the current line.
  refresh();
  // sleep(5);
  endwin();
}

int endOfMatch(char winner, int startRow, int startCol, char direction) {
  char* s = malloc(30 * sizeof(char));
  if (winner == '0') {
    attron(COLOR_PAIR(10));
    s = "DRAW!";
  } else if (winner == '1') {
    attron(COLOR_PAIR(9));
    s = "SORRY! YOU'VE LOST!";
  } else {
    attron(COLOR_PAIR(11));
    s = "CONGRATULATIONS! YOU'VE WON!";
  }
  mvprintw(STARTBOARD_Y - INNERSPACE_Y - 2, (COLS - strlen(s)) / 2 + 1, "%s", s);
  if (winner == '0')
    attroff(COLOR_PAIR(10));
  else if (winner == '1')
    attroff(COLOR_PAIR(9));
  else
    attroff(COLOR_PAIR(11));
  refresh();
  uploadFile(winner);
  // blinking
  if (winner == '1' || winner == '2') {
    int color = (winner == '1') ? colorComputer : colorPlayer;
    blinking(startRow, startCol, direction, color);
  }
  topRowComment();
  // free(s);
  return movementMenu(NULL, menuEndingMenu, 0);
}

char* getDifficulty() {
  int n_choices, startX, startY;
  char** choices = menuDifficulty(NULL, &n_choices, &startX, &startY);

  return choices[DEPTH - MIN_DEPTH];
}

char** menuBoardSize(WINDOW* menu_win, int* n_choices, int* startX, int* startY, int row_extra) {
  int NCOLS_MAX = (COLS - 3) / (INNERSPACE_X + 1);           // we want to leave a margin on both sides.
  int NROWS_MAX = (LINES - 5 - 4) / (INNERSPACE_Y + 1) - 1;  // we leave 5 spaces on the bottom and 4 on the top due to future queries.
  int row = 1, col = 2;
  mvwprintw(menu_win, row, col, "The size of the board is %i \u2715 %i. Move with the arrow keys to change it.", NROWS, NCOLS);
  wattron(menu_win, COLOR_PAIR(10));
  mvwprintw(menu_win, row + 2, col, "Note that your terminal size is limiting the size of the board to at most %i \u2715 %i. To increasead it exit the program, resize your terminal and then run the program again.", NROWS_MAX, NCOLS_MAX);
  wattroff(menu_win, COLOR_PAIR(10));

  *startY = row + 2 + 5 + row_extra;
  *startX = col + 19 + 1;

  if (row_extra == 0) {
    *n_choices = NROWS_MAX;
    mvwprintw(menu_win, *startY, col, "Number of rows:");
  } else {
    *n_choices = NCOLS_MAX;
    mvwprintw(menu_win, *startY, col, "Number of columns:");
  }

  char** choices = malloc((*n_choices) * sizeof(char*));
  for (int i = 0; i < *n_choices; i++) {
    choices[i] = malloc(3 * sizeof(char));
    sprintf(choices[i], "%d", i + 1);
  }
  return choices;
}

char** menuBoardSizeCols(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  int row_extra = 1;
  return menuBoardSize(menu_win, n_choices, startX, startY, row_extra);
}

char** menuBoardSizeRows(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  return menuBoardSize(menu_win, n_choices, startX, startY, 0);
}

char** menuColors(WINDOW* menu_win, int* n_choices, int* startX, int* startY, int col_extra) {
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
    wattron(menu_win, COLOR_PAIR(i + 1));                                      // change color to COLOR_PAIR(i+1) ACTIVATED
    mvwhline(menu_win, *startY, maxCol + col_extra, 0, MIN(INNERSPACE_X, 3));  // print the tiles
    wattroff(menu_win, COLOR_PAIR(i + 1));                                     // change color to COLOR_PAIR(i+1) DEACTIVATED
  }
  *startY = 3;
  wrefresh(menu_win);  // print the menu in the real screen
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

char** menuDifficulty(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  *n_choices = 4;
  char** choices = malloc((*n_choices) * sizeof(char*));
  choices[0] = "Easy";
  choices[1] = "Normal";
  choices[2] = "Hard";
  choices[3] = "Master";

  *startX = 2;
  *startY = 1;

  return choices;
}
char** menuEndingMenu(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  *n_choices = 3;
  char** choices = malloc((*n_choices) * sizeof(char*));
  choices[0] = "Play again";
  choices[1] = "Return to the main menu";
  choices[2] = "Exit";

  *startY = STARTBOARD_Y + 1 + NROWS * (INNERSPACE_Y + 1) + 1;
  char s[28] = "What do you want to do now?";
  mvprintw(*startY, 0, "%s", s);  // print current option in the abstract window
  *startX = strlen(s) + 2;

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
  *startY = 1;
  // box(menu_win, 0, 0);

  int length = 28, space_for_tiles = MIN(INNERSPACE_X, 3);
  mvwprintw(menu_win, WIN_HEIGHT - 4, WIN_WIDTH - length - space_for_tiles, "Current player's tile:");
  wattron(menu_win, COLOR_PAIR(colorPlayer));                                               // change color to COLOR_PAIR(i+1) ACTIVATED
  mvwhline(menu_win, WIN_HEIGHT - 4, WIN_WIDTH - space_for_tiles - 1, 0, space_for_tiles);  // print the tiles
  // mvwprintw(menu_win, WIN_HEIGHT - 3, WIN_WIDTH - INNERSPACE_X - 1, "   ");     // print the tiles
  wattroff(menu_win, COLOR_PAIR(colorPlayer));  // change color to COLOR_PAIR(i+1) DEACTIVATED
  mvwprintw(menu_win, WIN_HEIGHT - 3, WIN_WIDTH - length - space_for_tiles, "Current computer's tile:");
  wattron(menu_win, COLOR_PAIR(colorComputer));                                             // change color to COLOR_PAIR(i+1) ACTIVATED
  mvwhline(menu_win, WIN_HEIGHT - 3, WIN_WIDTH - space_for_tiles - 1, 0, space_for_tiles);  // print the tiles
  wattroff(menu_win, COLOR_PAIR(colorComputer));                                            // change color to COLOR_PAIR(i+1) DEACTIVATED
  char* s = getDifficulty();
  mvwprintw(menu_win, WIN_HEIGHT - 2, WIN_WIDTH - length - space_for_tiles, "Level of difficulty:");
  mvwprintw(menu_win, WIN_HEIGHT - 2, WIN_WIDTH - 1 - strlen(s), "%s", s);

  mvwprintw(menu_win, WIN_HEIGHT - 1, WIN_WIDTH - length - space_for_tiles, "Size of the board:\t    %i \u2715 %i", NROWS, NCOLS);

  wrefresh(menu_win);  // print the menu in the real screen
  return choices;
}

char** menuSettings(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  // box(menu_win, 0, 0);
  *n_choices = 4;
  char** choices = malloc((*n_choices) * sizeof(char*));
  choices[0] = "Difficulty of the game";
  choices[1] = "Size of the board";
  choices[2] = "Colors of the tiles";
  choices[3] = "Go back";

  *startX = 2;
  *startY = 1;

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
    clearFirst2Lines();
    attron(COLOR_PAIR(9));
    mvprintw(0, 0, "Error opening the file. The statistics cannot be shown properly. Press Enter to continue.");
    attroff(COLOR_PAIR(9));
    return NULL;
  }
  int played, won, lost, tied;
  fscanf(fp, "Games played: %d\nGames won (by the computer): %d\nGames lost (by the computer): %d\nGames tied: %d\n", &played, &won, &lost, &tied);
  fclose(fp);
  // box(menu_win, 0, 0);

  mvwprintw(menu_win, row, col, "Games played:\t\t\t%d", played);
  mvwprintw(menu_win, row + 1, col, "Win rate (by the computer): \t%.2lf %%", won * 100. / played);
  mvwprintw(menu_win, row + 2, col, "Loss rate (by the computer): \t%.2lf %%", lost * 100. / played);
  mvwprintw(menu_win, row + 3, col, "Tie rate:\t\t\t%.2lf %%", tied * 100. / played);
  // printf("Games played: %d\nWin rate (by the computer): %.2lf\nLose rate (by the computer): %.2lf\nTie rate: %.2lf\n", played, won * 100. / played, lost * 100. / played, tied * 100. / played);
  *startX = WIN_WIDTH - strlen(choices[0]) - 1;
  *startY = WIN_HEIGHT - 2;
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
  *startY = STARTBOARD_Y - INNERSPACE_Y;
  return choices;
}

char** menuWhoStarts(WINDOW* menu_win, int* n_choices, int* startX, int* startY) {
  *n_choices = 2;
  char** choices = malloc((*n_choices) * sizeof(char*));
  choices[0] = "Yes";
  choices[1] = "No";

  char s[22] = "Do you want to start?";
  int row = 1;
  mvprintw(row, 0, "%s", s);  // print current option in the abstract window
  *startX = strlen(s) + 2;
  *startY = row;
  return choices;
}

int movementMenu(WINDOW* menu_win, char** menu(WINDOW*, int*, int*, int*), int type) {
  int choice = 0, highlight = 1, c, n_choices = 0;
  if (menu == menuColorsP2 && colorPlayer == 1)
    highlight = 2;
  else if (menu == menuTilesReadyToPlay)
    highlight = LAST_CHOICE;
  else if (menu == menuBoardSizeRows)
    highlight = NROWS;
  else if (menu == menuBoardSizeCols)
    highlight = NCOLS;
  topRowComment();
  printMenu(menu_win, menu, type, &n_choices, highlight);
  refresh();
  while (true) {
    c = (menu_win == NULL) ? getch() : wgetch(menu_win);
    clearLine(LINES - 1);
    refresh();
    switch (c) {
      case KEY_UP:
      case KEY_LEFT:
        if (highlight == 1)
          highlight = n_choices;
        else
          highlight--;
        break;
      case KEY_DOWN:
        if (menu == menuTilesReadyToPlay) {
          choice = highlight;
          break;
        }
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
        attron(COLOR_PAIR(9));
        mvprintw(LINES - 1, 0, "Please, press enter to select the your choice.");
        attroff(COLOR_PAIR(9));
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

  if (menu != menuColorsP1 && menu != menuBoardSizeRows) {
    wclear(menu_win);    // clear all content on the window
    wrefresh(menu_win);  // print the menu in the real screen}
  }
  return choice;
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
    // clearLine(1);
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
  attron(COLOR_PAIR(12));
  while (fgets(line, sizeof(line), fp)) {
    // mvprintw(i, 0, "%s", line);
    mvprintw(MARGIN + i, centerCol - ncols / 2, "%s", line);
    i++;
  }
  attroff(COLOR_PAIR(12));
  refresh();  // print the menu in the real screen
  fclose(fp);
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
      if (highlight == i + 1) {           // Highlight the present choice
        attron(COLOR_PAIR(colorPlayer));  // change color to COLOR_PAIR(i+1) ACTIVATED
        for (int j = 0; j < INNERSPACE_Y; j++)
          mvprintw(startY + j, startX + INNERSPACE_X * i, "%s", choices[i]);  // print the tiles
        attroff(COLOR_PAIR(colorPlayer));                                     // change color to COLOR_PAIR(i+1) DEACTIVATED
      } else {
        attron(COLOR_PAIR(8));  // change color to COLOR_PAIR(i+1) ACTIVATED
        for (int j = 0; j < INNERSPACE_Y; j++)
          mvprintw(startY + j, startX + INNERSPACE_X * i, "%s", choices[i]);  // print the tiles
        attroff(COLOR_PAIR(8));                                               // change color to COLOR_PAIR(i+1) DEACTIVATED
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

void rectangle(int startX, int startY, int lenX, int lenY) {
  // horizontal lines
  mvhline(startY, startX + 1, 0, lenX - 1);
  mvhline(startY + lenY, startX + 1, 0, lenX - 1);
  // vertical lines
  mvvline(startY + 1, startX, 0, lenY - 1);
  mvvline(startY + 1, startX + lenX, 0, lenY - 1);
  // corners
  mvprintw(startY, startX, "\u250C");
  mvprintw(startY + lenY, startX, "\u2514");
  mvprintw(startY, startX + lenX, "\u2510");
  mvprintw(startY + lenY, startX + lenX, "\u2518");
  refresh();
}

int supportsColors() {
  if (has_colors() == FALSE) {
    endwin();
    puts("Your terminal does not support color");
    return 0;
  }
  start_color(); /* Start color 			*/
  // First color is the foreground color (e.g. for the text). The second one is the background color.
  init_pair(1, COLOR_RED, COLOR_RED);          // for tiles
  init_pair(2, COLOR_GREEN, COLOR_GREEN);      // for tiles
  init_pair(3, COLOR_YELLOW, COLOR_YELLOW);    // for tiles
  init_pair(4, COLOR_WHITE, COLOR_WHITE);      // for tiles
  init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);  // for tiles
  init_pair(6, COLOR_CYAN, COLOR_CYAN);        // for tiles
  init_pair(7, COLOR_BLUE, COLOR_BLUE);        // for the board
  init_pair(8, COLOR_BLACK, COLOR_BLACK);      // for camouflage
  init_pair(9, COLOR_RED, COLOR_BLACK);        // for errors and loss
  init_pair(10, COLOR_YELLOW, COLOR_BLACK);    // for alerts and draws
  init_pair(11, COLOR_GREEN, COLOR_BLACK);     // for winning
  init_pair(12, COLOR_MAGENTA, COLOR_BLACK);   // for presentation
  return 1;
}

void topRowComment() {
  clearFirst2Lines();
  mvprintw(0, 0, "Use arrow keys to go up and down. Press enter to select a choice.");  // printf in the abstract window
  refresh();                                                                            // Print it on to the real screen
}

void uploadFile(char i) {
  FILE* fp;
  char fileName[20] = "data/statistics.txt";
  fp = fopen(fileName, "r+");
  if (fp == NULL) {
    attron(COLOR_PAIR(9));
    mvprintw(LINES - 1, 0, "Error opening the file. The new data cannot be uploaded to the file.");
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
}
