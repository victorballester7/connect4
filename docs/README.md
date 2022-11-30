# Connect 4 game done in C using minimax algorithm

## Requirements

- `gcc`
- `cmake`
- A terminal supporting colors

## Execution

Run the following commands in the terminal:

```sh
git clone git@github.com:victorballester7/connect4.git
cd connect4
make run
```

Or alternatively, if you don't have the SSH keys activated:

```sh
git clone https://github.com/victorballester7/connect4.git
cd connect4
make run
```

If you don't have `cmake` installed on your machine, you can substitute the last line with the following ones:

```sh
gcc -Wall -pedantic -std=c99 -o bin/main src/*.c -lncurses
./bin/main
```

> Attention! Because of the local path definition of some files, avoid executing the program from another folder rather than `connect4/` (for example, avoid executing it in `.../connect4/bin/`).

### Gallery of photos of the game

![Main menu](../resources/mainmenu.png?raw=true "Main menu")
![Match](../resources/match.png?raw=true "Match")
![Ending of a match](../resources/match_ended.png?raw=true "Ending of a match")
![Colors settings menu](../resources/settings_colors.png?raw=true "Color settings menu")
