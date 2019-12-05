CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wconversion -pedantic -Wtype-limits 


compile:  cola.c test.c pruebas.c
	$(CC) $(CFLAGS) -g cola.c test.c pruebas.c -o cola_vd

test: compile
	./cola_vd

valgrind: compile
	valgrind --leak-check=full  --track-origins=yes --show-reachable=yes ./cola_vd
