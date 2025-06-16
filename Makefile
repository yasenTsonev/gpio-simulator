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

# Test target
test: tests/test_gpio
	./tests/test_gpio

tests/test_gpio: tests/test_gpio.c src/gpio.o
	$(CC) $(CFLAGS) -o $@ $^

clean-test:
	rm -f tests/test_gpio

.PHONY: test clean-test