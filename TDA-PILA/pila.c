#include "pila.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIN_ELEMENTOS 0
#define TAMANIO_INICIAL 5
#define ERROR -1
#define CONSTANTE_REDIMENSIONAR 2
#define EXITO 0
#define MIN_CANTIDAD_REDIMENSIONAR 10


/* 
 * Crea una pila, reservando la memoria necesearia para almacenar la
 * estructura.
 * Devuelve un puntero a la estructura pila_t creada o NULL si no pudo
 * crearla.
 */
pila_t* pila_crear(){

	pila_t* pila = malloc(sizeof(pila_t));

	if(pila != NULL){
		
		pila->tope = SIN_ELEMENTOS;
		pila->tamanio = TAMANIO_INICIAL;
		pila->elementos = malloc((long unsigned int)(pila->tamanio) * sizeof(void*));
		
		if(!pila->elementos){
			free(pila);
			return NULL;
		}
	}

	return pila;
}

// pre: cantidad es un numero positivo.
// pos: redimensiona el vector de elementos a la cantidad especificada.
int redimensionar_pila(void*** elementos, int cantidad, int* tamanio){

	void* aux = realloc((*elementos), (long unsigned int) cantidad * sizeof(void*));
	if(!aux)
		return ERROR;

	(*elementos) = aux;
	(*tamanio) = cantidad;
	return EXITO;
}

// pre: 
// pos: devuelve TRUE si la pila deberia achicarse, FALSE en caso contrario.
bool pila_deberia_achicarse(pila_t* pila){

	if(!pila)
		return false;

	return(((pila->tamanio/CONSTANTE_REDIMENSIONAR) >= pila->tope) && (pila->tamanio >= MIN_CANTIDAD_REDIMENSIONAR));
}

// pre: 
// pos: devuelve TRUE si la pila deberia agrandarse, FALSE en caso contrario.
bool pila_deberia_agrandarse(pila_t* pila){

	if(!pila)
		return false;

	return (((pila->tamanio) == pila->tope));
}

/* 
 * Apila un elemento.
 * Devuelve 0 si pudo o -1 en caso contrario.
 */
int pila_apilar(pila_t* pila, void* elemento){

	if(!pila)
		return ERROR;

    if(pila_deberia_agrandarse(pila)){
		int retorno = redimensionar_pila(&pila->elementos, CONSTANTE_REDIMENSIONAR * pila->tamanio, &pila->tamanio);
		if(retorno == ERROR)
			return ERROR;
	}

	pila->elementos[pila->tope] = elemento;
	(pila->tope)++;
    
     
	
	return EXITO;
}

/* 
 * Desapila un elemento.
 * Devuelve 0 si pudo desapilar o 1 si no pudo.
 */
int pila_desapilar(pila_t* pila){
	
	if( (!pila) || (pila_vacia(pila)) )
		return ERROR;

	
    if(pila_deberia_achicarse(pila)){
		int retorno = redimensionar_pila(&pila->elementos, (pila->tamanio/CONSTANTE_REDIMENSIONAR), &pila->tamanio);
		if(retorno == ERROR)
			return ERROR;
	}

	(pila->tope)--;

	
	return EXITO;
}

/* 
 * Determina si la pila está vacia.
 * Devuelve true si está vacía, false en caso contrario.
 */
bool pila_vacia(pila_t* pila){
	
	if(!pila)
		return true;
	else
		return (pila->tope == SIN_ELEMENTOS);
}

/* 
 * Devuelve la cantidad de elementos almacenados en la pila.
 */
int pila_cantidad(pila_t* pila){

	if(!pila)
		return SIN_ELEMENTOS;
	
	return (pila->tope);
}

/*
 * Devuelve el elemento en el tope de la pila o NULL
 * en caso de estar vacía.
 */
void* pila_tope(pila_t* pila){

	if(!pila || pila_vacia(pila))
		return NULL;
	else
		return pila->elementos[pila->tope - 1];
}

/* 
 * Destruye la pila liberando la memoria reservada para la misma.
 */
void pila_destruir(pila_t* pila){

	if(!pila)
		return;

	free(pila->elementos);	
	free(pila);
}

