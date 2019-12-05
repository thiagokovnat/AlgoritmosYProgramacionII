CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wconversion

compile: main1.c cuervo.c
	$(CC) $(CFLAGS) main1.c cuervo.c -o cuervo_de_tres_ojos

run: compile
	./cuervo_de_tres_ojos

valgrind: compile
	valgrind --leak-check=full  --track-origins=yes --show-reachable=yes ./cuervo_de_tres_ojos