CC      = gcc
CCFLAGS = -std=c89 -pedantic -Wall -Werror -D NDEBUG
LDFLAGS = -lm 
PARENT_SOURCES  = pipeline.c launcher.c
PARENT_OBJECTS  = pipeline.o launcher.o
PARENT_INCLUDES = launcher.h
CHILD_SOURCES   = randomChild.c
CHILD_OBJECTS   = randomChild.o
CHILD_INCLUDE   =

all: pipeline randomChild

pipeline:$(PARENT_OBJECTS) 
	$(CC) -o a.out $(CCFLAGS) $(LDFLAGS) $(PARENT_OBJECTS)

$(PARENT_OBJECTS):$(PARENT_SOURCES) $(PARENT_INCLUDES)
	$(CC) -c $(CCFLAGS) $(PARENT_SOURCES)

randomChild:$(CHILD_OBJECTS) 
	$(CC) -o randomChild $(CCFLAGS) $(LDFLAGS) $(CHILD_OBJECTS)

$(CHILD_OBJECTS):$(CHILD_SOURCES) $(CHILD_INCLUDES)
	$(CC) -c $(CCFLAGS) $(CHILD_SOURCES)

clean:
	rm -f a.out randomChild $(PARENT_OBJECTS) $(CHILD_OBJECTS) 
