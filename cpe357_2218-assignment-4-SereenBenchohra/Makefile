CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
MAIN = run_curl
OBJS = curl.o fileHandle.o processHandle.o split.o

all : $(MAIN)

$(MAIN) : $(OBJS) fileHandle.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

curl.o : curl.c fileHandle.h processHandle.h split.h
	$(CC) $(CFLAGS) -c curl.c

fileHandle.o : fileHandle.c fileHandle.h split.h
	$(CC) $(CFLAGS) -c fileHandle.c

split.o: split.c split.h
	$(CC) $(CFLAGS) -c split.c

processHandle.o: processHandle.c processHandle.h
	$(CC) $(CFLAGS) -c processHandle.c

clean :
	rm *.o $(MAIN)
