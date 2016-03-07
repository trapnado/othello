CC          = g++
CFLAGS      = -Wall -ansi -pedantic -ggdb
OBJS        = player.o board.o
PLAYERNAME  = greenEyedMonster0u0

SRC = src
OBJ = obj
BIN = bin

<<<<<<< HEAD
=======

>>>>>>> b89df401b5cd58fac7f451640cf5ed38109b067e
all: $(PLAYERNAME) testgame
	
$(PLAYERNAME): $(OBJS) wrapper.o
	$(CC) -o $@ $^

testgame: testgame.o
	$(CC) -o $@ $^

testminimax: $(OBJS) testminimax.o
	$(CC) -o $@ $^

%.o: %.cpp
	$(CC) -c $(CFLAGS) -x c++ $< -o $@
	
java:
	make -C java/

cleanjava:
	make -C java/ clean

clean:
	rm -f *.o $(PLAYERNAME) testgame testminimax
	
.PHONY: java testminimax
