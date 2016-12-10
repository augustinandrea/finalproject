# Makefile for the Scrabble Game
# play.cpp is the main program

# GFLAGS=-g -c -std=c++11 -DDEBUG
GFLAGS=-g -c -std=c++11

scrabble: scrabble.o polygon.o play.o dictionary.o gfx.o
	g++ scrabble.o polygon.o play.o dictionary.o gfx.o -lX11 -o scrabble

scrabble.o: scrabble.cpp scrabble.h
	g++ ${GFLAGS} scrabble.cpp -o scrabble.o

polygon.o: polygon.cpp polygon.h
	g++ ${GFLAGS} polygon.cpp -o polygon.o

play.o: play.cpp scrabble.h gfx.h
	g++ ${GFLAGS} play.cpp -o play.o

dictionary.o: dictionary.cpp dictionary.h
	g++ ${GFLAGS} dictionary.cpp -o dictionary.o

clean:
	rm -f *~ scrabble scrabble.o polygon.o play.o dictionary.o

commit:
	git commit -m "Update" *.h *.cpp Makefile

pull:
	-make commit
	git pull https://github.com/augustinandrea/finalproject

push:
	make pull
	git push
