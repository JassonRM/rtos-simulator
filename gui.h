//
// Created by jasson on 25/10/20.
//

#ifndef RTOS_SIMULATOR_GUI_H
#define RTOS_SIMULATOR_GUI_H

#include "allegro5/allegro5.h"
#include "allegro5/allegro_image.h"

#define WIDTH 1200
#define HEIGHT 1000
#define MAP_X 10
#define MAP_Y 10

#endif //RTOS_SIMULATOR_GUI_H

void init_app();

void run(int map[MAP_X][MAP_Y]);

void destroy();