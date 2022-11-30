
#define _GNU_SOURCE
#include "../include/connect4.h"
// #include "../include/evaluation.h"
#include "../include/minimax.h"
#include "../include/setup.h"

extern int colorPlayer, colorComputer, STARTBOARD_X, DEPTH, NROWS, NCOLS;

int supportsColors();
int main() {
  setlocale(LC_ALL, "");
  initscr();             // start ncurses mode.
  clear();               // clear screen.
  noecho();              // Don't echo() while doing getch().
  cbreak();              // Line buffering disabled. pass on everything.
  keypad(stdscr, TRUE);  // Ability to use the keyboard.
  curs_set(0);           // make the cursor invisible
  STARTBOARD_X = (COLS - (INNERSPACE_X + 1) * NCOLS + 1) / 2 - 1;
  int MIN_TERMINAL_WIDTH = (INNERSPACE_X + 1) * NCOLS + 3;
  int MIN_TERMINAL_HEIGHT = STARTBOARD_Y + 6 + (INNERSPACE_Y + 1) * NROWS + 1;  // we leave 5 spaces on the bottom due to future queries.
  char filenameLogo[30] = "resources/logo.txt";

  // position of the top left corner of the window
  int startRow = (31 - WIN_HEIGHT) / 2;
  int startCol = (COLS - WIN_WIDTH) / 2;

  if (!supportsColors()) {
    mvprintw(0, 0, "Your terminal does not support colors, sorry. Press any key to exit.\n");
    getch();
    ending();
    return 1;
  }

  if (LINES < MIN_TERMINAL_HEIGHT || COLS < MIN_TERMINAL_WIDTH) {
    attron(COLOR_PAIR(9));
    mvprintw(0, 0, "Your terminal is too small. In order to play with a larger board exit the program and resize it to at least %i \u2715 %i. Then run the program again. Press any key to exit.", MIN_TERMINAL_HEIGHT, MIN_TERMINAL_WIDTH);
    attroff(COLOR_PAIR(9));
    getch();
    ending();
    return 1;
  }

  WINDOW* menuWin = createWindow(WIN_HEIGHT, WIN_WIDTH, startRow, startCol);
  int choice = 0, choice2 = 0, result = 1;  // result = 1 means return to the main menu.
  while (choice != 4) {                     // Exit
    clear();
    refresh();
    printLogo(filenameLogo, startCol + WIN_WIDTH / 2);
    rectangle(startCol - 1, startRow - 1, WIN_WIDTH + 2, WIN_HEIGHT + 2);
    choice = movementMenu(menuWin, menuMainMenu, 0);
    switch (choice) {
      case 1:  // Play the game
        while ((result = playGame()) == 1) continue;
        break;
      case 2:  // Statistics
        movementMenu(menuWin, menuStats, 0);
        break;
      case 3:  // Settings
        while ((choice2 = movementMenu(menuWin, menuSettings, 0)) != 4) {
          switch (choice2) {
            case 1:
              DEPTH = MIN_DEPTH + movementMenu(menuWin, menuDifficulty, 0) - 1;
              break;
            case 2:
              NROWS = movementMenu(menuWin, menuBoardSizeRows, 2);
              NCOLS = movementMenu(menuWin, menuBoardSizeCols, 2);
              STARTBOARD_X = (COLS - (INNERSPACE_X + 1) * NCOLS + 1) / 2;
              break;
            case 3:
              colorPlayer = movementMenu(menuWin, menuColorsP1, 0);
              colorComputer = movementMenu(menuWin, menuColorsP2, 0);
              break;
            default:  // Go back
              break;
          }
        }
        break;
      default:  // Exit
        break;
    }
    if (result == 3) break;  // (result = 3) = EXIT
  }
  destroy_win(menuWin);
  ending();
  return 0;
}
