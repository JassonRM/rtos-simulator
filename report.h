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

#include <stdio.h>

#include "miscellaneous.h"

#define REPORT_WIDTH 1200
#define UNIT_SIDE 15
#endif //RTOS_SIMULATOR_REPORT_H

void report_run(int num_aliens, list_t *aliens, list_t *report_rm, list_t *report_edf, int page);

void draw_axis(int num_aliens, int row_height, int height, list_t *aliens, int units, float x_offset, float y_offset,
               int page);

void draw_aliens(int row_height, int height, list_t *aliens, int units, float x_offset, float y_offset, int page);

void
draw_report(int row_height, int height, list_t *report, int units, float x_offset, float y_offset, int mode, int page);

void report_destroy();
