//
// Created by marco on 26/10/20.
//

#ifndef RTOS_SIMULATOR_SCHEDULER_H
#define RTOS_SIMULATOR_SCHEDULER_H

#include "alien.h"
#include "miscellaneous.h"

alien_t *step(list_t *aliens, int mode, int cycle); //Returns index of next process

#endif //RTOS_SIMULATOR_SCHEDULER_H
