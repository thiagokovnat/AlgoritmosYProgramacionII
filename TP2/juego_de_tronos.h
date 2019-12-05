#ifndef __JUEGO_DE_TRONOS_H__
#define __JUEGO_DE_TRONOS_H__

#include "lista.h"
#include "abb.h"
#include "cola.h"

typedef struct casa{
	char* nombre;
	lista_t* integrantes;
	size_t cantidad_integrantes;
	int factor_nacimiento;
	int factor_envejecimiento;
}casa_t;

typedef struct juego{
	abb_t* arbol;
	cola_t* extinguidos;
	size_t cantidad_casas;
}juego_t;



void menu();
juego_t* inicializar_juego();
void destruir_juego(juego_t*);


#endif