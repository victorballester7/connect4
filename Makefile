# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

CC = gcc                       					 # compiler to use
CC_FLAGS = -Wall -pedantic -std=c99	-ggdb # flags

# location of binary files
BIN := bin
# location of .c files
SRC := src
# location of header files
INCLUDE := include

LIBRARIES := -lm -lncurses
EXECUTABLE := main 

# Rules are of the form:
# target: prerequisites
# 	 recipe

# This defines all the targets that are not files.
.PHONY: all run clean 

# default target to be executed is the first encountered. To change it, uncomment the following line and replace all with another target.
# .DEFAULT_GOAL := all
all: $(BIN)/$(EXECUTABLE) 

# call it with 'make run' because it is not the default one.
run: clean all
	@./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(filter-out $(SRC)/evaluation.c $(SRC)/main2.c, $(wildcard $(SRC)/*.c))
	@$(CC) $(CC_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	@-rm $(BIN)/*