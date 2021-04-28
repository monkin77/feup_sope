# Executable to be created: 
# source code is : main.c 
# For testing, all needed files can be found in the current directory 
#
all: upper upper2

upper: upper.o				# Link the object files together to create an executable
	cc upper.o -o upper

upper.o: upper.c	#compile .c into a .o object file (converts source code into machine code)
	cc -Wall -c upper.c

upper2: upper2.o				# Link the object files together to create an executable
	cc upper2.o -o upper2

upper2.o: upper2.c	#compile .c into a .o object file (converts source code into machine code)
	cc -Wall -c upper2.c



clean:
	rm -f upper upper2 \
	*.o
