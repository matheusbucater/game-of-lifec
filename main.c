#include "main.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <raylib.h>

void next_gen(cell_state curr_gen[GRID_ROWS][GRID_COLUMNS]);
void print_grid(cell_state grid[GRID_ROWS][GRID_COLUMNS]);
int count_alive_neighbors(int row_coord, int column_coord, cell_state curr_gen[GRID_ROWS][GRID_COLUMNS]);
void alive_neighbors_grid(int neighbords[GRID_ROWS][GRID_COLUMNS], cell_state cells_grid[GRID_ROWS][GRID_COLUMNS]);
void debug_neighbors(int grid[GRID_ROWS][GRID_COLUMNS]);

void draw_frame();
void draw_grid();
void draw_pixels();
void clear_grid();
void mouse_to_grid(cell_state cell);
void add_pixel_to_grid(void);
void remove_pixel_from_grid(void);

static int pixel_size = 40;
static cell_state grid[GRID_ROWS][GRID_COLUMNS] = { DEAD };
static cell_state grid_copy[GRID_ROWS][GRID_COLUMNS] = { DEAD };
static game_state state = STOPPED;

int main() {
    const int screen_width = 800;
    const int screen_height = 800;

    InitWindow(screen_height, screen_width, "Game of Life");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        draw_frame();
    }

    CloseWindow();
    return 0;
}

void draw_frame(void) {

    if (IsKeyPressed(KEY_SPACE)) {
        if (state == STOPPED) memcpy(&grid_copy, &grid, sizeof grid_copy);
        state = !state;
    }
    if (IsKeyPressed(KEY_R)) {
        if (state == PLAYING) state = STOPPED;
        memcpy(&grid, &grid_copy, sizeof grid);
    }
    if (IsKeyPressed(KEY_C)) clear_grid();
    if (IsKeyPressed(KEY_A)) memcpy(&grid, &blinker, sizeof grid);
    if (IsKeyPressed(KEY_T)) memcpy(&grid, &toad, sizeof grid);
    if (IsKeyPressed(KEY_B)) memcpy(&grid, &beacon, sizeof grid);
    if (IsKeyPressed(KEY_G)) memcpy(&grid, &glider, sizeof grid);
    

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) add_pixel_to_grid();
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) remove_pixel_from_grid();
    if (state == PLAYING) next_gen(grid);

    BeginDrawing();
        if (state == PLAYING) WaitTime(0.5);
        draw_pixels();
        draw_grid();
    EndDrawing();
}

void draw_grid(void) {

    float screen_width, screen_height;
    Vector2 hline_start, hline_end, vline_start, vline_end;

    screen_width = GetScreenWidth();
    screen_height = GetScreenHeight();

    for (int x = 0; x < screen_width; x++) {
        for (int y = 0; y < screen_height; y++) {

            hline_start = (Vector2){0, y * pixel_size};
            hline_end = (Vector2){screen_width, y * pixel_size};
            vline_start = (Vector2){x * pixel_size, 0};
            vline_end = (Vector2){x * pixel_size, screen_height};

            DrawLineV(hline_start, hline_end, LIGHTGRAY);
            DrawLineV(vline_start, vline_end, LIGHTGRAY);
        }
    }
}

void draw_pixels(void) {
    for (int x = 0; x < GRID_ROWS; x++) {
        for (int y = 0; y < GRID_COLUMNS; y++) {
            Color pixel_color = (grid[x][y] == ALIVE) ? BLACK : WHITE;
            Vector2 pixel_position = (Vector2){x * pixel_size, y * pixel_size};
            DrawRectangleV(pixel_position, (Vector2){pixel_size, pixel_size}, pixel_color);
        }
    }
}

void clear_grid(void) {
    for (int x = 0; x < GRID_ROWS; x++) {
        for (int y = 0; y < GRID_COLUMNS; y++) {
            grid[x][y] = DEAD;
        }
    }
}

void mouse_to_grid(cell_state cell) {
    Vector2 mouse_pos, pixel_pos;

    mouse_pos = GetMousePosition();
    pixel_pos = (Vector2){mouse_pos.x / pixel_size, mouse_pos.y / pixel_size};

    printf("%d, %d\n", (int)pixel_pos.x, (int)pixel_pos.y);
    grid[(int)pixel_pos.x][(int)pixel_pos.y] = cell;
}

void add_pixel_to_grid(void) {
    mouse_to_grid(ALIVE);
}

void remove_pixel_from_grid(void) {
    mouse_to_grid(DEAD);
}

void debug_neighbors(int grid[GRID_ROWS][GRID_COLUMNS]) {
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLUMNS; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

void print_grid(cell_state grid[GRID_ROWS][GRID_COLUMNS]) {
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLUMNS; j++) {
            cell_state cell = grid[i][j];
            printf((cell == ALIVE) ? "■" : "□");
        }
        printf("\n");
    }
}

void next_gen(cell_state curr_gen[GRID_ROWS][GRID_COLUMNS]) {
    int neighbors[GRID_ROWS][GRID_COLUMNS] = { 0 };
    alive_neighbors_grid(neighbors, curr_gen);
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLUMNS; j++) {
            cell_state cell = curr_gen[i][j];
            int cell_neighbors = neighbors[i][j];
            switch (cell) {
                case DEAD:
                    if (cell_neighbors == 3) curr_gen[i][j] = ALIVE;
                    break;
                case ALIVE:
                    if (cell_neighbors < 2 || cell_neighbors > 3) curr_gen[i][j] = DEAD;
                    else curr_gen[i][j] = ALIVE;
                    break;
            }
        }
    }
}

void alive_neighbors_grid(int neighbords[GRID_ROWS][GRID_COLUMNS], cell_state cells_grid[GRID_ROWS][GRID_COLUMNS]) {
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLUMNS; j++) {
            neighbords[i][j] = count_alive_neighbors(i, j, cells_grid);
        }
    }
}

int count_alive_neighbors(int row_coord, int column_coord, cell_state curr_gen[GRID_ROWS][GRID_COLUMNS]) {

    int neighbors_count = 0;
    for (int i = -1; i < 2; i++) {
        int neighbor_row = row_coord + i;
        if (neighbor_row < 0 || neighbor_row >= GRID_ROWS) continue;

        for (int j = -1; j < 2; j++) {
            int neighbor_column = column_coord + j;
            if (neighbor_column < 0 || neighbor_column >= GRID_COLUMNS) continue;
            if (neighbor_column == column_coord && neighbor_row == row_coord) continue;
            
            if (curr_gen[neighbor_row][neighbor_column] == ALIVE) neighbors_count++;
        }
    }
    return neighbors_count;
}

