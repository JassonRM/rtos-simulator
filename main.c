#include "gui.h"
#include "report.h"
#include "miscellaneous.h"
#include <pthread.h>
#include "scheduler.h"

int MAX_ENERGY;
int map[MAP_Y][MAP_X] = {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                         {0,  0,  -1, 0,  0,  0,  -1, 0,  0,  0,  0,  -1, 0,  0,  -1},
                         {-1, 0,  -1, -1, 0,  -1, 0,  0,  -1, -1, -1, -1, 0,  -1, -1},
                         {-1, 1,  0,  0,  0,  -1, 0,  -1, 0,  0,  0,  -1, 0,  0,  -1},
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
    init_alien(&alien, 1, 3, 8, 4, &MAX_ENERGY);
    append(list, alien);
    init_alien(&alien, 2, 1, 8, 4, &MAX_ENERGY);
    append(list, alien);
//    init_alien(&alien, 3, 1, 8, 4, &MAX_ENERGY);
//    append(list, alien);
//    init_alien(&alien, 4, 1, 8, 4, &MAX_ENERGY);
//    append(list, alien);

    pthread_t logic_thread;
//    pthread_create(&logic_thread, NULL, update, alien);

    list_t *report_rm;
    list_t *report_edf;
    new_list(&report_rm);
    new_list(&report_edf);
    alien_t *temp;
    for (int i = 0; i < 150; i += 1) {
        temp = step(list, 1, i);
        append(report_edf, temp);
    }
    reset_elements(list);

    for (int i = 0; i < 150; i += 1) {
        temp = step(list, 0, i);
        append(report_rm, temp);
    }

    pthread_t report_thread;
    struct arg_struct args;
    args.num_aliens = size(list);
    args.aliens = list;
    args.report_rm = report_rm;
    args.report_edf = report_edf;
    args.page = 0;
    pthread_create(&report_thread, NULL, report_run, &args);
    run(map, list, &MAX_ENERGY);



    return 0;
}
