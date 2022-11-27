
#define _GNU_SOURCE
#include "../include/connect4.h"
// #include "../include/evaluation.h"
#include "../include/minimax.h"
#include "../include/setup.h"

extern int colorPlayer, colorComputer;

int supportsColors();
int main() {
  setlocale(LC_ALL, "");
  initscr();             // start ncurses mode.
  clear();               // clear screen.
  noecho();              // Don't echo() while doing getch().
  cbreak();              // Line buffering disabled. pass on everything.
  keypad(stdscr, TRUE);  // Ability to use the keyboard.
  curs_set(0);           // make the cursor invisible
  char filenameLogo[30] = "resources/logo1.txt";

  // position of the top left corner of the window
  int startRow = (30 - HEIGHT) / 2;
  int startCol = (TERMINAL_WIDTH - WIDTH) / 2;

  if (!supportsColors()) return 0;

  WINDOW* menuWin = createWindow(HEIGHT, WIDTH, startRow, startCol);
  int choice = 0, result = 1;  // result = 1 means return to the main menu.
  while (choice != 4) {        // Exit
    clear();
    refresh();
    topRowComment();
    printLogo(filenameLogo, startCol + WIDTH / 2);
    choice = movementMenu(menuWin, printMainMenu);
    switch (choice) {
      case 1:  // Play the game
        while ((result = playGame()) == 1) continue;
        break;
      case 2:  // Statistics
        movementMenu(menuWin, printStats);
        break;
      case 3:  // Settings
        colorPlayer = movementMenu(menuWin, printSettingsP1);
        colorComputer = movementMenu(menuWin, printSettingsP2);
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
