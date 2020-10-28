//
// Created by marco on 26/10/20.
//

#include "alien.h"
#include "stdio.h"
#include <stdlib.h>

void init_alien(alien_t **alien, int id, int offset, int period, int exec_time) {
    alien_t *new = (alien_t *) malloc(sizeof(alien_t));
    *alien = new;
    (*alien)->id = id;
    (*alien)->offset = offset;
    (*alien)->period = period;
    (*alien)->exec_time = exec_time;
    (*alien)->rem_time = exec_time;
    (*alien)->x = 0;
    (*alien)->y = 1;
    return;
}