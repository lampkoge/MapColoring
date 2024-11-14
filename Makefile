# Makefile for Map Coloring Project

# Compiler settings
CC = gcc
CFLAGS = -Wall -std=c11 -pedantic

# Target executable name
TARGET = mapcol

# Object files
OBJS = main.o map.o country.o color.o

# Default rule to build the executable
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

CC = gcc
CFLAGS = -Wall -std=c11 -pedantic
TARGET = mapcol

all: $(TARGET)

$(TARGET): main.o map.o country.o color.o
	$(CC) $(CFLAGS) main.o map.o country.o color.o -o $(TARGET)

main.o: main.c map.h country.h color.h
	$(CC) $(CFLAGS) -c main.c

map.o: map.c map.h country.h color.h
	$(CC) $(CFLAGS) -c map.c

country.o: country.c country.h color.h
	$(CC) $(CFLAGS) -c country.c

color.o: color.c color.h
	$(CC) $(CFLAGS) -c color.c

clean:
	rm -f *.o $(TARGET)
