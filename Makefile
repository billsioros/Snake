
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


CELL_DEP = $(addprefix $(PATH_INC)/, types.hpp cell.hpp color3f.hpp) $(PATH_SRC)/cell.cpp

COLOR3F_DEP = $(addprefix $(PATH_INC)/, color3f.hpp) $(PATH_SRC)/color3f.cpp

FOOD_DEP = $(addprefix $(PATH_INC)/, types.hpp color3f.hpp food.hpp) $(PATH_SRC)/food.cpp

GAME_DEP = $(addprefix $(PATH_INC)/, types.hpp cell.hpp game.hpp window.hpp snake.hpp color3f.hpp) $(PATH_SRC)/game.cpp

SNAKE_DEP = $(addprefix $(PATH_INC)/, types.hpp cell.hpp window.hpp snake.hpp color3f.hpp) $(PATH_SRC)/snake.cpp


$(PATH_BIN)/cell.o: $(CELL_DEP)
	$(CC) -I $(PATH_INC) $(DEFINED) $(CCFLAGS) $(PATH_SRC)/cell.cpp -c -o $(PATH_BIN)/cell.o

$(PATH_BIN)/color3f.o: $(COLOR3F_DEP)
	$(CC) -I $(PATH_INC) $(DEFINED) $(CCFLAGS) $(PATH_SRC)/color3f.cpp -c -o $(PATH_BIN)/color3f.o

$(PATH_BIN)/food.o: $(FOOD_DEP)
	$(CC) -I $(PATH_INC) $(DEFINED) $(CCFLAGS) $(PATH_SRC)/food.cpp -c -o $(PATH_BIN)/food.o

$(PATH_BIN)/game.o: $(GAME_DEP)
	$(CC) -I $(PATH_INC) $(DEFINED) $(CCFLAGS) $(PATH_SRC)/game.cpp -c -o $(PATH_BIN)/game.o

$(PATH_BIN)/snake.o: $(SNAKE_DEP)
	$(CC) -I $(PATH_INC) $(DEFINED) $(CCFLAGS) $(PATH_SRC)/snake.cpp -c -o $(PATH_BIN)/snake.o


OBJS = $(addprefix $(PATH_BIN)/,  cell.o color3f.o food.o game.o snake.o)

$(PATH_BIN)/%.exe: $(PATH_TEST)/%.cpp $(OBJS)
	$(CC) -I $(PATH_INC) $(DEFINED) $(CCFLAGS) $< $(OBJS) $(LIBS) -o $@
