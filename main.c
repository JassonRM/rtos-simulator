#include "gui.h"

int main(int argc, char** argv) {
    init_app();

    int map[MAP_X][MAP_Y] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                             {0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
                             {1, 0, 1, 1, 0, 1, 0, 0, 1, 1},
                             {1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
                             {1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
                             {1, 0, 0, 1, 0 ,0 ,0, 1, 0, 1},
                             {1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
                             {1, 0, 0, 1, 0, 1, 1, 0, 1, 1},
                             {1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    run(map);
    return 0;
}
