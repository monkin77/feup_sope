# Makefile for count - test of problems with shared vars
#
all: count count2

count: count.c
	 gcc -Wall count.c -o count -lpthread

count2: count2.c
	 gcc -Wall count2.c -o count2 -lpthread

clean:
	rm -f *.o count count2
