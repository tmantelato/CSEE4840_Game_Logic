CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -g

 
game: util.o

util.o: util.h

.PHONY: all
all:
	clean game

.PHONY: clean
clean:
	rm *.o game

