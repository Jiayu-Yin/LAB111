// Add brief description here

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMROWS	 9    // map size
#define NUMCOLS  9    // map size
#define NUMWALKS 1000 // number of random walks
#define NUMSTEP  10   // number of steps in each walk

struct Cell {
    char symbol;
    double probability;
    double mean_value;
    double std_value;
};
const char* AllSymbol = "WBDVL";

void ERROR(FILE* fp) {
    fclose(fp);
    printf("Error!");
    exit(1);
}

void load_map(struct Cell cells[NUMROWS][NUMCOLS]) {
    FILE* file = NULL;
    char symbol;
    file = fopen("island_map.txt", "rt");
    if (file == NULL) {
        ERROR(NULL);
        return;
    }
    for (int row = 0; row < NUMROWS; row++) {
        for (int col = 0; col < NUMCOLS; col++) {
            if (fscanf(file, "%c ", &symbol) != 1) {
                ERROR(file);
                return;
            }
            int index = 0;
            int is_legal_symbol = 0;
            while (index < 5) {
                if (AllSymbol[index++] == symbol) {
                    is_legal_symbol = 1;
                    break;
                }
            }
            if (!is_legal_symbol) {
                ERROR(file);
                return;
            }
            cells[row][col].symbol = symbol;
            cells[row][col].mean_value = 0;
            cells[row][col].probability = 0;
            cells[row][col].std_value = 0;
        }
    }
    fclose(file);
    printf("Map:\n");
    for (int row = 0; row < NUMROWS; row++) {
        for (int col = 0; col < NUMCOLS; col++) {
            printf("%c%c", cells[row][col].symbol, " \n"[(col == NUMCOLS - 1)]);
        }
    }
}

int random_step(struct Cell cells[NUMROWS][NUMCOLS], int row, int col) {
    int try_cnt = 0;
    while (try_cnt <= NUMSTEP) {
        if (cells[row][col].symbol == 'B') {
            return try_cnt;
        }
        if (cells[row][col].symbol != 'L') {
            return -1;
        }
        try_cnt += 1;
        if (try_cnt > NUMSTEP) {
            return -1;
        }
        int next_move = rand() % 8;
        if (next_move == 0 || next_move == 1 || next_move == 7) {
            if (row - 1 >= 0) {
                row -= 1;
            }
        }
        if (next_move == 3 || next_move == 4 || next_move == 5) {
            if (row + 1 < NUMROWS) {
                row += 1;
            }
        }
        if (next_move == 1 || next_move == 2 || next_move == 3) {
            if (col + 1 < NUMCOLS) {
                col += 1;
            }
        }
        if (next_move == 5 || next_move == 6 || next_move == 7) {
            if (col - 1 >= 0) {
                col -= 1;
            }
        }
    }
    return -1;
}

void display_results(struct Cell cells[NUMROWS][NUMCOLS]) {
    printf("\nProbability of escape:\n");
    for (int row = 0; row < NUMROWS; row++) {
        for (int col = 0; col < NUMCOLS; col++) {
            printf("%.2lf%c", cells[row][col].probability, " \n"[(col == NUMCOLS - 1)]);
        }
    }
    printf("\nMean path length:\n");
    for (int row = 0; row < NUMROWS; row++) {
        for (int col = 0; col < NUMCOLS; col++) {
            printf("%.2lf%c", cells[row][col].mean_value, " \n"[(col == NUMCOLS - 1)]);
        }
    }

    printf("\nStandard deviation of path length:\n");
    for (int row = 0; row < NUMROWS; row++) {
        for (int col = 0; col < NUMCOLS; col++) {
            printf("%.2lf%c", cells[row][col].std_value, " \n"[(col == NUMCOLS - 1)]);
        }
    }
}

int main(void) {
    srand(123456);
    struct Cell cells[NUMROWS][NUMCOLS] = { 0 };
    load_map(cells);

    // Perform random walks and calculate results
    for (int row = 0; row < NUMROWS; row++) {
        for (int col = 0; col < NUMCOLS; col++) {
            double all_steps = 0;
            double std_value = 0;
            double steps_array[NUMWALKS] = { 0 };
            int success_cnt = 0;
            for (int walk = 0; walk < NUMWALKS; walk++) {
                int steps = random_step(cells, row, col);
                if (steps < 0) {
                    continue;
                }
                steps_array[success_cnt] = steps;
                success_cnt++;
                all_steps += steps;
            }
            cells[row][col].probability = 100.0 * success_cnt / NUMWALKS;
            if (success_cnt > 0) {
                cells[row][col].mean_value = all_steps / success_cnt;
                for (int n = 0; n < success_cnt; n++) {
                    std_value += (steps_array[n] - cells[row][col].mean_value) * (steps_array[n] - cells[row][col].mean_value);
                }
                std_value = sqrt(std_value / success_cnt);
                cells[row][col].std_value = std_value;
            }
            else {
                cells[row][col].mean_value = 0;
                cells[row][col].std_value = 0;
            }
        }
    }
    // Print results
    display_results(cells);
    return 0;
}
