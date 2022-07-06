CC = gcc

CFLAGS = -Wall -g -Og -ansi 

all: forkit tryit


tryit: tryit.c
	$(CC) -o $@ $(CFLAGS) tryit.c

forkit: 
	$(CC) -o $@ $(CFLAGS) forkit.c

clean:
	-rm  forkit tryit 

