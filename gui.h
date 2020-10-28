//
// Created by jasson on 25/10/20.
//

#ifndef RTOS_SIMULATOR_GUI_H
#define RTOS_SIMULATOR_GUI_H

#include "allegro5/allegro5.h"
#include "allegro5/allegro_image.h"
#include "alien.h"
#include "miscellaneous.h"

#define WIDTH 1800
#define HEIGHT 1500
#define MAP_X 15
#define MAP_Y 15

#endif //RTOS_SIMULATOR_GUI_H

void init_app();

void run(int map[MAP_X][MAP_Y], list_t*);

void move(alien_t*, int[MAP_X][MAP_Y]);

void destroy();