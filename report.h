//
// Created by marco on 27/10/20.
//

#ifndef RTOS_SIMULATOR_REPORT_H
#define RTOS_SIMULATOR_REPORT_H

#include "allegro5/allegro5.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include <allegro5/allegro_ttf.h>


#define REPORT_WIDTH 1200
#define UNIT_SIDE 15
#endif //RTOS_SIMULATOR_REPORT_H


void report_init_app();

void report_run(int num_aliens);

void draw_axis(int num_aliens, int row_height, int height);

void report_destroy();