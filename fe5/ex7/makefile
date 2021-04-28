# Executable to be created: 
# source code is : main.c 
# For testing, all needed files can be found in the current directory 
#
all: main noeco

main: main.o				# Link the object files together to create an executable
	cc main.o -o main

main.o: main.c	#compile .c into a .o object file (converts source code into machine code)
	cc -Wall -c main.c

noeco: noeco.o
	cc noeco.o -o noeco

noeco.o: noeco.c
	cc -Wall -c noeco.c

clean:
	rm -f main  \ noeco \
	*.o
