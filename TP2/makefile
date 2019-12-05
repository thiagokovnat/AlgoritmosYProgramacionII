CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wconversion -pedantic -Wtype-limits 


compile:  juego_de_tronos.c abb.c lista.c cola.c main.c
	$(CC) $(CFLAGS) -g juego_de_tronos.c cola.c abb.c main.c lista.c -o prueba_vd

test: compile
	./prueba_vd

valgrind: compile
	valgrind --leak-check=full  --track-origins=yes --show-reachable=yes ./prueba_vd
