# Executable to be created: 
# source code is : main.c 
# For testing, all needed files can be found in the current directory 
#
all: main alinA alinB alinC

main: main.o				# Link the object files together to create an executable
	cc main.o -o main

main.o: main.c	#compile .c into a .o object file (converts source code into machine code)
	cc -Wall -c main.c

alinA: alinA.o
	cc alinA.o -o alinA

alinA.o: alinA.c
	cc -Wall -c alinA.c

alinB: alinB.o
	cc alinB.o -o alinB

alinB.o: alinB.c
	cc -Wall -c alinB.c

alinC: alinC.o
	cc alinC.o -o alinC

alinC.o: alinC.c
	cc -Wall -c alinC.c

clean:
	rm -f main  \
	main.o \
	sexec \
	sexec.o \
	alinA \
	alinA.o \
	alinB \
	alinB.o \
	alinC \
	alinC.o \
