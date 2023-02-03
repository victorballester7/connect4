
#define _GNU_SOURCE
#include "../include/connect4.h"
// #include "../include/evaluation.h"
#include "../include/minimax.h"
#include "../include/setup.h"

extern int colorPlayer, colorComputer, INNERSPACE_X, INNERSPACE_Y, STARTBOARD_X, STARTBOARD_Y, DEPTH, NROWS, NCOLS, NROWS_MAX, NCOLS_MAX;

int main() {
  setlocale(LC_ALL, "");
  initscr();             // start ncurses mode.
  clear();               // clear screen.
  noecho();              // Don't echo() while doing getch().
  cbreak();              // Line buffering disabled. pass on everything.
  keypad(stdscr, TRUE);  // Ability to use the keyboard.
  curs_set(0);           // make the cursor invisible
  int MIN_TERMINAL_WIDTH;
  int MIN_TERMINAL_HEIGHT;
  setMinDimensions(&MIN_TERMINAL_WIDTH, &MIN_TERMINAL_HEIGHT);
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

  int count = -1;
  while (++count < 3) {
    if (LINES < MIN_TERMINAL_HEIGHT || COLS < MIN_TERMINAL_WIDTH) {
      if (count == 2) {
        attron(COLOR_PAIR(9));
        mvprintw(0, 0, "Your terminal is too small. In order to play with a larger board exit the program and resize it to at least %i \u2715 %i. Then run the program again. Press any key to exit.", MIN_TERMINAL_HEIGHT, MIN_TERMINAL_WIDTH);
        attroff(COLOR_PAIR(9));
        getch();
        ending();
        return 1;
      } else if (count == 1)  // small size
        INNERSPACE_X = 3;
      else if (count == 0)  // medium size
        INNERSPACE_X = 5;
      INNERSPACE_Y /= 2;
      setMinDimensions(&MIN_TERMINAL_WIDTH, &MIN_TERMINAL_HEIGHT);
    } else
      break;
  }
  NCOLS_MAX = (COLS - 3) / (INNERSPACE_X + 1);           // we want to leave a margin on both sides.
  NROWS_MAX = (LINES - 5 - 4) / (INNERSPACE_Y + 1) - 1;  // we leave 5 spaces on the bottom and 4 on the top due to future queries.

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
              DEPTH = MIN_DEPTH + 2 * (movementMenu(menuWin, menuDifficulty, 0) - 1);
              break;
            case 2:
              NROWS = NROWS_MAX - movementMenu(menuWin, menuBoardSizeRows, 2) + 1;
              NCOLS = NCOLS_MAX - movementMenu(menuWin, menuBoardSizeCols, 2) + 1;
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
