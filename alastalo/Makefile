PROGRAM = muhkuness

CCX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=gnu++11 -O3 -march=native
LIBFLAGS = -lboost_locale

SOURCES = $(wildcard *.cpp)
reassemble: $(SOURCES)
	$(CCX) $(CXXFLAGS) -o $(PROGRAM) $(SOURCES) $(LIBFLAGS)

.PHONY: clean
clean:
	rm -f $(PROGRAM)
