# Makefile for very simple example Posix threads usage
# The executable built is:
#	sthread
#
CC = gcc
CFLAGS = -Wall
LIBS = -lpthread

sthread: sthread.o
	$(CC) -o sthread sthread.o $(LIBS)

clean:
	rm -f sthread *.o
