/**
 *	Conway's Game of Life implementation in C.
 *
 *	Made by @francescopeluso. 2025.
 */

#include "life.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/* Clear screen + move home + clear scrollback. */
void clear_screen(void) {
    /* Thanks to @antirez for this trick. */
    printf("\x1b[2J\x1b[3J\x1b[H");
    fflush(stdout);
}

/* Returns the dimension that the grid should have
   (excluded the horizontal and vertical bars used 
    as grid borders). */
int get_terminal_inner_size(int *rows, int *cols) {
    int r = 24, c = 80;
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_row > 0 && ws.ws_col > 0) {
        r = ws.ws_row;
        c = ws.ws_col;
    } else {
        /* Fallback to envvars. */
        char *L = getenv("LINES");
        char *C = getenv("COLUMNS");
        if (L) r = atoi(L);
        if (C) c = atoi(C);
    }

    /* Exclude borders. */
    r -= 3; // one more row for cursor empty row. 
    c -= 2;

    if (r < 5) r = 5;
    if (c < 5) c = 5;

    if (rows) *rows = r;
    if (cols) *cols = c;
    return 0;
}

