#include "cola.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIN_ELEMENTOS 0
#define EXITO 0
#define ERROR -1

// PRECONDICIONES:
// POSTCONDICIONES: IMPLEMENTA LAS PRIMITIVAS DE LA COLA, QUE PERMITEN INTERACTUAR CON ELLA PARA SU USO.

/* 
 * Crea una cola reservando la memoria necesaria
 * para almacenar la estructura.
 * Devuelve un puntero a la estructura cola_t creada.
 */
cola_t* cola_crear(){

	cola_t* cola = malloc(sizeof(cola_t));

	if(!cola)
		return NULL;

	cola->nodo_inicio = NULL;
	cola->nodo_fin = NULL;
	cola->cantidad = SIN_ELEMENTOS;

	return cola;
}

// pre:
// pos: crea un nuevo nodo y encola el elemento en el. Establece el nodo siguiente como NULL. Devuelve NULL si hubo error.
nodo_t* encolar_en_nuevo_nodo(void* elemento){

	nodo_t* aux = malloc(sizeof(nodo_t));
	if(!aux)
		return NULL;

	aux->elemento = elemento;
	aux->siguiente = NULL;

	return aux;
}

/* 
 * Encola un elemento.
 * Devuelve 0 si pudo encolar o -1 si no pudo.
 */
int cola_encolar(cola_t* cola, void* elemento){

	if(!cola)
		return ERROR;

	nodo_t* nuevo_nodo = encolar_en_nuevo_nodo(elemento);
		if(!nuevo_nodo)
			return ERROR;

	if(cola_vacia(cola))	
		cola->nodo_inicio = nuevo_nodo;
	else
		cola->nodo_fin->siguiente = nuevo_nodo;
			
	cola->nodo_fin = nuevo_nodo;
	cola->cantidad++;

	return EXITO;
}

/* 
 * Desencola un elemento.
 * Devuelve 0 si pudo desencolar o -1 si no pudo.
 */
int cola_desencolar(cola_t* cola){

	if(!cola || cola_vacia(cola))
		return ERROR;

	nodo_t* nodo_aux = cola->nodo_inicio->siguiente;
	free(cola->nodo_inicio);
	
	if(!nodo_aux){
		cola->nodo_inicio = NULL;
		cola->nodo_fin = NULL;
	}
	else
		cola->nodo_inicio = nodo_aux;
		
	cola->cantidad--;
	return EXITO;
}

/* 
 * Determina si la cola está vacia.
 * Devuelve true si está vacía y false si no.
 * Si la cola no existe devolverá true.
 */
bool cola_vacia(cola_t* cola){

	if(!cola)
		return true;
	else
		return (cola->cantidad == SIN_ELEMENTOS);
}

/* 
 * Devuelve la cantidad de elementos almacenados en la cola.
 * Si la cola no existe devolverá 0.
 */
int cola_cantidad(cola_t* cola){

	if(!cola)
		return SIN_ELEMENTOS;
	else
		return cola->cantidad;
}

/*
 * Devuelve el primer elemento de la cola o NULL en caso de estar
 * vacía.
 * Si la cola no existe devolverá NULL.
 */
void* cola_primero(cola_t* cola){

	if(!cola || cola_vacia(cola))
		return NULL;
	else
		return cola->nodo_inicio->elemento;
}

// pre: 
// pos: desencola todos los elementos de la cola.
void vaciar_cola(cola_t* cola){

	if(!cola)
		return;

	while(!cola_vacia(cola))
		cola_desencolar(cola);
}

/* 
 * Destruye la cola liberando toda la memoria reservada
 * por la cola.
 */
void cola_destruir(cola_t* cola){

	if(!cola)
		return;

	if(!cola_vacia(cola))
		vaciar_cola(cola);
	
	free(cola);
}

