poke327: ashlock_aren.assignment-1.02.o terrain.o
	gcc ashlock_aren.assignment-1.02.o terrain.o -o poke327

ashlock_aren.assignment-1.02.o: ashlock_aren.assignment-1.02.c terrain.h
	gcc -Wall -Werror -ggdb ashlock_aren.assignment-1.02.c -c

terrain.o: terrain.c terrain.h
	gcc -Wall -Werror -ggdb terrain.c -c

clean:
	rm -f ashlock_aren.assignment-1.02.o terrain.o poke327 core *~ *.o