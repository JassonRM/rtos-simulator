//
// Created by marco on 16/9/20.
//

#ifndef COLOR_CLASSIFIER_SERVER_MISCELLANEOUS_H
#define COLOR_CLASSIFIER_SERVER_MISCELLANEOUS_H

#include "string.h"
#include <stdlib.h>
#include <stdio.h>

#include "alien.h"

typedef struct node {
    alien_t *alien;
    struct node *next;
} node_t;

typedef struct list {
    node_t *element;
} list_t;

void new_list(list_t **list);

void init_list(list_t *list, alien_t *content);

void append(list_t *list, alien_t *content);

alien_t* get_by_id(list_t *list, int id);

void destroy_list(list_t *list);

void print(list_t *list);


#endif //COLOR_CLASSIFIER_SERVER_MISCELLANEOUS_H
