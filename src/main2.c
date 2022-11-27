
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
  STARTBOARD_X = (COLS - (INNERSPACE_X + 1) * NCOLS + 1) / 2;
  char filenameLogo[30] = "resources/logo1.txt";

  // position of the top left corner of the window
  int startRow = (30 - WIN_HEIGHT) / 2;
  int startCol = (COLS - WIN_WIDTH) / 2;

  if (!supportsColors()) return 0;

  WINDOW* menuWin = createWindow(WIN_HEIGHT, WIN_WIDTH, startRow, startCol);
  int choice = 0, result = 1;  // result = 1 means return to the main menu.
  while (choice != 4) {        // Exit
    clear();
    refresh();
    topRowComment();
    printLogo(filenameLogo, startCol + WIN_WIDTH / 2);
    choice = movementMenu(menuWin, menuMainMenu, 0);
    switch (choice) {
      case 1:  // Play the game
        while ((result = playGame()) == 1) continue;
        break;
      case 2:  // Statistics
        movementMenu(menuWin, menuStats, 0);
        break;
      case 3:  // Settings
        switch (movementMenu(menuWin, menuSettings, 0)) {
          case 1:
            DEPTH = movementMenu(menuWin, menuDepth, 2);
            break;
          case 2:
            NROWS = movementMenu(menuWin, menuBoardSizeRows, 2);
            NCOLS = movementMenu(menuWin, menuBoardSizeCols, 2);
            break;
          case 3:
            colorPlayer = movementMenu(menuWin, menuColorsP1, 0);
            colorComputer = movementMenu(menuWin, menuColorsP2, 0);
            break;
          default:  // Go back
            break;
        }
        break;
      default:  // Exit
        break;
    }
    if (result == 3) break;  // (result = 3) = EXIT
  }
  clrtoeol();  // erase the current line to the right of the cursor, inclusive, to the end of the current line.
  refresh();
  // sleep(5);
  endwin();
  return 0;
}
