# Makefile for the Scrabble Game
# play.cpp is the main program

# GFLAGS=-g -c -std=c++11 -DDEBUG
GFLAGS=-g -c -std=c++11
INCS=dictionary.h gfxnew.h polygon.h scrabble.h letter.h button.h

scrabble: scrabble.o polygon.o play.o dictionary.o gfxnew.o letter.o button.o
	g++ scrabble.o polygon.o play.o dictionary.o gfxnew.o button.o -lX11 -o scrabble

scrabble.o: scrabble.cpp ${INCS}
	g++ ${GFLAGS} scrabble.cpp -o scrabble.o

polygon.o: polygon.cpp ${INCS}
	g++ ${GFLAGS} polygon.cpp -o polygon.o

play.o: play.cpp ${INCS}
	g++ ${GFLAGS} play.cpp -o play.o

dictionary.o: dictionary.cpp ${INCS}
	g++ ${GFLAGS} dictionary.cpp -o dictionary.o

button.o: button.cpp ${INCS}
	g++ ${GFLAGS} button.cpp -o button.o

letter.o: letter.cpp ${INCS}
	g++ ${GFLAGS} letter.cpp -o letter.o

clean:
	rm -f *~ scrabble scrabble.o polygon.o play.o dictionary.o button.o

commit:
	git commit -m "Update" *.h *.cpp Makefile

pull:
	-make commit
	git pull https://github.com/augustinandrea/finalproject

push:
	make pull
	git push
