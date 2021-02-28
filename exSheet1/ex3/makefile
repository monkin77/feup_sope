# Executable to be created: example
# source code is : example.c 
# For testing, all needed files can be found in the current directory 
#
all: example

example: example.o				# Link the object files together to create an executable
	cc example.o -o example

example.o: example.c	#compile .c into a .o object file (converts source code into machine code)
	cc -Wall -c example.c

clean:
	rm -f example  \
	example.o
