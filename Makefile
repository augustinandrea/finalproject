# Makefile for the Game of Life

GFLAGS=-g -c -std=c++11 -DDEBUG

polybounce: polybounce.o polygon.o
	g++ polybounce.o polygon.o gfx.o -lX11 -o polybounce

polygon.o: polygon.cpp polygon.h
	g++ ${GFLAGS} polygon.cpp -o polygon.o

polybounce.o: polybounce.cpp
	g++ ${GFLAGS} polybounce.cpp -o polybounce.o

clean:
	rm -f *.o *~ crossword

commit:
	git commit -m "Update" *.h *.cpp Makefile

pull:
	-make commit
	git pull

push:
	make pull
	git push
