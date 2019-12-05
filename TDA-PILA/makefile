CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wconversion -pedantic -Wtype-limits 


compile:  test.c pruebas.c pila.c
	$(CC) $(CFLAGS) -g test.c pila.c pruebas.c -o prueba_vd

test: compile
	./prueba_vd

valgrind: compile
	valgrind --leak-check=full  --track-origins=yes --show-reachable=yes ./prueba_vd
