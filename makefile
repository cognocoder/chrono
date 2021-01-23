
# This binary is just for test, so it il not be installed.
binary = cognocoder.chrono.timer

# Default driver.
driver ?= timer
test ?= .tst

headers = time.hpp timer.hpp

# Default: All objects needed to build timer application 
objects = time.o timer.o

# Documentation files.
documentation = README

.PHONY: all build clean run

# Remove transient files.
REMOVE := rm -rf *.gch *.o *.d $(binary) $(documentation).html

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
	@./$(binary)

%.o: %.cpp
	g++ $(FLAGS) -c $< -o $@


# Documentation metadata arguments.
DOCMETA = --metadata title="cognocoder/chrono documentation"

# Documentation build as an HTML file.
$(documentation).html: $(documentation).md
	pandoc $^ -f markdown -t html -s -o $@ $(DOCMETA)

