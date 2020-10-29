#include "gui.h"
#include "report.h"
#include "miscellaneous.h"
#include <pthread.h>
#include "scheduler.h"

int MAX_ENERGY;
int map[MAP_Y][MAP_X] = {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                         {1,  0,  -1, 0,  0,  0,  -1, 0,  0,  0,  0,  -1, 0,  0,  -1},
                         {-1, 0,  -1, -1, 0,  -1, 0,  0,  -1, -1, -1, -1, 0,  -1, -1},
                         {-1, 0,  0,  0,  0,  -1, 0,  -1, 0,  0,  0,  -1, 0,  0,  -1},
                         {-1, 0,  -1, -1, -1, -1, 0,  -1, 0,  -1, 0,  0,  0,  -1, -1},
                         {-1, 0,  0,  -1, 0,  0,  0,  -1, -1, -1, -1, 0,  -1, 0,  -1},
                         {-1, -1, 0,  0,  0,  -1, 2,  0,  0,  0,  0,  0,  -1, 0,  -1},
                         {-1, 0,  0,  -1, 0,  -1, -1, -1, -1, -1, 0,  -1, 0,  0,  -1},
                         {-1, 0,  -1, 0,  0,  -1, 0,  0,  0,  0,  0,  -1, -1, 0,  -1},
                         {-1, 0,  0,  -1, -1, -1, 0,  -1, -1, -1, 0,  0,  0,  0,  -1},
                         {-1, -1, -1, 0,  0,  0,  0,  -1, 0,  0,  0,  -1, -1, -1, -1},
                         {-1, 0,  0,  -1, -1, 0,  -1, -1, -1, -1, -1, 0,  0,  0,  0},
                         {-1, -1, 0,  0,  0,  0,  -1, 0,  0,  0,  0,  0,  -1, 0,  -1},
                         {-1, 0,  0,  -1, -1, 0,  0,  0,  -1, -1, -1, -1, 0,  0,  -1},
                         {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};

void update(alien_t *alien) {
    for (int i = 0; i < 20; i++) {
        move(alien, map);
        sleep(1);
    }
}

int main(int argc, char **argv) {
    init_app();

    list_t *list;
    new_list(&list);
    alien_t *alien;
    init_alien(&alien, 1, 3, 4, 2, &MAX_ENERGY);
    append(list, alien);
    init_alien(&alien, 2, 1, 4, 2, &MAX_ENERGY);
    append(list, alien);

    pthread_t logic_thread;
    //pthread_create(&logic_thread, NULL, update, alien);

    list_t *report_rm;
    list_t *report_edf;
    new_list(&report_rm);
    new_list(&report_edf);
    alien_t *temp;
    for (int i = 0; i < 15; i += 1) {
        temp = step(list, 1, i);
        append(report_edf, temp);
    }
    reset_elements(list);

    for (int i = 0; i < 15; i += 1) {
        temp = step(list, 0, i);
        append(report_rm, temp);
    }

//    run(map, list, &MAX_ENERGY);
    report_run(2, list, report_rm, report_edf);
    return 0;
}
