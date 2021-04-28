# Executable to be created: 
# source code is : main.c 
# For testing, all needed files can be found in the current directory 
#
all: a b c d

a: a.o				# Link the object files together to create an executable
	cc a.o -o a

a.o: a.c	#compile .c into a .o object file (converts source code into machine code)
	cc -Wall -c a.c

b: b.o 				# Link the object files together to create an executable

b.o: b.c	#compile .c into a .o object file (converts source code into machine code)	
	cc -Wall -c b.c	

c: c.o 				# Link the object files together to create an executable

c.o: c.c	#compile .c into a .o object file (converts source code into machine code)	
	cc -Wall -c c.c	

d: d.o 				# Link the object files together to create an executable

d.o: d.c	#compile .c into a .o object file (converts source code into machine code)	
	cc -Wall -c d.c	

clean:
	rm -f a  \
	a.o \
	b \
	b.o \
	c \
	c.o \
