CC = gcc
CFLAGS = -g -Wall -Werror
DEPS = io/File.h disk/Dish.h
OBJ = io/File.o disk/Disk.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: test01 test02

test01: apps/test01.c io/File.h disk/Disk.h
	$(CC) -o test01 apps/test01.c $(CFLAGS)

test02: apps/test02.c io/File.h disk/Disk.h
	$(CC) -o test02 apps/test02.c $(CFLAGS)

clean:
	$(RM) all