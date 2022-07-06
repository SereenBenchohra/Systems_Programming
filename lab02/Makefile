CFLAGS = -Wall -ansi -pedantic -g
CC = gcc

uniq: uniq.o
			$(CC) $(CFLAGS) uniq.o

uniq.o: uniq.c
			$(CC) $(CFLAGS) -c uniq.c

clean:
			rm -f uniq.o a.out
