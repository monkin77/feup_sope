# Executable to be created: 
# source code is : main.c 
# For testing, all needed files can be found in the current directory 
#

CFLAGS = -Wall -fno-stack-protector

all: main

main: main.o				# Link the object files together to create an executable
	cc main.o -o main

main.o: main.c	#compile .c into a .o object file (converts source code into machine code)
	cc $(CFLAGS) -c main.c

clean:
	rm -f main  \
	main.o
