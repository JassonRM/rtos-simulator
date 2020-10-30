//
// Created by jasson on 25/10/20.
//
#include "gui.h"
#include "scheduler.h"
#include <pthread.h>


const float FPS = 30.0;

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *block;
ALLEGRO_BITMAP *martian;
ALLEGRO_FONT *font;
int cycle = 0;
bool running, running_auto;

void init_app() {
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    srand(time(NULL));
}

void run(int map[MAP_Y][MAP_X], list_t *alien_list, int *max_energy, list_t *report_rm, list_t *report_edf) {
    ALLEGRO_DISPLAY *display = al_create_display(WIDTH, HEIGHT);
    char *window_title = "RTOS Simulator";
    al_set_window_title(display, window_title);

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    block = al_load_bitmap("assets/block.png");
    martian = al_load_bitmap("assets/martian.png");
    font = al_load_font("assets/arial.ttf", 16, 0);

    int cell_size = 50;
    int offset_x = 3 * cell_size;
    int offset_y = cell_size;

    int exec_time = 1;
    int period = 1;

    running = true;
    running_auto = false;
    int mode = 0;
    int aliens = 1;

    int j = 0;
    al_start_timer(timer);
    while (running) {
        al_clear_to_color(al_map_rgb(255, 255, 255));

        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        int mouse_x, mouse_y;
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_X) {
                    running = false;
                }
                break;
            case ALLEGRO_EVENT_TIMER:
                if (running_auto == false) { break; }
                if (j == 15) {
                    next_clock(map, alien_list, mode, report_rm, report_edf);
                    j = 0;
                }
                j += 1;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
                if (mouse_y > 0 && mouse_y < cell_size) {
                    if (mouse_x > 0.5 * cell_size && mouse_x < 2.5 * cell_size) {
                        if (mode == 0) {
                            mode = 1;
                        } else {
                            mode = 0;
                        }
                    } else if (mouse_x > 0.5 * cell_size + offset_x && mouse_x < 2.5 * cell_size + offset_x) {
                        // Automatic mode
                        running_auto = true;

                    } else if (mouse_x > 3 * cell_size + offset_x && mouse_x < 5.5 * cell_size + offset_x) {
                        // Manual mode
                        next_clock(map, alien_list, mode, report_rm, report_edf);
                    } else if (mouse_x > 7.5 * cell_size + offset_x && mouse_x < 8.1 * cell_size + offset_x) {
                        // Sub exec time
                        if (exec_time > 1) {
                            exec_time--;
                        }
                    } else if (mouse_x > 8.7 * cell_size + offset_x && mouse_x < 9.3 * cell_size + offset_x) {
                        // Add exec time
                        if (exec_time < 99) {
                            exec_time++;
                        }
                    } else if (mouse_x > 10.8 * cell_size + offset_x && mouse_x < 11.4 * cell_size + offset_x) {
                        // Sub period
                        if (period > 1) {
                            period--;
                        }
                    } else if (mouse_x > 12 * cell_size + offset_x && mouse_x < 12.6 * cell_size + offset_x) {
                        // Add period
                        if (period < 99) {
                            period++;
                        }
                    } else if (mouse_x > 12.8 * cell_size + offset_x && mouse_x < 15 * cell_size + offset_x) {
                        if (!running_auto) {
                            // Add martian
                            printf("New alien\n");
                            alien_t *alien;
                            init_alien(&alien, aliens, cycle, period, exec_time, max_energy);
                            append(alien_list, alien);
                            while (map[alien->y][alien->x] != 0) {
                                alien->x = rand() % 15;
                                alien->y = rand() % 15;
                            }
                            map[alien->y][alien->x] = aliens;
                            aliens++;
                        }
                    }
                }
                break;
            default:
                break;
        }
        al_flush_event_queue(event_queue);
        // Draw toolbar

        // Change mode
        al_draw_filled_rounded_rectangle(0.5 * cell_size, cell_size / 4, 2.5 * cell_size, 3 * cell_size / 4, 10, 10,
                                         al_map_rgb(0, 191, 255));
        if (mode == 0) {
            al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * cell_size + cell_size / 4, cell_size / 3, NULL,
                         "Use EDF");
        } else {
            al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * cell_size + cell_size / 4, cell_size / 3, NULL,
                         "Use RM");
        }

        // Auto mode
        al_draw_filled_rounded_rectangle(0.5 * cell_size + offset_x, cell_size / 4, 2.5 * cell_size + offset_x,
                                         3 * cell_size / 4, 10, 10, al_map_rgb(0, 191, 255));
        al_draw_text(font, al_map_rgb(0, 0, 0), 0.5 * cell_size + cell_size / 4 + offset_x, cell_size / 3, NULL,
                     "Auto mode");

        // Manual mode
        al_draw_filled_rounded_rectangle(3 * cell_size + offset_x, cell_size / 4, 5.5 * cell_size + offset_x,
                                         3 * cell_size / 4, 10, 10, al_map_rgb(0, 191, 255));
        al_draw_text(font, al_map_rgb(0, 0, 0), 3 * cell_size + cell_size / 4 + offset_x, cell_size / 3, NULL,
                     "Manual mode");

        // Exec time
        al_draw_text(font, al_map_rgb(0, 0, 0), 5.6 * cell_size + cell_size / 4 + offset_x, cell_size / 3, NULL,
                     "Exec time:");

        // Sub button
        al_draw_filled_rounded_rectangle(7.5 * cell_size + offset_x, cell_size / 4, 8.1 * cell_size + offset_x,
                                         3 * cell_size / 4, 10, 10, al_map_rgb(0, 191, 255));
        al_draw_text(font, al_map_rgb(0, 0, 0), 7.5 * cell_size + cell_size / 4 + offset_x, cell_size / 3, NULL, "-");

        // Exec time label
        char exec_time_label[2];
        sprintf(exec_time_label, "%d", exec_time);
        al_draw_text(font, al_map_rgb(0, 0, 0), 8 * cell_size + cell_size / 4 + offset_x, cell_size / 3, NULL,
                     exec_time_label);

        // Plus button
        al_draw_filled_rounded_rectangle(8.7 * cell_size + offset_x, cell_size / 4, 9.3 * cell_size + offset_x,
                                         3 * cell_size / 4, 10, 10, al_map_rgb(0, 191, 255));
        al_draw_text(font, al_map_rgb(0, 0, 0), 8.7 * cell_size + cell_size / 4 + offset_x, cell_size / 3, NULL, "+");

        // Period
        al_draw_text(font, al_map_rgb(0, 0, 0), 9.4 * cell_size + cell_size / 4 + offset_x, cell_size / 3, NULL,
                     "Period:");

        // Sub button
        al_draw_filled_rounded_rectangle(10.8 * cell_size + offset_x, cell_size / 4, 11.4 * cell_size + offset_x,
                                         3 * cell_size / 4, 10, 10, al_map_rgb(0, 191, 255));
        al_draw_text(font, al_map_rgb(0, 0, 0), 10.8 * cell_size + cell_size / 4 + offset_x, cell_size / 3, NULL, "-");

        // period label
        char period_label[2];
        sprintf(period_label, "%d", period);
        al_draw_text(font, al_map_rgb(0, 0, 0), 11.3 * cell_size + cell_size / 4 + offset_x, cell_size / 3, NULL,
                     period_label);

        // Plus button
        al_draw_filled_rounded_rectangle(12 * cell_size + offset_x, cell_size / 4, 12.6 * cell_size + offset_x,
                                         3 * cell_size / 4, 10, 10, al_map_rgb(0, 191, 255));
        al_draw_text(font, al_map_rgb(0, 0, 0), 12 * cell_size + cell_size / 4 + offset_x, cell_size / 3, NULL, "+");

        // Add martian button
        al_draw_filled_rounded_rectangle(12.8 * cell_size + offset_x, cell_size / 4, 15 * cell_size + offset_x,
                                         3 * cell_size / 4, 10, 10, al_map_rgb(0, 191, 255));
        al_draw_text(font, al_map_rgb(0, 0, 0), 12.8 * cell_size + cell_size / 4 + offset_x, cell_size / 3, NULL,
                     "Add martian");

        // Draw map and status
        int id;
        alien_t *alien;
        int current_position = 0;
        for (int i = 0; i < MAP_X; i++) {
            for (int j = 0; j < MAP_Y; j++) {
                id = map[j][i];
                switch (id) {
                    case 0:
                        // Empty space
                        break;
                    case -1:
                        // Block
                        al_draw_scaled_bitmap(block, 0, 0, 48, 48, cell_size * i + offset_x, cell_size * j + offset_y,
                                              cell_size,
                                              cell_size, NULL);
                        break;
                    default:
                        // Alien
                        alien = get_by_id(alien_list, id);
                        if (alien != NULL) {
                            al_draw_filled_rectangle(cell_size * i + offset_x, cell_size * j + offset_y,
                                                     cell_size * i + offset_x + cell_size,
                                                     cell_size * j + cell_size + offset_y,
                                                     al_map_rgb(alien->r, alien->g, alien->b));
                            al_draw_scaled_bitmap(martian, 0, 0, 428, 428, cell_size * i + offset_x,
                                                  cell_size * j + offset_y,
                                                  cell_size,
                                                  cell_size, NULL);

                            // Draw energy bar
                            al_draw_filled_rectangle(0, current_position * cell_size + offset_y, cell_size,
                                                     current_position * cell_size + cell_size + offset_y,
                                                     al_map_rgb(alien->r, alien->g, alien->b));
                            al_draw_scaled_bitmap(martian, 0, 0, 428, 428, 0, current_position * cell_size + offset_y,
                                                  cell_size,
                                                  cell_size, NULL);
                            float energy = alien->rem_time / (float) *max_energy;
                            int energy_bar = energy * 2 * cell_size;
                            ALLEGRO_COLOR color;
                            if (energy > 0.2) {
                                color = al_map_rgb(0, 200, 0);
                            } else {
                                color = al_map_rgb(200, 0, 0);
                            }
                            al_draw_filled_rectangle(cell_size, current_position * cell_size + offset_y,
                                                     cell_size + energy_bar,
                                                     current_position * cell_size + cell_size + offset_y, color);
                            al_draw_rectangle(cell_size, current_position * cell_size + offset_y, cell_size * 3,
                                              current_position * cell_size + cell_size + offset_y, al_map_rgb(0, 0, 0),
                                              2);
                            current_position++;
                        }
                        break;
                }
            }
        }
        al_flip_display();
    }
    destroy();
}

