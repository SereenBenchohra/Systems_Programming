CC = gcc
CFLAGS = -Wall -pedantic -std=c99
ORIG = original
COMMONOBJS = main.o util.o
ORIGOBJS = original.o $(COMMONOBJS)
BEST = best
BESTOBJS = best.o $(COMMONOBJS)
WORST = worst
WORSTOBJS = worst.o $(COMMONOBJS)

all : $(ORIG) $(BEST) $(WORST)

$(ORIG) : $(ORIGOBJS)
	$(CC) $(CFLAGS) -o $(ORIG) $(ORIGOBJS)

$(BEST) : $(BESTOBJS)
	$(CC) $(CFLAGS) -o $(BEST) $(BESTOBJS)

$(WORST) : $(WORSTOBJS)
	$(CC) $(CFLAGS) -o $(WORST) $(WORSTOBJS)

original.o : original.c mem.h
	$(CC) $(CFLAGS) -c original.c

best.o : best.c mem.h
	$(CC) $(CFLAGS) -c best.c

worst.o : worst.c mem.h
	$(CC) $(CFLAGS) -c worst.c

main.o : main.c mem.h util.h
	$(CC) $(CFLAGS) -c main.c

util.o : util.c util.h mem.h
	$(CC) $(CFLAGS) -c util.c

clean :
	rm *.o $(ORIG) $(BEST) $(WORST) core*
