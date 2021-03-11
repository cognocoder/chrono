
BINARY = cognocoder.chrono.timer

# Flags to enable errors, fatal errors, strict to standard code.
FLAGS  = -Wall -Wextra -Werror -Wfatal-errors -pedantic -pedantic-errors
# Standard C++20, with debug symbols.
FLAGS += -std=c++20 -ggdb

# Default driver.
driver ?= timer
test ?= .tst

# Default: All objects needed to build timer application 
objects = time.o timer.o

.PHONY: all clean run

REMOVE := rm -rf *.gch $(objects) $(BINARY)

run: $(BINARY)
	@./$(BINARY)

$(BINARY): $(driver)$(test).cpp $(objects)
	@g++ $(FLAGS) $^ -o $@

all: clean $(BINARY) run

clean:
	@$(REMOVE)

%.o: %.cpp
	@g++ $(FLAGS) -c $< -o $@

