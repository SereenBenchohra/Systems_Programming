CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
MAIN = fs_emulator
OBJS = fs_emulator.o user_commands.o InodeHandle.o

all : $(MAIN)

$(MAIN) : $(OBJS) user_commands.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

fs_emulator.o : fs_emulator.c user_commands.h InodeHandle.h
	$(CC) $(CFLAGS) -c fs_emulator.c

user_commands.o : user_commands.c user_commands.h 
	$(CC) $(CFLAGS) -c user_commands.c

InodeHandle.o: InodeHandle.c InodeHandle.h
	$(CC) $(CFLAGS) -c InodeHandle.c

clean :
	rm *.o $(MAIN) 
