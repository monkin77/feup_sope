# Makefile example 1
#
# Two executables are to be created: bank , client
# Their source code is, respectively: bank.c , client.c
# The sources need, respectively: (common.h , bank.h) , common.h
# For testing, all needed files can be found in the current directory 
#
all: bank client	

bank: bank.o
	cc bank.o -o bank

client: client.o
	cc client.o -o client

bank.o: bank.c common.h bank.h
	cc -Wall -c bank.c

client.o: client.c common.h
	cc -Wall -c client.c

clean:
	rm -f bank client \
		bank.o client.o
