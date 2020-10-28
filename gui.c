//
// Created by jasson on 25/10/20.
//
#include "gui.h"
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

const float FPS = 30.0;

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *block;
ALLEGRO_BITMAP *martian;

void init_app() {
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    srand(time(NULL));
}

void run(int map[MAP_Y][MAP_X], list_t *alien_list) {
    ALLEGRO_DISPLAY *display = al_create_display(WIDTH, HEIGHT);
    char *window_title = "RTOS Simulator";
    al_set_window_title(display, window_title);

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    block = al_load_bitmap("assets/block.png");
    martian = al_load_bitmap("assets/martian.png");

    int cell_size = 100;
    int offset_x = 300;

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
        int id;
        alien_t *alien;
        for (int i = 0; i < MAP_X; i++) {
            for (int j = 0; j < MAP_Y; j++) {
                id = map[j][i];
                switch (id) {
                    case 0:
                        break;
                    case -1:
                        al_draw_scaled_bitmap(block, 0, 0, 48, 48, cell_size * i + offset_x, cell_size * j, cell_size,
                                              cell_size, NULL);
                        break;
                    default:
                        alien = get_by_id(alien_list, id);
                        al_draw_filled_rectangle(cell_size * i + offset_x, cell_size * j, cell_size * i + offset_x + cell_size, cell_size * j + cell_size, al_map_rgb(alien->r, alien->g, alien->b));
                        al_draw_scaled_bitmap(martian, 0, 0, 428, 428, cell_size * i + offset_x, cell_size * j,
                                              cell_size,
                                              cell_size, NULL);
                        break;
                }
            }
        }
        if(alien_list != NULL && alien_list->element != NULL){
            int current_position = 0;
            node_t *current = alien_list->element;
            ALLEGRO_FONT *font = al_load_font("assets/arial.ttf", 16, 0);
            do {
                // Draw energy bars
                al_draw_text(font, al_map_rgb(0, 0, 0), current_position * 100 + 50, 50, NULL, "1");
                al_draw_filled_rectangle(current_position * 100, 0, current_position * 100 + cell_size, cell_size, al_map_rgb(alien->r, alien->g, alien->b));
                al_draw_scaled_bitmap(martian, 0, 0, 428, 428, current_position * 100, 0,
                                      cell_size,
                                      cell_size, NULL);
            } while (current->next != NULL);
        }
        al_flip_display();
    }
    destroy();
}

void move(alien_t *alien, int map[MAP_Y][MAP_X]) {
    int direction = alien->direction;
    bool done = false;
    while (!done) {
        switch (direction) {
            case 0: // Left
                if (alien->x > 0 && map[alien->x - 1][alien->y] == 0) {
                    map[alien->x][alien->y] = 0;
                    alien->x -= 1;
                    map[alien->x][alien->y] = alien->id;
                    done = true;
                }
                break;
            case 1: // Right
                if (alien->x < MAP_X - 1 && map[alien->x + 1][alien->y] == 0) {
                    map[alien->x][alien->y] = 0;
                    alien->x += 1;
                    map[alien->x][alien->y] = alien->id;
                    done = true;
                }
                break;
            case 2: // Up
                if (alien->y > 0 && map[alien->x][alien->y - 1] == 0) {
                    map[alien->x][alien->y] = 0;
                    alien->y -= 1;
                    map[alien->x][alien->y] = alien->id;
                    done = true;
                }
                break;
            case 3: // Down
                if (alien->y < MAP_Y - 1 && map[alien->x][alien->y + 1] == 0) {
                    map[alien->x][alien->y] = 0;
                    alien->y += 1;
                    map[alien->x][alien->y] = alien->id;
                    done = true;
                }
                break;
            default:
                break;
        }
        direction = rand() % 4;
    }
};

void destroy() {
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_bitmap(block);
}
