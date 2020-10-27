//
// Created by marco on 26/10/20.
//

#ifndef RTOS_SIMULATOR_SCHEDULER_H
#define RTOS_SIMULATOR_SCHEDULER_H

#include "alien.h"
#include "miscellaneous.h"

alien_t *step(list_t *aliens, int mode, int cycle); //Returns index of next process

alien_t *step_rm(list_t *aliens, int cycle);

alien_t *step_edf(list_t *aliens, int cycle);

#endif //RTOS_SIMULATOR_SCHEDULER_H
