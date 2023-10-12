poke327: ashlock_aren.assignment-1.03.o terrain.o heap.o player.o
	gcc ashlock_aren.assignment-1.03.o terrain.o heap.o player.o -o poke327

ashlock_aren.assignment-1.03.o: ashlock_aren.assignment-1.03.c terrain.h heap.h
	gcc -Wall -Werror -ggdb ashlock_aren.assignment-1.03.c -c

terrain.o: terrain.c terrain.h
	gcc -Wall -Werror -ggdb terrain.c -c

heap.o: heap.c heap.h
	gcc -Wall -Werror -ggdb heap.c -c

player.o: player.c player.h terrain.h
	gcc -Wall -Werror -ggdb player.c -c

clean:
	rm -f ashlock_aren.assignment-1.03.o terrain.o heap.o player.o poke327 core *~ *.o