void move(alien_t *alien, int map[MAP_Y][MAP_X]) {
    int direction = rand() % 4;
    bool done = false;
    while (!done) {
        switch (direction) {
            case 0: // Left
                if (alien->x > 0 && map[alien->y][alien->x - 1] == 0) {
                    map[alien->y][alien->x] = 0;
                    alien->x -= 1;
                    map[alien->y][alien->x] = alien->id;
                    done = true;
                }
                break;
            case 1: // Right
                if (alien->x < MAP_X - 1 && map[alien->y][alien->x + 1] == 0) {
                    map[alien->y][alien->x] = 0;
                    alien->x += 1;
                    map[alien->y][alien->x] = alien->id;
                    done = true;
                }
                break;
            case 2: // Up
                if (alien->y > 0 && map[alien->y - 1][alien->x] == 0) {
                    map[alien->y][alien->x] = 0;
                    alien->y -= 1;
                    map[alien->y][alien->x] = alien->id;
                    done = true;
                }
                break;
            case 3: // Down
                if (alien->y < MAP_Y - 1 && map[alien->y + 1][alien->x] == 0) {
                    map[alien->y][alien->x] = 0;
                    alien->y += 1;
                    map[alien->y][alien->x] = alien->id;
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
    al_destroy_bitmap(martian);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
}

void next_clock(int map[MAP_X][MAP_Y], list_t *alien_list, int mode, list_t *report_rm, list_t *report_edf) {
    alien_t *next_rm, *next_edf;
    if (mode == 0) {
        next_rm = step(alien_list, 0, cycle);
        append(report_rm, next_rm);
        if (next_rm != NULL) {
            if (next_rm->id != -1) {
                move(next_rm, map);
            } else {
                running = false;
            }
        }
    } else {
        next_edf = step(alien_list, 1, cycle);
        append(report_edf, next_edf);
        if (next_edf != NULL) {
            if (next_edf->id != -1) {
                move(next_edf, map);
            } else {
                running = false;
            }
        }
    }
    cycle++;
}
