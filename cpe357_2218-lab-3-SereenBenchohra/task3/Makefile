CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
MAIN = data_conv_tests
OBJS = data_conv_tests.o array_list.o data_conv.o

all : $(MAIN)

$(MAIN) : $(OBJS) array_list.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

data_conv_tests.o : data_conv_tests.c array_list.h 
	$(CC) $(CFLAGS) -c data_conv_tests.c

array_list.o : array_list.c array_list.h 
	$(CC) $(CFLAGS) -c array_list.c

data_conv.o: data_conv.c array_list.h
	$(CC) $(CFLAGS) -c data_conv.c

clean :
	rm *.o $(MAIN) 
