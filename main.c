#include "gui.h"
#include "report.h"
#include "miscellaneous.h"
#include <pthread.h>

    int map[MAP_Y][MAP_X] = {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                             {1, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, -1},
                             {-1, 0, -1, -1, 0, -1, 0, 0, -1, -1, -1, -1, 0, -1, -1},
                             {-1, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, 0, -1},
                             {-1, 0, -1, -1, -1, -1, 0, -1, 0, -1, 0, 0, 0, -1, -1},
                             {-1, 0, 0, -1, 0 ,0 ,0, -1, -1, -1, -1, 0, -1, 0, -1},
                             {-1, -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, -1},
                             {-1, 0, 0, -1, 0, -1, -1, -1, -1, -1, 0, -1, 0, 0, -1},
                             {-1, 0, -1, 0, 0, -1, 0, 0, 0, 0, 0, -1, -1, 0, -1},
                             {-1, 0, 0, -1, -1, -1, 0, -1, -1, -1, 0, 0, 0, 0, -1},
                             {-1, -1, -1, 0, 0, 0, 0, -1, 0, 0, 0, -1, -1, -1, -1},
                             {-1, 0, 0, -1, -1, 0, -1, -1, -1, -1, -1, 0, 0, 0, 0},
                             {-1, -1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, -1},
                             {-1, 0, 0, -1, -1, 0, 0, 0, -1, -1, -1, -1, 0, 0, -1},
                             {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};

void update(alien_t* alien){
    for(int i = 0; i < 20; i++){
        move(alien, map);
        sleep(1);
    }
}

int main(int argc, char** argv) {
    init_app();
    report_init_app();

    list_t *list;
    new_list(&list);
    alien_t *alien;
    init_alien(&alien, 1, 1, 4, 1);
    append(list, alien);
//    init_alien(&alien, 2, 1, 4, 1);
//    append(list, alien);

    pthread_t logic_thread;
    pthread_create(&logic_thread, NULL, update, alien);

    run(map, list);
    report_run(4);
    return 0;
}
