rtos-simulator: main.c
	gcc main.c -o main `pkg-config --cflags --libs allegro-5`