CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
MAIN = split_tests
OBJS = split_tests.o array_list.o split.o

all : $(MAIN)

$(MAIN) : $(OBJS) array_list.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

split_tests.o : split_tests.c array_list.h 
	$(CC) $(CFLAGS) -c split_tests.c

array_list.o : array_list.c array_list.h 
	$(CC) $(CFLAGS) -c array_list.c

split.o: split.c array_list.h
	$(CC) $(CFLAGS) -c split.c

clean :
	rm *.o $(MAIN) 
