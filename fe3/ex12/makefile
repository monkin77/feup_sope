# Makefile for count - test of problems with shared vars
#
all: bbcount f_bbcount2 f_bbcount3 -lpthread -lrt

bbcount: bbcount.c
	 gcc -Wall bbcount.c -o bbcount -lpthread

f_bbcount2: f_bbcount2.c
	gcc -Wall f_bbcount2.c -o f_bbcount2 -lpthread

f_bbcount3: f_bbcount3.c
	gcc -Wall f_bbcount3.c -o f_bbcount3 -lpthread

clean:
	rm -f *.o bbcount f_bbcount2 f_bbcount3
