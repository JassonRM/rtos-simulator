#include "gui.h"
#include "report.h"
#include "miscellaneous.h"
#include <pthread.h>
#include "scheduler.h"

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
                         {-1, -1, -1, 0,  0,  0,  0,  -1, 3,  0,  0,  -1, -1, -1, -1},
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
    init_alien(&alien, 1, 1, 4, 1);
    append(list, alien);
    init_alien(&alien, 2, 0, 5, 2);
    append(list, alien);

    pthread_t logic_thread;
    pthread_create(&logic_thread, NULL, update, alien);

    list_t *report;
    new_list(&report);
    alien_t *temp;
    for (int i = 0; i < 15; ++i) {
        temp = step(list, 0, i);
        append(report, temp);
    }

    run(map, list);
    report_run(2, list, report, 0);
    return 0;
}
