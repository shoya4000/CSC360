CC = gcc
CFLAGS = -g -Wall -Werror -Iio -Idisk
DEPS = io/File.h disk/Dish.h
OBJ = io/File.o disk/Disk.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: test01 test02

test01: apps/test01.o $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test02: apps/test02.o $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) all