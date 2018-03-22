
CC     = g++
CFLAGS = -W -o3 -g3

PATH_SRC = ./src/
PATH_BIN = ./bin/

MAIN_DEP = $(addprefix $(PATH_SRC), Game.h main.cpp)
GNRL_DEP = $(addprefix $(PATH_SRC), general.h general.cpp)
VCTR_DEP = $(addprefix $(PATH_SRC), general.h Vector2D.h Vector2D.cpp)
GAME_DEP = $(addprefix $(PATH_SRC), general.h Game.h Game.cpp)
OBJS     = $(addprefix $(PATH_BIN), main.o general.o Vector2D.o Game.o)

$(PATH_BIN)snake : $(OBJS)
	@echo Compiling executable file 'snake'
	$(CC) $(CFLAGS) $(OBJS) -o $(PATH_BIN)snake

$(PATH_BIN)main.o : $(MAIN_DEP)
	@echo Compiling object file 'main.o'
	$(CC) $(CFLAGS) $(PATH_SRC)main.cpp -c -o $(PATH_BIN)main.o

$(PATH_BIN)general.o : $(GNRL_DEP)
	@echo Compiling object file 'general.o'
	$(CC) $(CFLAGS) $(PATH_SRC)general.cpp -c -o $(PATH_BIN)general.o

$(PATH_BIN)Vector2D.o : $(VCTR_DEP)
	@echo Compiling object file 'Vector2D.o'
	$(CC) $(CFLAGS) $(PATH_SRC)Vector2D.cpp -c -o $(PATH_BIN)Vector2D.o

$(PATH_BIN)Game.o : $(VCTR_DEP)
	@echo Compiling object file 'Game.o'
	$(CC) $(CFLAGS) $(PATH_SRC)Game.cpp -c -o $(PATH_BIN)Game.o

.PHONY clean:
	rm -i $(PATH_BIN)*