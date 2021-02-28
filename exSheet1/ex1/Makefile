# Makefile example 1
#
# Executable to be created: hello
# source code is : hello.c , client.c
# The sources need: hello.h  
# For testing, all needed files can be found in the current directory 
#
all: hello

hello: hello.o				# Link the object files together to create an executable
	cc hello.o -o hello

hello.o: hello.c hello.h	#compile hello.c into a .o object file (converts source code into machine code)
	cc -Wall -c hello.c

clean:
	rm -f hello  \
	hello.o
