CC = gcc
FLAGS = -Wall -pedantic -g


all: createArchive.o nicoFuncts.o mytar.o clreader.o tableArchive.o \
extractArchive.o
	make mytar

mytar: createArchive.o nicoFuncts.o mytar.o clreader.o tableArchive.o \
extractArchive.o
	$(CC) -o mytar createArchive.o nicoFuncts.o mytar.o clreader.o \
tableArchive.o  extractArchive.o $(FLAGS)

extractArchive.o: extractArchive.c
	$(CC) extractArchive.c -c $(FLAGS)

createArchive.o: createArchive.c
	$(CC) createArchive.c -c $(FLAGS)

nicoFuncts.o: nicoFuncts.c
	$(CC) nicoFuncts.c -c $(FLAGS)

tableArchive.o: tableArchive.c
	$(CC) tableArchive.c -c $(FLAGS)

clreader.o: clreader.c
	$(CC) clreader.c -c $(FLAGS)

mytar.o: mytar.c
	$(CC) mytar.c -c $(FLAGS)

clean:
		rm -f *.o

