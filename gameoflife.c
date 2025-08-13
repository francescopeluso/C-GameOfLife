/**
 *	Conway's Game of Life implementation in C.
 *
 *	Made by @francescopeluso. 2025.
 */

#include <stdio.h>
#include <unistd.h>

/* Static grid dimensions. */
static const int ROWS = 25;
static const int COLS = 50;

static const int SLEEP_USEC = 250000;

/* Used characters for dead or alive cells. */
static const char DEAD  = ' ';
static const char ALIVE = '@';

/* Function prototypes, see implementations for docs. */
void    set_cell(char *grid, int x, int y, char state);
char    get_cell(char *grid, int x, int y);
int     get_adjusted_coords(int x, int y);
void    print_grid(char *grid);
void    setup_grid(char *grid, char state);
int     count_living_neighbors(char *grid, int x, int y);
void    compute_new_state(char *old, char *new);

/* Main function. */
int main(void) {
    char old_grid[ROWS*COLS];
    char new_grid[ROWS*COLS];
    
    setup_grid(old_grid, DEAD);

    /* Setting first alive cells (glider). */
    set_cell(old_grid, 11, 10, ALIVE);
    set_cell(old_grid, 12, 11, ALIVE);
    set_cell(old_grid, 10, 12, ALIVE);
    set_cell(old_grid, 11, 12, ALIVE);
    set_cell(old_grid, 12, 12, ALIVE);

    print_grid(old_grid);

    while(1) {
        compute_new_state(old_grid, new_grid);
        print_grid(new_grid);
        usleep(SLEEP_USEC);
        compute_new_state(new_grid, old_grid);
        print_grid(old_grid);
        usleep(SLEEP_USEC);
    }
    
    return 0; 
}

/* Translates the specified coords into a valid array index so
   that we don't mistakenly access an index out of bounds.
   It should work for negative coordinates too. */
int get_adjusted_coords(int x, int y) {
    int adj_x = ((x % COLS) + COLS) % COLS;
    int adj_y = ((y % ROWS) + ROWS) % ROWS;
    return adj_y*COLS+adj_x; 
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
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            set_cell(grid, x, y, state);
        }
    } 
}

/* Return the number of living neighbors of a specified cell. */
int count_living_neighbors(char *grid, int x, int y) {
    return
        (get_cell(grid, x-1, y-1) == ALIVE) +
        (get_cell(grid, x, y-1) == ALIVE) +
        (get_cell(grid, x+1, y-1) == ALIVE) +
        (get_cell(grid, x-1, y+1) == ALIVE) +
        (get_cell(grid, x, y+1) == ALIVE) +
        (get_cell(grid, x+1, y+1) == ALIVE) +
        (get_cell(grid, x-1, y) == ALIVE) +
        (get_cell(grid, x+1, y) == ALIVE);
}

void compute_new_state(char *old, char *new) {
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            int alive_neighbors = count_living_neighbors(old, x, y);
            char new_state = DEAD;

            if (get_cell(old, x, y) == ALIVE) {
                // survive, else die for overpopulation or isolation
                if (alive_neighbors == 2 || alive_neighbors == 3)
                    new_state = ALIVE;
            } else {
                // reproduction
                if (alive_neighbors == 3)
                    new_state = ALIVE;
            }
            set_cell(new, x, y, new_state);
        }
    }
}

/* Prints the grid on the terminal, enclosed within a border.
   Of course we need to clear the screen before printing the
   updated one. */
void print_grid(char *grid) {

    /* Clear the screen (thanks @antirez for this trick using 'hexdump -C') */ 
    printf("\x1b[H\x1b[2J");

    printf("+%.*s+\n", COLS, "--------------------------------------------------");

    for (int y = 0; y < ROWS; y++) {
        printf("|");
        for (int x = 0; x < COLS; x++)
            printf("%c", get_cell(grid, x, y));
        printf("|\n");
    }

    printf("+%.*s+\n", COLS, "--------------------------------------------------");
}
