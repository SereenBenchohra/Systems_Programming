SHELL = /bin/sh
CC == gcc 

CFLAGS = -Wall -g -I ~pn-cs357/Given/Mush/include

LDFLAGS = -Wall -g -L ~pn-cs357/Given/Mush/lib64 -lmush


mush2: mush2.o
	$(CC) $(LDFLAGS) -o mush2.o -lmush

mush2.o: mush2.c
	$(CC) $(CFLAGS) -c mush2.c

all: mush2.c

clean:
	rm *.o