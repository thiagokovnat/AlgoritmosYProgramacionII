#include <stdbool.h>
#include <stdlib.h>
#include "pila.h"
#include <stdio.h>
#include "lista.h"

#define ERROR -1
#define EXITO 0
#define SIN_ELEMENTOS 0

struct lista{
	pila_t* pila;	
};

struct lista_iterador{
	pila_t* pila;	
};

/*
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t* lista_crear(){

	lista_t* lista = malloc(sizeof(lista_t));
	if(!lista)
		return NULL;

	lista->pila = pila_crear();
	if(!lista->pila){
		free(lista);
		return NULL;
	}

	return lista;
}

/*
 * Inserta un elemento al final de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar(lista_t* lista, void* elemento){

	if(!lista || !lista->pila)
		return ERROR;

	return pila_apilar(lista->pila, elemento);
}

int llenar_pila_auxiliar(pila_t* pila_original, pila_t* nueva_pila){

	if(!pila_original || !nueva_pila)
		return ERROR;

	while(!pila_vacia(pila_original)){
		pila_apilar(nueva_pila, (void*)pila_tope(pila_original));
		pila_desapilar(pila_original);
	}

	return EXITO;
}

/*
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){

	if(!lista || !lista->pila)
		return ERROR;

	if(posicion > (pila_cantidad(lista->pila) - 1))
		return lista_insertar(lista, elemento);

	pila_t* pila_aux = pila_crear();
	if(!pila_aux)
		return ERROR;

	llenar_pila_auxiliar(lista->pila, pila_aux);
	int cantidad_insertados = 0;

	while(!pila_vacia(pila_aux)){

		if(cantidad_insertados == posicion)
			pila_apilar(lista->pila, elemento);

		else{
			pila_apilar(lista->pila, pila_tope(pila_aux));
			pila_desapilar(pila_aux);
		}

		cantidad_insertados++;
	}

	pila_destruir(pila_aux);
	return EXITO;

}

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar(lista_t* lista){

	if(!lista || !lista->pila)
		return ERROR;

	return pila_desapilar(lista->pila);
}

/*
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento.  
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.  
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar_de_posicion(lista_t* lista, size_t posicion){

	if(!lista || !lista->pila)
		return ERROR;

	if(posicion > (pila_cantidad(lista->pila) - 1))
		return lista_borrar(lista);

	pila_t* pila_aux = pila_crear();
	if(!pila_aux)
		return ERROR;

	llenar_pila_auxiliar(lista->pila, pila_aux);
	int cantidad_recorridos = 0;

	while(!pila_vacia(pila_aux)){

		if(cantidad_recorridos != posicion)
			pila_apilar(lista->pila, pila_tope(pila_aux));
		
		pila_desapilar(pila_aux);
		cantidad_recorridos++;
	}


	pila_destruir(pila_aux);
	return EXITO;
}

/*
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){

	if(!lista || !lista->pila)
		return NULL;

	if(posicion > (pila_cantidad(lista->pila) - 1))
		return lista_ultimo(lista);

	pila_t* pila_aux = pila_crear();
	if(!pila_aux)
		return NULL;

	llenar_pila_auxiliar(lista->pila, pila_aux);
	int cantidad_recorridos = 0;
	void* elem = NULL;

	while(!pila_vacia(pila_aux)){

		if(cantidad_recorridos == posicion)
			elem = pila_tope(pila_aux);
		
		pila_apilar(lista->pila, pila_tope(pila_aux));
		pila_desapilar(pila_aux);
		cantidad_recorridos++;
	}

	pila_destruir(pila_aux);
	return elem;
}

/* 
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
void* lista_ultimo(lista_t* lista){

	if(!lista || !lista->pila)
		return NULL;

	return pila_tope(lista->pila);
}

/* 
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t* lista){

	if(!lista || !lista->pila)
		return true;

	return pila_vacia(lista->pila);
}

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t* lista){

	if(!lista || !lista->pila)
		return SIN_ELEMENTOS;

	return (size_t) pila_cantidad(lista->pila);
}

/*
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t* lista){

	if(!lista || !lista->pila)
		return;

	pila_destruir(lista->pila);
	free(lista);
}

void inicializar_pila_iterador(pila_t* pila_lista, pila_t* pila_iter, void** vector){

	if(!pila_lista || !pila_iter || !vector)
		return;

	int indice_vector = 0;
	while(!pila_vacia(pila_lista)){
		vector[indice_vector] = pila_tope(pila_lista);
		pila_desapilar(pila_lista);
		indice_vector++;
	}

	for (int i = 0; i < indice_vector; ++i){
		pila_apilar(pila_iter, vector[i]);
		pila_apilar(pila_lista, vector[indice_vector - 1 - i]);
	}

}

/*
 * Crea un iterador para una lista. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique la lista iterada (agregando o quitando
 * elementos de la lista).
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
lista_iterador_t* lista_iterador_crear(lista_t* lista){

	if(!lista || !lista->pila)
		return NULL;

	lista_iterador_t* iter = malloc(sizeof(lista_iterador_t));
	if(!iter)
		return NULL;

	void** vector_aux = malloc(sizeof(void*) * lista_elementos(lista));
	if(!vector_aux){
		free(iter);
		return NULL;
	}

	iter->pila = pila_crear();
	if(!iter->pila){
		free(vector_aux);
		free(iter);
		return NULL;
	}

	inicializar_pila_iterador(lista->pila, iter->pila, vector_aux);
	free(vector_aux);
	return iter;
}

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){

	if(!iterador || !iterador->pila)
		return false;

	return !pila_vacia(iterador->pila);
}

/*
 * Avanza el iterador al proximo elemento y lo devuelve.
 * En caso de error devuelve NULL.
 */
void* lista_iterador_siguiente(lista_iterador_t* iterador){

	if(!iterador || !iterador->pila)
		return NULL;

	void* elem = NULL;

	if(!pila_vacia(iterador->pila)){
		elem = pila_tope(iterador->pila);
		pila_desapilar(iterador->pila);
	}

	return elem;
}

/*
 * Libera la memoria reservada por el iterador.
 */
void lista_iterador_destruir(lista_iterador_t* iterador){

	if(!iterador)
		return;

	if(iterador->pila)
		pila_destruir(iterador->pila);

	free(iterador);
}

/*
 * Iterador interno. Recorre la lista e invoca la funcion con cada
 * elemento de la misma.
 */
void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*)){

	if(!lista || !lista->pila || !funcion)
		return;

	void** vector_aux = malloc(sizeof(void*) * lista_elementos(lista));
	if(!vector_aux)
		return;

	int indice_vector = 0;
	while(!pila_vacia(lista->pila)){
		vector_aux[indice_vector] = pila_tope(lista->pila);
		pila_desapilar(lista->pila);
		indice_vector++;
	}

	for(int i = indice_vector - 1; i >= 0; i--){
		funcion(vector_aux[i]);
		pila_apilar(lista->pila, vector_aux[i]);
	}

	free(vector_aux);
}