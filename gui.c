//
// Created by jasson on 25/10/20.
//
#include "gui.h"
#include <stdio.h>

const float FPS = 30.0;

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *block;
ALLEGRO_BITMAP *martian;

void init_app() {
    ALLEGRO_MONITOR_INFO info;
    al_get_monitor_info(ALLEGRO_DEFAULT_DISPLAY_ADAPTER, &info);
    printf("X: %d\n", info.x2 - info.x1);
    printf("Y: %d\n", info.y2);

    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
}

void run(int map[MAP_X][MAP_Y]) {
    ALLEGRO_DISPLAY *display = al_create_display(WIDTH, HEIGHT);
    char *window_title = "RTOS Simulator";
    al_set_window_title(display, window_title);

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    block = al_load_bitmap("assets/block.png");
    martian = al_load_bitmap("assets/martian_blue.png");

    int cell_size = 100;
    int offset_x = 200;

    bool running = true;
    al_start_timer(timer);
    while (running) {
        al_clear_to_color(al_map_rgb(255, 255, 255));

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                break;
            default:
                break;
        }
        for (int i = 0; i < MAP_X; i++) {
            for (int j = 0; j < MAP_Y; j++) {
                switch (map[j][i]) {
                    case 1:
                        al_draw_scaled_bitmap(block, 0, 0, 48, 48, cell_size * i + offset_x, cell_size * j, cell_size,
                                              cell_size, NULL);
                        break;
                    case 2:
                        al_draw_scaled_bitmap(martian, 0, 0, 213, 428, cell_size * i + offset_x, cell_size * j, cell_size,
                                              cell_size, NULL);
                        break;
                    default:
                        continue;
                }
            }
        }
        al_flip_display();
    }
    destroy();
}

void destroy() {
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_bitmap(block);
}
