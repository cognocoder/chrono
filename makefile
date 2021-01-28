
# This binary is just for test, so it il not be installed.
binary = cognocoder.chrono.timer

# Default driver.
driver ?= timer
test ?= .tst

# Default: All objects needed to build timer application 
objects = time.o timer.o


.PHONY: all build clean run

REMOVE := rm -rf *.gch $(objects) $(binary)

# Flags to enable errors, fatal errors, strict to standard code.
FLAGS  = -Wall -Wextra -Werror -Wfatal-errors -pedantic -pedantic-errors
# Standard C++20, with debug symbols.
FLAGS += -std=c++20 -ggdb

build: clean $(objects)

all: clean $(binary) run
	$(REMOVE)

$(binary): $(driver)$(test).cpp $(objects)
	g++ $(FLAGS) $^ -o $@

clean:
	$(REMOVE)

run: $(binary)
	./$(binary)

%.o: %.cpp
	g++ $(FLAGS) -c $< -o $@

