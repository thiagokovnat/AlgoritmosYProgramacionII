CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wconversion -pedantic -Wtype-limits 


compile: abb.c pruebas.c test.c
	$(CC)  -g abb.c test.c pruebas.c -o prueba_vd

test: compile
	./prueba_vd

valgrind: compile
	valgrind --leak-check=full  --track-origins=yes --show-reachable=yes ./prueba_vd
