
CC=gcc
CFLAGS=-I.
DEPS = header.h
OBJ = main.o functions.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cshell: $(OBJ)
	gcc -o $@ $^ $(CFLAGS); rm *.o
