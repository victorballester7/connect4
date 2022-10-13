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

LIBRARIES := -lm -lcurses
EXECUTABLE := connect4 
PROVA := prova 
EVALUATION := evaluation

# Rules are of the form:
# target: prerequisites
# 	 recipe

# This defines all the targets that are not files.
.PHONY: all prova evaluation run run_prova run_evaluation clean 

# default target to be executed is the first encountered. To change it, uncomment the following line and replace all with another target.
# .DEFAULT_GOAL := all
all: $(BIN)/$(EXECUTABLE) 

prova: $(BIN)/$(PROVA)

evaluation: $(BIN)/$(EVALUATION)

# call it with 'make run' because it is not the default one.
run: clean all
	@./$(BIN)/$(EXECUTABLE)

run_prova: clean prova
	@./$(BIN)/$(PROVA)

run_evaluation: clean evaluation
	@./$(BIN)/$(EVALUATION)

$(BIN)/$(EXECUTABLE): $(SRC)/connect4.c $(SRC)/minimax.c
	@$(CC) $(CC_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

$(BIN)/$(PROVA): $(SRC)/prova.c
	@$(CC) $(CC_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

$(BIN)/$(EVALUATION): $(SRC)/evaluation.c
	clear
	@$(CC) $(CC_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	@-rm $(BIN)/*