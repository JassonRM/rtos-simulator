//
// Created by marco on 26/10/20.
//

#include "miscellaneous.h"
#include "scheduler.h"

int main(int argc, char **argv) {

    list_t *list;
    new_list(&list);
    alien_t *alien;
    init_alien(&alien, 1, 0, 6, 3);
    append(list, alien);

    alien_t *alien2;
    init_alien(&alien2, 2, 0, 9, 4);
    append(list, alien2);

//    alien_t *alien3;
//    init_alien(&alien3, 3, 0, 18, 6);
//    append(list, alien3);

    for (int i = 0; i < 19; i++) {
        alien_t *next = step(list, 1, i);
        if (next != NULL) {
            printf("%d\n", next->id);
        } else {
            printf("None\n");
        }
    }
    return 0;
}