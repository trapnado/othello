SRC = src
OBJ = obj
BIN = bin

CC          = g++
CFLAGS      = -Wall -ansi -pedantic -ggdb
OBJS        = $(OBJ)/player.o $(OBJ)/board.o
PLAYERNAME  = greenEyedMonster0u0



all: $(BIN)/$(PLAYERNAME) testgame

testminimax: objects $(BIN)/testminimax

testgame: $(BIN)/testgame

objects: $(BIN)/board $(BIN)/player 

# Things to put in BIN	
#objects
$(BIN)/$(PLAYERNAME): $(OBJ)/wrapper.o $(OBJS) 
	$(CC) -o $@ $^

$(BIN)/player: $(OBJ)/player.o 
	$(CC) -o $@ $^

$(BIN)/board: $(OBJ)/board.o
	$(CC) -o $@ $^

$(BIN)/testgame: $(OBJ)/testgame.o
	$(CC) -o $@ $^

$(BIN)/testminimax: $(OBJ)/testminimax.o
	$(CC) -o $@ $^

# THings to put in OBJ
$(OBJ)/wrapper.o: $(SRC)/wrapper.cpp
	$(CC) -c $(CFLAGS) -x c++ $< -o $@

$(OBJ)/player.o: $(SRC)/player.cpp
	$(CC) -c $(CFLAGS) -x c++ $< -o $@

$(OBJ)/board.o: $(SRC)/board.cpp
	$(CC) -c $(CFLAGS) -x c++ $< -o $@

$(OBJ)/testgame.o: $(SRC)/testgame.cpp
	$(CC) -c $(CFLAGS) -x c++ $< -o $@

$(OBJ)/testminimax.o: $(SRC)/testminimax.cpp
	$(CC) -c $(CFLAGS) -x c++ $< -o $@

#%.o: %.cpp
#	$(CC) -c $(CFLAGS) -x c++ $< -o $@
	
java:
	make -C java/

cleanjava:
	make -C java/ clean

clean:
	rm -f *(OBJ)/.o $(BIN)/$(PLAYERNAME) $(BIN)/testgame $(BIN)/testminimax
	
.PHONY: java testminimax
