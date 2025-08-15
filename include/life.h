/**
 *	Conway's Game of Life implementation in C.
 *
 *	Made by @francescopeluso. 2025.
 */

#ifndef LIFE_H
#define LIFE_H

#include <unistd.h>

/* Grid dimensions that will be set on runtime. */
extern int ROWS;
extern int COLS;

/* Symbols used for alive or dead cells. */
extern const char DEAD;
extern const char ALIVE;

/* Function prototypes. */
void set_cell(char *grid, int x, int y, char state);
char get_cell(char *grid, int x, int y);
int  get_adjusted_coords(int x, int y);
void print_grid(char *grid);
void setup_grid(char *grid, char state);
int  count_living_neighbors(char *grid, int x, int y);
void compute_new_state(char *old, char *new);

/* Utility functions for terminal. */
void clear_screen(void);
int  get_terminal_inner_size(int *rows, int *cols);

#endif

