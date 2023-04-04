#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define HEIGHT 25
#define WIDTH 80

int get_speed(void);
int input(char init[HEIGHT][WIDTH]);
void output(char init[HEIGHT][WIDTH]);
int is_alive(char init[HEIGHT][WIDTH], int i, int j);
int create_next_gen(char init[HEIGHT][WIDTH], char next_gen[HEIGHT][WIDTH]);
int count_alive_neighbors(char init[HEIGHT][WIDTH], int i, int j);
void copy_matrix(char init[HEIGHT][WIDTH], char next_gen[HEIGHT][WIDTH]);
int swap_coord_i(int new_i);
int swap_coord_j(int new_j);

int main() {
    char init[HEIGHT][WIDTH];
    if (input(init) == 0) {
        output(init);
        if (freopen("/dev/tty", "r", stdin) == NULL) {
            printf("Unable to open terminal for reading");
        }
        int speed = get_speed();
        if (speed != 0) {
            char next_gen[HEIGHT][WIDTH];
            int is_anybody_alive = 1;
            while (is_anybody_alive == 1) {
                system("clear");
                is_anybody_alive = create_next_gen(init, next_gen);
                output(next_gen);
                copy_matrix(init, next_gen);
                usleep(speed);
            }
        } else {
            printf("You have not chosen a speed\n");
        }
    } else {
        printf("No such file or invalid file structure");
    }
    return 0;
}

int get_speed(void) {
    int chosen_speed = 0;
    printf("Please select a game speed:\n");
    printf("1 - slow,\n");
    printf("2 - regular,\n");
    printf("3 - fast\n");
    if (scanf("%d", &chosen_speed) == 1) {
        if (chosen_speed == 1) chosen_speed = 80000;
        if (chosen_speed == 2) chosen_speed = 50000;
        if (chosen_speed == 3) chosen_speed = 10000;
    }
    return chosen_speed;
}

int input(char init[HEIGHT][WIDTH]) {
    int err = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            char temp = getchar();
            char t;
            if (temp == '\n' && ((t = getchar()) == ' ' || t == '*')) {
                init[i][j] = t;
            } else if (temp == ' ' || temp == '*') {
                init[i][j] = temp;
            } else {
                err = 1;
            }
        }
    }
    return err;
}

void output(char init[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {
            if (j < WIDTH) {
                printf("%c", init[i][j]);
            } else if (j == WIDTH) {
                printf("|\n");
            }
        }
    }
}

int is_alive(char init[HEIGHT][WIDTH], int i, int j) {
    int result = -1;
    if (init[i][j] == ' ') {
        result = 0;  // мертв
    } else if (init[i][j] == '*') {
        result = 1;  // жив
    }
    return result;
}

int count_alive_neighbors(char init[HEIGHT][WIDTH], int i, int j) {
    int count = 0;

    if (is_alive(init, swap_coord_i(i), swap_coord_j(j + 1)) == 1) count++;
    if (is_alive(init, swap_coord_i(i + 1), swap_coord_j(j + 1)) == 1) count++;
    if (is_alive(init, swap_coord_i(i + 1), swap_coord_j(j)) == 1) count++;
    if (is_alive(init, swap_coord_i(i + 1), swap_coord_j(j - 1)) == 1) count++;
    if (is_alive(init, swap_coord_i(i), swap_coord_j(j - 1)) == 1) count++;
    if (is_alive(init, swap_coord_i(i - 1), swap_coord_j(j - 1)) == 1) count++;
    if (is_alive(init, swap_coord_i(i - 1), swap_coord_j(j)) == 1) count++;
    if (is_alive(init, swap_coord_i(i - 1), swap_coord_j(j + 1)) == 1) count++;

    return count;
}

int create_next_gen(char init[HEIGHT][WIDTH], char next_gen[HEIGHT][WIDTH]) {
    int is_next_gen_alive = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int alive_state = is_alive(init, i, j);
            int number_alive = count_alive_neighbors(init, i, j);
            if (alive_state == 1 && (number_alive > 3 || number_alive < 2)) {
                next_gen[i][j] = ' ';
            } else if (alive_state == 1 && (number_alive == 3 || number_alive == 2)) {
                next_gen[i][j] = '*';
                is_next_gen_alive = 1;
            } else if (alive_state == 0 && number_alive == 3) {
                next_gen[i][j] = '*';
                is_next_gen_alive = 1;
            } else {
                next_gen[i][j] = ' ';
            }
        }
    }
    return is_next_gen_alive;
}

void copy_matrix(char init[HEIGHT][WIDTH], char next_gen[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            init[i][j] = next_gen[i][j];
        }
    }
}

int swap_coord_i(int new_i) {
    int result = new_i;
    if (new_i == -1) {
        result = HEIGHT - 1;
    } else if (new_i == HEIGHT) {
        result = 0;
    }
    return result;
}

int swap_coord_j(int new_j) {
    int result = new_j;
    if (new_j == -1) {
        result = WIDTH - 1;
    } else if (new_j == WIDTH) {
        result = 0;
    }
    return result;
}