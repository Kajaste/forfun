PROGRAM = reassemble

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -O3 -march=native

SOURCES = $(wildcard *.c)
reassemble: $(SOURCES)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(SOURCES)

.PHONY: clean
clean:
	rm -f $(PROGRAM)
