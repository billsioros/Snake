
CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -g3

LIBS = -lGL -lGLU -lglut

PATH_SRC = ./src
PATH_INC = ./include
PATH_BIN = ./bin
PATH_TEST = ./test

.PHONY: all
all:
	mkdir -p $(PATH_BIN)
	@echo
	@echo "*** Compiling object files ***"
	@echo "***"
	make $(OBJS)
	@echo "***"

.PHONY: clean
clean:
	@echo
	@echo "*** Purging binaries ***"
	@echo "***"
	rm -rvf $(PATH_BIN)
	@echo "***"


CELL_DEP = $(addprefix $(PATH_INC)/, game.hpp cell.hpp) $(PATH_SRC)/cell.cpp

SNAKE_DEP = $(addprefix $(PATH_INC)/, game.hpp cell.hpp snake.hpp) $(PATH_SRC)/snake.cpp


$(PATH_BIN)/cell.o: $(CELL_DEP)
	$(CC) -I $(PATH_INC) $(DEFINED) $(CCFLAGS) $(PATH_SRC)/cell.cpp -c -o $(PATH_BIN)/cell.o

$(PATH_BIN)/snake.o: $(SNAKE_DEP)
	$(CC) -I $(PATH_INC) $(DEFINED) $(CCFLAGS) $(PATH_SRC)/snake.cpp -c -o $(PATH_BIN)/snake.o


OBJS = $(addprefix $(PATH_BIN)/,  cell.o snake.o)

$(PATH_BIN)/%.exe: $(PATH_TEST)/%.cpp $(OBJS)
	$(CC) -I $(PATH_INC) $(DEFINED) $(CCFLAGS) $< $(OBJS) $(LIBS) -o $@
