CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
MAIN = array_list_tests
OBJS = array_list_tests.o array_list.o

all : $(MAIN)

$(MAIN) : $(OBJS) array_list.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

array_list_tests.o : array_list_tests.c array_list.h
	$(CC) $(CFLAGS) -c array_list_tests.c

array_list.o : array_list.c array_list.h
	$(CC) $(CFLAGS) -c array_list.c

clean :
	rm *.o $(MAIN) core
