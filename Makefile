CC = gcc
CFLAGS = -o -Wall -Werror kapish kapish.c 
TARGET=kapish

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)