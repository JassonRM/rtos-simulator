CC=gcc
CFLAGS=
ALLEGRO = `pkg-config --cflags --libs allegro-5`
DEPS =

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: application

application: main.o
	$(CC) main.o $(ALLEGRO) -o rtos-simulator

main.o: main.c
	$(CC) -c $(CFLAGS) main.c -o main.o

clean:
	rm *o rtos-simulator