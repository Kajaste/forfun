PROGRAM = muhkuness

CCX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=gnu++11 -O3 -march=native

SOURCES = $(wildcard *.cpp)
all: $(SOURCES)
	$(CCX) $(CXXFLAGS) $(DEBUGFLAGS) -o $(PROGRAM) $(SOURCES)

.PHONY: clean
clean:
	rm -f $(PROGRAM)
