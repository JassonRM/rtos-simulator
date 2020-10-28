CC=gcc
CFLAGS=
LIBS = `pkg-config --cflags --libs allegro-5 allegro_image-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5`
DEPS = %.h
TARGET = rtos-simulator
OBJFILES = main.o gui.o alien.o scheduler.o miscellaneous.o report.o
#OBJFILES = scheduler_test.o gui.o alien.o scheduler.o miscellaneous.o report.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o $(TARGET) $(LIBS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~