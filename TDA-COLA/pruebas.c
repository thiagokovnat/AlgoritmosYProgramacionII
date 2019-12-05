#include "pruebas.h"
#include <stdio.h>
#include "cola.h"
#include <stdbool.h>
#include <stdlib.h>
#define ERROR -1
#define EXITO 0

// pre: -
// pos: imprime por pantalla si paso la prueba dependiendo de la condicion booleana
void assert_prueba(char* mensaje, bool condicion){

	if(condicion)
		printf("#OK, %s \n\n", mensaje);
	else
		printf("FALLO\n\n");
}

// ----------------------------------------PRUEBAS SOBRE COLAS VACIAS/NULAS---------------------------------------------------

// pre:
// pod: imprime por pantalla si paso la prueba o si fallo
void siDesencoloUnaColaVaciaDeberiaDevolverError(){

	printf("\nInicializando Prueba (Desencolar Cola Vacia Deberia Devolver Error)...\n");
	cola_t* cola = cola_crear();

	assert_prueba("devuelve error", cola_desencolar(cola) == ERROR);
	cola_destruir(cola);
}

// pre:
// pod: imprime por pantalla si paso la prueba o si fallo
void siDesencoloUnaColaNulaDeberiaDevolverError(){

	printf("Inicializando Prueba (Desencolar Cola Nula Deberia Devolver Error)...\n");
	cola_t* cola = NULL;

	assert_prueba("devuelve error", cola_desencolar(cola) == ERROR);
}

// pre:
// pod: imprime por pantalla si paso la prueba o si fallo
void siEncoloEnUnaPilaNulaDeberiaDevolverError(){

	printf("Inicializando Prueba (Encolar Cola Nula Deberia Devolver Error)...\n");
	cola_t* cola = NULL;
	int elemento = 1;

	assert_prueba("devuelve error",cola_encolar(cola, &elemento) == ERROR);
}

// pre:
// pod: imprime por pantalla si paso la prueba o si fallo
void siIntentoVerPrimeroDeColaVaciaDeberiaDevolverNULL(){

	printf("Inicializando Prueba (Ver Primero en cola nula deberia devolver NULL)...\n");
	cola_t* cola = NULL;

	assert_prueba("devuelve NULL",!cola_primero(cola));
}

//-------------------------------------------PRUEBAS SOBRE COLAS CON ELEMENTOS------------------------------------------------

// pre:
// pod: imprime por pantalla si paso la prueba o si fallo
void siEncoloYDesencoloLaMismaCantidadDeElementosColaVaciaDeberiaDevolverTrue(){

	printf("Inicializando Prueba (Encolar y Desencolar misma cantidad de elementos deberia vaciar la cola)...\n");
	cola_t* cola = cola_crear();
	int elemento = 1;

	for (int i = 0; i < 500; ++i)
		cola_encolar(cola, &elemento);
	

	for (int i = 0; i < 500; ++i)
		cola_desencolar(cola);
	
	assert_prueba("vacia la pila", cola_vacia(cola));
	cola_destruir(cola);
}

// pre:
// pod: imprime por pantalla si paso la prueba o si fallo
void siEncoloYDesencoloElementosDeberiaDevolverlosEnMismoOrden(){

	printf("Inicializando Prueba (Encolar y desencolar elementos deberia devolverlos en el mismo orden)...\n");
	cola_t* cola = cola_crear();

	int elem[5] = {1,2,3,4,5};
	int coincidencias = 0;

	for (int i = 0; i < 5; ++i)
		cola_encolar(cola, &elem[i]);
	

	for (int i = 0; i < 5; ++i){

		if(*(int*)cola_primero(cola) == elem[i])
			coincidencias++;
		cola_desencolar(cola);
	}

	assert_prueba("los devuelve en mismo orden", coincidencias == 5);
	cola_destruir(cola);
}

// pre:
// pod: imprime por pantalla si paso la prueba o si fallo
void siEncoloUnElementoNuloDeberiaEncolarCorrectamente(){

	printf("Inicializando Prueba (Encolar un elemento NULL deberia encolar correctamente)...\n");
	cola_t* cola = cola_crear();
	int* elem = NULL;

	assert_prueba("encola correctamente",(cola_encolar(cola, elem) == EXITO) && (cola_primero(cola) == NULL));
	cola_destruir(cola);
}

