//
// Created by marco on 16/9/20.
//

#include "miscellaneous.h"


void new_list(list_t **list) {
    list_t *new = (list_t *) malloc(sizeof(list_t));
    new->element = NULL;
    *list = new;
}

void init_list(list_t *list, alien_t *content) {
    node_t *head = NULL;
    head = (node_t *) malloc(sizeof(node_t));
    head->next = NULL;
    head->alien = content;
    list->element = head;
}

void append(list_t *list, alien_t *content) {

    if (list == NULL) {
        return;
    }
    node_t *head = list->element;
    node_t *temp = head;
    if (head == NULL) {
        return init_list(list, content);
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    node_t *new_node = NULL;
    new_node = (node_t *) malloc(sizeof(node_t));
    new_node->next = NULL;
    new_node->alien = content;
    temp->next = new_node;
}

alien_t* get_by_id(list_t *list, int id){
    if(list == NULL){
        return NULL;
    }
    node_t *current = list->element;
    while (current != NULL){
        if(current->alien->id == id){
            return current->alien;
        }
        current = current->next;
    }
    return NULL;
}

void destroy_list(list_t *list) {
    node_t *head = list->element;
    node_t *temp = head;
    free(head);
    while (temp->next != NULL) {
        head = temp;
        temp = temp->next;
        free(head);
    }
    free(temp);
    free(list);
}


void print(list_t *list) {
    if (list == NULL) {
        return;
    }
    node_t *head = list->element;
    node_t *temp = head;
    if (head == NULL) {
        return;
    }
    while (temp != NULL) {
        printf("Alien: %d\n", temp->alien->id);
        temp = temp->next;
    }
}
