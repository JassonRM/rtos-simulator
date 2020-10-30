//
// Created by jasson on 25/10/20.
//

#ifndef RTOS_SIMULATOR_GUI_H
#define RTOS_SIMULATOR_GUI_H

#include <stdio.h>
#include <stdlib.h>

#include "allegro5/allegro5.h"
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_font.h"
#include <allegro5/allegro_ttf.h>

#include "alien.h"
#include "miscellaneous.h"


#define WIDTH 900
#define HEIGHT 800
#define MAP_X 15
#define MAP_Y 15

#endif //RTOS_SIMULATOR_GUI_H

void init_app();

void run(int map[MAP_X][MAP_Y], list_t *, int *max_energy, list_t *report_rm, list_t *report_edf);

void move(alien_t *, int[MAP_X][MAP_Y]);

void destroy();

void auto_mode(struct auto_args *args);

void next_clock(int map[MAP_X][MAP_Y], list_t *alien_list, int mode, list_t *report_rm, list_t *report_edf);
