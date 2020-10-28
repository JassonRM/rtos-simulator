//
// Created by marco on 26/10/20.
//

#ifndef RTOS_SIMULATOR_ALIEN_H
#define RTOS_SIMULATOR_ALIEN_H

typedef struct alien {
    int id;
    int offset;
    int period;
    int exec_time;
    int rem_time;
    int x;
    int y;
    int direction;
    int r, g, b;
} alien_t;

void init_alien(alien_t **alien, int id, int offset, int period, int exec_time, int* max_energy);

#endif //RTOS_SIMULATOR_ALIEN_H
