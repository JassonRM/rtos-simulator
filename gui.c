//
// Created by jasson on 25/10/20.
//
#include "gui.h"


const float FPS = 30.0;

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *block;
ALLEGRO_BITMAP *martian;
ALLEGRO_FONT *font;

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

void run(int map[MAP_Y][MAP_X], list_t *alien_list, int *max_energy) {
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
    font = al_load_font("assets/arial.ttf", 16, 0);

    int cell_size = 50;
    int offset_x = 3 * cell_size;
    int offset_y = cell_size;

    bool running = true;
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
                if(event.keyboard.keycode == ALLEGRO_KEY_X){
                    running = false;
                }
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
                if(mouse_y > 20 && mouse_y < 80){
                    if(mouse_x > 200 + offset_x && mouse_x < 400 + offset_x){
                        automatic_mode();
                    }else if(mouse_x > 500 + offset_x && mouse_x < 750 + offset_x){
                        manual_mode();
                    }
                }
            default:
                break;
        }
        // Draw toolbar
        // Auto mode
        al_draw_filled_rounded_rectangle(2 * cell_size + offset_x, cell_size / 4, 4 * cell_size + offset_x, 3 * cell_size / 4, 10, 10, al_map_rgb(100, 100, 200));
        al_draw_text(font, al_map_rgb(0, 0, 0), 2 * cell_size + cell_size / 4 + offset_x, cell_size / 3, NULL, "Auto mode");

        // Manual mode
        al_draw_filled_rounded_rectangle(5 * cell_size + offset_x, cell_size / 4, 7.5 * cell_size + offset_x, 3 * cell_size / 4, 10, 10, al_map_rgb(100, 100, 200));
        al_draw_text(font, al_map_rgb(0, 0, 0), 5 * cell_size + cell_size / 4 + offset_x, cell_size / 3, NULL, "Manual mode");


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
                        al_draw_scaled_bitmap(block, 0, 0, 48, 48, cell_size * i + offset_x, cell_size * j + offset_y, cell_size,
                                              cell_size, NULL);
                        break;
                    default:
                        // Alien
                        alien = get_by_id(alien_list, id);
                        if (alien != NULL) {
                            al_draw_filled_rectangle(cell_size * i + offset_x, cell_size * j + offset_y,
                                                     cell_size * i + offset_x + cell_size, cell_size * j + cell_size + offset_y,
                                                     al_map_rgb(alien->r, alien->g, alien->b));
                            al_draw_scaled_bitmap(martian, 0, 0, 428, 428, cell_size * i + offset_x, cell_size * j + offset_y,
                                                  cell_size,
                                                  cell_size, NULL);

                            // Draw energy bar
                            al_draw_filled_rectangle(0, current_position * cell_size, cell_size,
                                                     current_position * cell_size + cell_size,
                                                     al_map_rgb(alien->r, alien->g, alien->b));
                            al_draw_scaled_bitmap(martian, 0, 0, 428, 428, 0, current_position * cell_size,
                                                  cell_size,
                                                  cell_size, NULL);
                            float energy = alien->exec_time / (float) *max_energy;
                            int energy_bar = energy * 2 * cell_size;
                            ALLEGRO_COLOR color;
                            if(energy > 0.2){
                                color = al_map_rgb(0, 200, 0);
                            }else{
                                color = al_map_rgb(200, 0, 0);
                            }
                            al_draw_filled_rectangle(cell_size, current_position * cell_size, cell_size + energy_bar, current_position * cell_size + cell_size, color);
                            al_draw_rectangle(cell_size, current_position * cell_size, cell_size * 3, current_position * cell_size + cell_size, al_map_rgb(0, 0, 0), 2);
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

void automatic_mode(){

}

void manual_mode(){

}
