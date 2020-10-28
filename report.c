//
// Created by marco on 27/10/20.
//

#include "report.h"
#include <stdio.h>

ALLEGRO_DISPLAY *report_display;
ALLEGRO_EVENT_QUEUE *report_event_queue;
ALLEGRO_TIMER *report_timer;

const float REPORT_FPS = 30.0;

void report_init_app() {
    ALLEGRO_MONITOR_INFO info;
    al_get_monitor_info(ALLEGRO_DEFAULT_DISPLAY_ADAPTER, &info);
    printf("X: %d\n", info.x2 - info.x1);
    printf("Y: %d\n", info.y2);

    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
}

void report_run(int num_aliens) {
    int row_height = 50;
    int report_height = row_height * (num_aliens + 3) + 40;
    report_display = al_create_display(REPORT_WIDTH, report_height);
    char *window_title = "Report";
    al_set_window_title(report_display, window_title);

    report_timer = al_create_timer(1.0 / REPORT_FPS);

    report_event_queue = al_create_event_queue();
    al_register_event_source(report_event_queue, al_get_keyboard_event_source());
    al_register_event_source(report_event_queue, al_get_display_event_source(report_display));
    al_register_event_source(report_event_queue, al_get_timer_event_source(report_timer));


    bool running = true;
    al_start_timer(report_timer);
    while (running) {
        al_clear_to_color(al_map_rgb(255, 255, 255));

        ALLEGRO_EVENT event;
        al_wait_for_event(report_event_queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                break;
            default:
                break;
        }
//        al_draw_filled_rectangle(0, 0, UNIT_SIDE, UNIT_SIDE, al_map_rgb(0, 0, 0));
        draw_axis(num_aliens, row_height, report_height);
        al_flip_display();
    }
    report_destroy();
}

void draw_axis(int num_aliens, int row_height, int height) {
    int units = 4;
    float step_width = units * UNIT_SIDE;
    int steps = REPORT_WIDTH / step_width;
    float x_offset = (REPORT_WIDTH - step_width * steps) / 2 + 60;
    float y_offset = 40;
    char str[100];
    ALLEGRO_FONT *font = al_load_font("assets/arial.ttf", 16, 0);

    for (int i = 0; i < steps-1; i += 1) {
        al_draw_line(x_offset + step_width * i, y_offset, x_offset + step_width * i, height - y_offset,
                     al_map_rgb(0, 0, 0), 2);
        sprintf(str, "%d", i * units);
        al_draw_text(font, al_map_rgb(0, 0, 0), x_offset + step_width * i - 4, height - 2 * y_offset / 3,
                     ALLEGRO_ALIGN_LEFT,
                     str);

    }
    al_draw_text(font, al_map_rgb(0, 0, 0), 10, height - y_offset - row_height, ALLEGRO_ALIGN_LEFT, "RMS");
    al_draw_text(font, al_map_rgb(0, 0, 0), 10, height - y_offset - 2 * row_height, ALLEGRO_ALIGN_LEFT, "EDF");
    for (int i = 0; i < num_aliens; i += 1) {
        al_draw_text(font, al_map_rgb(0, 0, 0), 10, height - y_offset - (i + 3) * row_height,
                     ALLEGRO_ALIGN_LEFT, "p");
    }

}

void report_destroy() {
    al_destroy_display(report_display);
    al_destroy_timer(report_timer);
//    al_destroy_font()
}