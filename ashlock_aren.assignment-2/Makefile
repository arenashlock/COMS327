minesweeper: minesweeper.o
	g++ minesweeper.o -o minesweeper -lncurses

minesweeper.o: minesweeper.cpp
	g++ -Wall -Werror -ggdb minesweeper.cpp -c

#terrain.o: terrain.c terrain.h
#	gcc -Wall -Werror -ggdb terrain.c -c

clean:
	rm -f minesweeper.o minesweeper core *~ *.o