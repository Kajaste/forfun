CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -O3 -march=native

PROGRAM = reassemble
SOURCES = reassemble.c

reassemble: $(SOURCES)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(SOURCES)

.PHONY: clean
clean:
	rm -f $(PROGRAM)
