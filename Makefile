CC=gcc
CFLAGS=
LIBS = `pkg-config --cflags --libs allegro-5 allegro_image-5` -pthread
DEPS = %.h
TARGET = rtos-simulator
OBJFILES = main.o gui.o alien.o scheduler.o miscellaneous.o
#OBJFILES = scheduler_test.o gui.o alien.o scheduler.o miscellaneous.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o $(TARGET) $(LIBS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~