#include "allegro5/allegro5.h"

int main(int argc, char** argv) {
    al_init();
    al_install_keyboard();
    al_install_mouse();

    ALLEGRO_DISPLAY* window = al_create_display(800, 800);
    char* window_title = "RTOS Simulator";
    al_set_window_title(window, window_title);

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(window));

    while (true){
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                al_destroy_display(window);
                return 0;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                al_destroy_display(window);
                return 0;
                break;
            default:
                break;
        }
        al_flip_display();
    }
    return 0;
}
