# Makefile for very simple example Posix threads usage
# The executable built is:
# main
#
CC = gcc
CFLAGS = -Wall
LIBS = -lpthread

main: main.o
	$(CC) -o main main.o $(LIBS)

clean:
	rm -f main *.o
