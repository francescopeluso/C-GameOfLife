/**
 *	Conway's Game of Life implementation in C.
 *  -------------------------------------------
 * 
 *  Conway’s Game of Life is a zero-player
 *  cellular automaton devised by John Conway 
 *  in 1970. It runs on an infinite 2D grid of
 *  cells that are either alive or dead.
 * 
 *  At each discrete “generation,” every cell
 *  updates simultaneously based only on its
 *  eight neighbors, producing rich, emergent
 *  behavior (still lifes, oscillators, gliders)
 *  from simple rules—and the system is even
 *  Turing-complete.
 * 
 *  Rules:
 *   - Live cell with <2 neighbors:
 *      dies (underpopulation)
 * 
 *   - Live cell with 2–3 neighbors:
 *      survives
 * 
 *   - Live cell with >3 neighbors:
 *      dies (overcrowding)
 * 
 *   - Dead cell with exactly 3 neighbors:
 *      becomes alive (reproduction)
 * 
 *  -------------------------------------------
 *	Made by @francescopeluso. 2025.
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>     // used for setlocale()
#include <unistd.h>     // used for usleep()
#include <time.h>       // used for srand()
#include "life.h"

const useconds_t SLEEP_USEC = 125000;

/* Places a glider at 1/3 from the top-left corner of
   the grid, so that we can see how the cells behave
   during their lifecycles.  */
void seed_glider(char *grid) {
    /* Glider semplice circa a 1/3 della griglia */
    int cx = COLS / 3, cy = ROWS / 3;
    set_cell(grid, cx+1, cy+0, ALIVE);
    set_cell(grid, cx+2, cy+1, ALIVE);
    set_cell(grid, cx+0, cy+2, ALIVE);
    set_cell(grid, cx+1, cy+2, ALIVE);
    set_cell(grid, cx+2, cy+2, ALIVE);
}

void seed_random(char *grid) {
    float p = 0.35;
    srand(time(NULL));
    
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            if ((rand()%100)/100.0 < p)
                set_cell(grid, x, y, ALIVE);
        }
    }
}

/* Main function. */
int main(void) {
    
    /* Make stdout unbuffered so ANSI codes apply immediately */
    setvbuf(stdout, NULL, _IONBF, 0);

    /* Enabling UTF-8 encoding in the terminal. */
    setlocale(LC_ALL, "");

    /* Sets grid size according to the terminal size. */
    get_terminal_inner_size(&ROWS, &COLS);

    /* Allocated memory dinamically. */
    size_t N = (size_t)ROWS * (size_t)COLS;
    char *old_grid = malloc(N);
    char *new_grid = malloc(N);
    if (!old_grid || !new_grid) {
        fprintf(stderr, "Insufficient memory. Buy a new computer.\n");
        free(old_grid); free(new_grid);
        return 1;
    }

    setup_grid(old_grid, DEAD);
    //seed_glider(old_grid);
    seed_random(old_grid);
    
    while (1) {
        clear_screen();
        print_grid(old_grid);
        usleep(SLEEP_USEC);

        compute_new_state(old_grid, new_grid);
        
        clear_screen();
        print_grid(new_grid);
        usleep(SLEEP_USEC);

        compute_new_state(new_grid, old_grid);
    }

    /* This code will never be reached tho. :/ */
    free(old_grid);
    free(new_grid);
    return 0;
}
