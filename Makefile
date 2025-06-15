CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
TARGET = gpio_simulator

# Source files
SRCS = src/main.c src/gpio.c src/cli.c src/persistence.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule for object files
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean