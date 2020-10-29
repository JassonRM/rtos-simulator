#include "gui.h"
#include "report.h"
#include "miscellaneous.h"
#include <pthread.h>
#include "scheduler.h"

int MAX_ENERGY;
int map[MAP_Y][MAP_X] = {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                         {0,  0,  -1, 0,  0,  0,  -1, 0,  0,  0,  0,  -1, 0,  0,  -1},
                         {-1, 0,  -1, -1, 0,  -1, 0,  0,  -1, -1, -1, -1, 0,  -1, -1},
                         {-1, 0,  0,  0,  0,  -1, 0,  -1, 0,  0,  0,  -1, 0,  0,  -1},
                         {-1, 0,  -1, -1, -1, -1, 0,  -1, 0,  -1, 0,  0,  0,  -1, -1},
                         {-1, 0,  0,  -1, 0,  0,  0,  -1, -1, -1, -1, 0,  -1, 0,  -1},
                         {-1, -1, 0,  0,  0,  -1, 0,  0,  0,  0,  0,  0,  -1, 0,  -1},
                         {-1, 0,  0,  -1, 0,  -1, -1, -1, -1, -1, 0,  -1, 0,  0,  -1},
                         {-1, 0,  -1, 0,  0,  -1, 0,  0,  0,  0,  0,  -1, -1, 0,  -1},
                         {-1, 0,  0,  -1, -1, -1, 0,  -1, -1, -1, 0,  0,  0,  0,  -1},
                         {-1, -1, -1, 0,  0,  0,  0,  -1, 0,  0,  0,  -1, -1, -1, -1},
                         {-1, 0,  0,  -1, -1, 0,  -1, -1, -1, -1, -1, 0,  0,  0,  0},
                         {-1, -1, 0,  0,  0,  0,  -1, 0,  0,  0,  0,  0,  -1, 0,  -1},
                         {-1, 0,  0,  -1, -1, 0,  0,  0,  -1, -1, -1, -1, 0,  0,  -1},
                         {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};

int main(int argc, char **argv) {
    init_app();

    list_t *list;
    new_list(&list);

    list_t *report_rm;
    list_t *report_edf;
    new_list(&report_rm);
    new_list(&report_edf);

    run(map, list, &MAX_ENERGY, report_rm, report_edf);
    struct arg_struct args;
    args.num_aliens = size(list);
    args.aliens = list;
    args.report_rm = report_rm;
    args.report_edf = report_edf;
    args.page = 0;
    report_run(&args);
    return 0;
}
