//
// Created by marco on 26/10/20.
//

#include "scheduler.h"

alien_t *step(list_t *aliens, int mode, int cycle) {
    if (mode == 0) {
        return step_rm(aliens, cycle);
    } else {
        return step_edf(aliens, cycle);
    }
}

alien_t *step_rm(list_t *aliens, int cycle) {
    if (aliens == NULL) {
        return NULL;
    }
    node_t *head = aliens->element;
    node_t *temp = head;
    if (head == NULL) {
        return NULL;
    }
    alien_t *smallest = NULL;
    while (temp != NULL) {
        if (cycle != temp->alien->offset && cycle % (temp->alien->offset + temp->alien->period) == 0) {
            if (temp->alien->rem_time != 0) {
                printf("ERROR scheduling task\n");
                return NULL;
            }
            temp->alien->rem_time = temp->alien->exec_time;
        }
        if ((smallest == NULL || temp->alien->period < smallest->period) && temp->alien->rem_time != 0) {
            smallest = temp->alien;
        }
        temp = temp->next;
    }
    if (smallest != NULL) {
        smallest->rem_time -= 1;
    }
    return smallest;
}

alien_t *step_edf(list_t *aliens, int cycle) {

}