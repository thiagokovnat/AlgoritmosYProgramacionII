CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wconversion -pedantic -Wtype-limits 


compile:  test.c lista.c pruebas.c
	$(CC) $(CFLAGS)  -g test.c pruebas.c lista.c -o prueba_vd

test: compile
	./prueba_vd

valgrind: compile
	valgrind --leak-check=full  --track-origins=yes --show-reachable=yes ./prueba_vd
