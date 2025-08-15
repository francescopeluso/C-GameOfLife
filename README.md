# Conway's "Game of Life"

A small terminal implementation of Conway's Game of Life in C.

![Demo](src/conway.gif)

Conway's Game of Life is a zero-player cellular automaton. Each cell on a grid is either alive or dead. On each generation:
- Any live cell with 2 or 3 live neighbors stays alive.
- Any dead cell with exactly 3 live neighbors becomes alive.
- All other cells die or remain dead.

This program runs the simulation in the terminal with wrap-around edges.

## Build & run
```sh
make
./life
```
