
# This binary is just for test, so it il not be installed.
binary = cognocoder.chrono.timer

# Default driver.
driver ?= timer
test ?= .tst

headers = time.hpp timer.hpp
library = libcognocoder.chrono

# Default: All objects needed to build timer application 
objects = time.o timer.o


.PHONY: all clean run install uninstall uninstall-cognocoder

# Remove transient files.
REMOVE := rm -rf *.gch *.o *.d $(binary) $(library).a

all: clean $(binary) run
	$(REMOVE)
	@echo

# Flags to enable errors, fatal errors, strict to standard code.
FLAGS  = -Wall -Wextra -Werror -Wfatal-errors -pedantic -pedantic-errors
# Standard C++20, with debug symbols.
FLAGS += -std=c++20 -ggdb 

$(binary): $(driver)$(test).cpp $(objects)
	g++ $(FLAGS) $^ -o $@

clean:
	@echo
	$(REMOVE)
	@echo

run: $(binary)
	@echo
	@./$(binary)
	@echo

%.o: %.cpp
	g++ $(FLAGS) -c $< -o $@


# Installation base directory.
DIR = /usr/local

HEADERS_DIR = /include
OBJECTS_DIR = /lib

# Installation namespace directory.
NAMESPACE = /cognocoder/chrono

$(library).a: $(objects)
	@ar -cq  $(library).a $(objects)

install: $(headers) $(library).a
	mkdir -p $(DIR)$(HEADERS_DIR)$(NAMESPACE)
	mkdir -p $(DIR)$(OBJECTS_DIR)$(NAMESPACE)
	cp $(headers) $(DIR)$(HEADERS_DIR)$(NAMESPACE)
	cp $(library).a $(DIR)$(OBJECTS_DIR)$(NAMESPACE)/$(library).a

uninstall:
	rm $(DIR)$(HEADERS_DIR)$(NAMESPACE)/*.hpp
	rm $(DIR)$(OBJECTS_DIR)$(NAMESPACE)/*.a
	rm $(DIR)$(OBJECTS_DIR)$(NAMESPACE)/*.o

uninstall-cognocoder:
	rm -rf $(DIR)$(HEADERS_DIR)$(NAMESPACE)
	rm -rf $(DIR)$(OBJECTS_DIR)$(NAMESPACE)

