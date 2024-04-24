#ifndef MAIN_H
#define MAIN_H

#define GRID_ROWS 20
#define GRID_COLUMNS 20

typedef enum {
    STOPPED = 0,
    PLAYING,
} game_state;

typedef enum {
    DEAD = 0,
    ALIVE,
} cell_state;

cell_state blinker[GRID_ROWS][GRID_COLUMNS] = {
    { DEAD, DEAD, DEAD, DEAD, DEAD },
    { DEAD, DEAD, DEAD, DEAD, DEAD },
    { DEAD, ALIVE, ALIVE, ALIVE, DEAD },
    { DEAD, DEAD, DEAD, DEAD, DEAD },
    { DEAD, DEAD, DEAD, DEAD, DEAD },
};

cell_state toad[GRID_ROWS][GRID_COLUMNS] = {
    { DEAD, DEAD, DEAD, DEAD, DEAD, DEAD },
    { DEAD, DEAD, DEAD, DEAD, DEAD, DEAD },
    { DEAD, DEAD, ALIVE, ALIVE, ALIVE, DEAD },
    { DEAD, ALIVE, ALIVE, ALIVE, DEAD, DEAD },
    { DEAD, DEAD, DEAD, DEAD, DEAD, DEAD },
    { DEAD, DEAD, DEAD, DEAD, DEAD, DEAD },
};

cell_state beacon[GRID_ROWS][GRID_COLUMNS] = {
    { DEAD, DEAD, DEAD, DEAD, DEAD, DEAD },
    { DEAD, ALIVE, ALIVE, DEAD, DEAD, DEAD },
    { DEAD, ALIVE, ALIVE, DEAD, DEAD, DEAD },
    { DEAD, DEAD, DEAD, ALIVE, ALIVE, DEAD },
    { DEAD, DEAD, DEAD, ALIVE, ALIVE, DEAD },
    { DEAD, DEAD, DEAD, DEAD, DEAD, DEAD },
};

cell_state glider[GRID_ROWS][GRID_COLUMNS] = {
    { DEAD, DEAD, DEAD, DEAD, DEAD },
    { DEAD, ALIVE, DEAD, DEAD, DEAD },
    { DEAD, DEAD, ALIVE, ALIVE, DEAD },
    { DEAD, ALIVE, ALIVE, DEAD, DEAD }
};

#endif
