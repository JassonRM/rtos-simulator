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
        if (cycle > temp->alien->offset && cycle % temp->alien->period == temp->alien->offset) {
            if (temp->alien->rem_time != 0) {
                printf("ERROR scheduling task\n");
                return NULL;
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