//
// Created by marco on 26/10/20.
//

#include "scheduler.h"

alien_t *step(list_t *aliens, int mode, int cycle) {
    mode = mode == 1;

    if (aliens == NULL) {
        return NULL;
    }
    node_t *head = aliens->element;
    node_t *temp = head;
    if (head == NULL) {
        return NULL;
    }
    alien_t *next = NULL;
    while (temp != NULL) {
        if (cycle < temp->alien->offset || (temp->alien->exit != -1 && cycle > temp->alien->exit)) {
            temp = temp->next;
            continue;
        } else if ((cycle - temp->alien->offset) % temp->alien->period == 0 && cycle != temp->alien->offset) {
            if (temp->alien->rem_time != 0) {
                printf("ERROR scheduling task\n");
                alien_t *alien;
                int m = 0;
                init_alien(&alien, -1, 0, 0, 0, &m);
                return alien;
            }
            temp->alien->rem_time = temp->alien->exec_time;
        }
        if ((next == NULL || temp->alien->period < next->period) && temp->alien->rem_time != 0 && !mode) {
            next = temp->alien;
        } else if ((next == NULL || temp->alien->rem_time < next->rem_time) && temp->alien->rem_time != 0 && mode) {
            next = temp->alien;
        }
        temp = temp->next;
    }
    if (next != NULL) {
        next->rem_time -= 1;
    }
    return next;
}