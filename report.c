//
// Created by marco on 27/10/20.
//

#include "report.h"


ALLEGRO_DISPLAY *report_display;
ALLEGRO_EVENT_QUEUE *report_event_queue;
ALLEGRO_TIMER *report_timer;
ALLEGRO_FONT *report_font;


const float REPORT_FPS = 30.0;

void report_run(int num_aliens, list_t *aliens, list_t *report, int mode) {
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

    report_font = al_load_font("assets/arial.ttf", 16, 0);

    bool running = true;
    al_start_timer(report_timer);

    int units = 5;
    float x_offset = 60;
    float y_offset = 40;
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
        draw_aliens(row_height, report_height, aliens, units, x_offset, y_offset);
        draw_report(row_height, report_height, report, units, x_offset, y_offset, mode);
        draw_axis(num_aliens, row_height, report_height, aliens, units, x_offset, y_offset);


        al_flip_display();
    }
    report_destroy();
}

void draw_axis(int num_aliens, int row_height, int height, list_t *aliens, int units, float x_offset, float y_offset) {
    float step_width = units * UNIT_SIDE;
    int steps = REPORT_WIDTH / step_width;
    x_offset += (REPORT_WIDTH - step_width * steps) / 2;
    char str[100];

    for (int i = 0; i < steps - 1; i += 1) {
        al_draw_line(x_offset + step_width * i, y_offset, x_offset + step_width * i, height - y_offset,
                     al_map_rgb(0, 0, 0), 2);
        sprintf(str, "%d", i * units);
        al_draw_text(report_font, al_map_rgb(0, 0, 0), x_offset + step_width * i - 4, height - 2 * y_offset / 3,
                     ALLEGRO_ALIGN_LEFT,
                     str);

    }
    al_draw_text(report_font, al_map_rgb(0, 0, 0), 10, height - y_offset - row_height, ALLEGRO_ALIGN_LEFT, "RMS");
    al_draw_text(report_font, al_map_rgb(0, 0, 0), 10, height - y_offset - 2 * row_height, ALLEGRO_ALIGN_LEFT,
                 "EDF");


    if (aliens == NULL) {
        return NULL;
    }
    node_t *head = aliens->element;
    node_t *temp = head;
    if (head == NULL) {
        return NULL;
    }
    alien_t *next = NULL;
    int i = 0;
    char id[100];
    while (temp != NULL) {
        sprintf(id, "%d", temp->alien->id);
        al_draw_text(report_font, al_map_rgb(0, 0, 0), 10, height - y_offset - (i + 3) * row_height,
                     ALLEGRO_ALIGN_LEFT, id);
        temp = temp->next;
        i += 1;
    }

}

void draw_aliens(int row_height, int height, list_t *aliens, int units, float x_offset, float y_offset) {

    float step_width = units * UNIT_SIDE;
    int steps = REPORT_WIDTH / step_width;
    x_offset += (REPORT_WIDTH - step_width * steps) / 2;

    if (aliens == NULL) {
        return NULL;
    }
    node_t *head = aliens->element;
    node_t *temp = head;
    if (head == NULL) {
        return NULL;
    }
    alien_t *next = NULL;

    float x, y;
    int i = 0;
    int j;
    while (temp != NULL) {
        x = x_offset;
        y = height - y_offset - (i + 3) * row_height;
        j = 0;
        while (x < REPORT_WIDTH - temp->alien->exec_time * UNIT_SIDE) {
            if (j % temp->alien->period == temp->alien->offset) {
                al_draw_filled_rectangle(x, y, x + UNIT_SIDE * temp->alien->exec_time, y + UNIT_SIDE,
                                         al_map_rgb(temp->alien->r, temp->alien->g, temp->alien->b));
                al_draw_rectangle(x, y, x + UNIT_SIDE * temp->alien->exec_time, y + UNIT_SIDE, al_map_rgb(0, 0, 0), 1);
            }
            x += UNIT_SIDE;
            j += 1;
        }
        i += 1;
        temp = temp->next;
    }


}

void draw_report(int row_height, int height, list_t *report, int units, float x_offset, float y_offset, int mode) {
    mode += 1;
    float step_width = units * UNIT_SIDE;
    int steps = REPORT_WIDTH / step_width;
    x_offset += (REPORT_WIDTH - step_width * steps) / 2;

    if (report == NULL) {
        return NULL;
    }
    node_t *head = report->element;
    node_t *temp = head;
    if (head == NULL) {
        return NULL;
    }
    alien_t *next = NULL;

    float x, y;
    x = x_offset;
    while (temp != NULL) {
        if (temp->alien != NULL) {
            y = height - y_offset - mode * row_height;
            al_draw_filled_rectangle(x, y, x + UNIT_SIDE, y + UNIT_SIDE,
                                     al_map_rgb(temp->alien->r, temp->alien->g, temp->alien->b));
            al_draw_rectangle(x, y, x + UNIT_SIDE, y + UNIT_SIDE, al_map_rgb(0, 0, 0), 1);
        }
        temp = temp->next;
        x += UNIT_SIDE;
    }
}


void report_destroy() {
    al_destroy_display(report_display);
    al_destroy_timer(report_timer);
    al_destroy_font(report_font);
}

