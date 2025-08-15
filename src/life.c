/**
 *	Conway's Game of Life implementation in C.
 *
 *	Made by @francescopeluso. 2025.
 */

#include <stdio.h>
#include <stdlib.h>
#include "life.h"

/* I know it is a bad practice to use global variables,
   but nvm for this program. */

/* Global vars declared in the header. */
int ROWS = 25;
int COLS = 50;

/* Used characters for dead or alive cells. */
const char DEAD  = ' ';
const char ALIVE = '@';

/* Translates the specified coords into a valid array index so
   that we don't mistakenly access an index out of bounds.
   It should work for negative coordinates too. */
int get_adjusted_coords(int x, int y) {
    int ax = ((x % COLS) + COLS) % COLS;
    int ay = ((y % ROWS) + ROWS) % ROWS;
    return ay * COLS + ax;
}

/* Sets the cell at the specified coords into a specified state. */
void set_cell(char *grid, int x, int y, char state) {
    grid[get_adjusted_coords(x, y)] = state;
}

/* Returns the state of a cell at the specified coords. */
char get_cell(char *grid, int x, int y) {
    return grid[get_adjusted_coords(x, y)];
}

/* Set ALL the cells of the specified grid to a specified state. */
void setup_grid(char *grid, char state) {
    for (int y = 0; y < ROWS; y++)
        for (int x = 0; x < COLS; x++)
            set_cell(grid, x, y, state);
}

/* Couting the living neighbor cells.
   By neighbor cells we mean the ones that are adjacent
   to the one we're evaluating, in a 3x3 area. */
int count_living_neighbors(char *grid, int x, int y) {
    return
        (get_cell(grid, x-1, y-1) == ALIVE) +
        (get_cell(grid, x,   y-1) == ALIVE) +
        (get_cell(grid, x+1, y-1) == ALIVE) +
        (get_cell(grid, x-1, y+1) == ALIVE) +
        (get_cell(grid, x,   y+1) == ALIVE) +
        (get_cell(grid, x+1, y+1) == ALIVE) +
        (get_cell(grid, x-1, y  ) == ALIVE) +
        (get_cell(grid, x+1, y  ) == ALIVE);
}

/* Computes new state for each cell, by evaluating the
   number of alive neighbor cells. */
void compute_new_state(char *old, char *new) {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            int n = count_living_neighbors(old, x, y);
            char s = get_cell(old, x, y);
            char out = DEAD;
            if (s == ALIVE) {
                if (n == 2 || n == 3) out = ALIVE;
            } else {
                if (n == 3) out = ALIVE;
            }
            set_cell(new, x, y, out);
        }
    }
}

/* Prints the grid parsed as an argument.
   This will clear the terminal each time the function is
   called and will print the grid within a border. */
void print_grid(char *grid) {
    /* Top border. */
    putchar('+');
    for (int i = 0; i < COLS; i++) putchar('-');
    puts("+");

    /* Left and right border, with the grid between. */
    for (int y = 0; y < ROWS; y++) {
        putchar('|');
        for (int x = 0; x < COLS; x++)
            putchar(get_cell(grid, x, y));
        puts("|");
    }

    /* Bottom border. */
    putchar('+');
    for (int i = 0; i < COLS; i++) putchar('-');
    puts("+");
}

