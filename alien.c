//
// Created by marco on 26/10/20.
//

#include "alien.h"
#include <stdlib.h>
#include <stdio.h>

void init_alien(alien_t **alien, int id, int offset, int period, int exec_time, int* max_energy) {
    alien_t *new = (alien_t *) malloc(sizeof(alien_t));
    *alien = new;
    (*alien)->id = id;
    (*alien)->offset = offset;
    (*alien)->period = period;
    (*alien)->exec_time = exec_time;
    (*alien)->rem_time = exec_time;
    (*alien)->x = 0;
    (*alien)->y = 1;
    (*alien)->direction = 1;
    (*alien)->r = rand();
    (*alien)->g = rand();
    (*alien)->b = rand();
    if(exec_time > *max_energy){
        *max_energy = exec_time;
    }
    return;
}