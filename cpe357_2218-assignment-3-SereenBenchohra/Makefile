CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g
MAIN = run_proc
OBJS = run_proc_file.o stat_file_handle.o dir_management.o

all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

run_proc_file.o : run_proc_file.c stat_file_handle.h dir_management.h
	$(CC) $(CFLAGS) -c run_proc_file.c

stat_file_handle.o : stat_file_handle.c stat_file_handle.h
	$(CC) $(CFLAGS) -c stat_file_handle.c

dir_management.o: dir_management.c dir_management.h
	$(CC) $(CFLAGS) -c dir_management.c

clean :
	rm *.o $(MAIN)
