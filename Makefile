CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -g

game: util.o

util.o: util.h

vga_led.o: vga_led.h

.PHONY: all
all:
	clean game

.PHONY: clean
clean:
	rm *.o game