
BINARY = cognocoder.timer

# Flags to enable errors, fatal errors, strict to standard code.
FLAGS  = -Wall -Wextra -Werror -Wfatal-errors -pedantic -pedantic-errors
# Standard C++20, with debug symbols.
FLAGS += -std=c++20 -ggdb 

# Default driver.
driver ?= timer
test ?= .tst

headers = time.hpp timer.hpp

.PHONY: all clean run

# Remove transient files.
REMOVE := rm -rf *.gch *.o *.d $(BINARY)

all: clean $(BINARY) run
	$(REMOVE)
	@echo

# Default: All objects needed to build timer application 
objects = time.o timer.o

# Build timer application or a test driver.
ifneq ($(driver), timer)
	objects = $(driver).o
endif

$(BINARY): $(driver)$(test).cpp $(objects)
	g++ $(FLAGS) $^ -o $@

clean:
	@echo
	$(REMOVE)
	@echo

run: $(BINARY)
	@echo
	@./$(BINARY)
	@echo

%.o: %.cpp
	g++ $(FLAGS) -c $< -o $@


# Installation base directory.
DIR = /usr/local

HEADERS_DIR = /include
OBJECTS_DIR = /lib

# Installation namespace directory.
NAMESPACE = /cognocoder

install: $(headers) $(objects)
	@mkdir -p $(DIR)$(HEADERS_DIR)$(NAMESPACE)
	@mkdir -p $(DIR)$(OBJECTS_DIR)$(NAMESPACE)
	@for header in $(headers); do \
		cp $$header $(DIR)$(HEADERS_DIR)$(NAMESPACE); \
	done
	@for object in $(objects); do \
		cp $$object $(DIR)$(OBJECTS_DIR)$(NAMESPACE); \
	done

uninstall:
	@for header in $(headers); do \
		rm -rf $(DIR)$(HEADERS_DIR)$(NAMESPACE)/$$header; \
	done
	@for object in $(objects); do \
		rm -rf $(DIR)$(OBJECTS_DIR)$(NAMESPACE)/$$object; \
	done

uninstall-cognocoder:
	@rm -rf $(DIR)$(HEADERS_DIR)$(NAMESPACE)
	@rm -rf $(DIR)$(OBJECTS_DIR)$(NAMESPACE)

