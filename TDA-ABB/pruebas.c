#include <stdio.h>
#include <stdlib.h>
#include "abb.h"
#include <stdbool.h>
#define ERROR -1
#define EXITO 0
#define ANSI_COLOR_GREEN   "\x1b[1m\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED	"\x1b[1m\x1b[31m"
static int success = 0;
static int failure = 0;

typedef struct cosa{
	int clave;
	int contenido[10];
}Cosa;

void destruir_cosa(Cosa* c){
    if(c)
		free(c);
}

int comparar_cosas(void* elemento1, void* elemento2){

    if(!elemento1 || !elemento2)
		return 0;

    if(((Cosa*)elemento1)->clave>((Cosa*)elemento2)->clave)
		return 1;

    if(((Cosa*)elemento1)->clave<((Cosa*)elemento2)->clave)
		return -1;

    return 0;
}

void destructor_de_cosas(void* elemento){
    if(!elemento)
		return;
    destruir_cosa((Cosa*)elemento);
}


Cosa* crear_cosa(int clave){

	Cosa* aux = malloc(sizeof(Cosa));
	if(!aux)
		return NULL;

	aux->clave = clave;
	return aux;
}

void assert_prueba(char* prueba, bool condicion){

	printf("Test: %s: ", prueba);

	if(condicion){
        success++;
		printf(ANSI_COLOR_GREEN "OK. \n" ANSI_COLOR_RESET);
    }	
    else{
        failure++;
		printf(ANSI_COLOR_RED"FALLO.\n" ANSI_COLOR_RESET);
    }
}


void test_arboles_nulos(){

	printf("\nTEST SOBRE ARBOLES NULOS: \n\n");
	abb_t* abb = NULL;
	Cosa* cosa = crear_cosa(1);
	bool condicion = arbol_insertar(abb, cosa) == ERROR;

	assert_prueba("Insertar en Arbol Nulo deberia devolver error", condicion);
	assert_prueba("Arbol nulo deberia ser considerado vacio", arbol_vacio(abb));
	assert_prueba("Borrar sobre arbol nulo deberia devolver error", arbol_borrar(abb, cosa) == ERROR);
	assert_prueba("Buscar en arbol nulo deberia devolver NULL", arbol_buscar(abb, cosa) == NULL);

	void* array[2];

	assert_prueba("Recorrer preorden en arbol nulo deberia devolver 0", arbol_recorrido_preorden(abb, array, 2) == 0);
	assert_prueba("Recorrer postorden en arbol nulo deberia devolver 0", arbol_recorrido_postorden(abb, array, 2) == 0);
	assert_prueba("Recorrer inorden en arbol nulo deberia devolver 0", arbol_recorrido_inorden(abb, array, 2) == 0);

	if(condicion)
		free(cosa);
}

void test_insercion_y_borrado(){

	printf("\nTEST SOBRE INSERCION Y BORRADO: \n\n");

	Cosa* cosa1 = crear_cosa(1);
	Cosa* cosa2 = crear_cosa(2);
	Cosa* cosa3 = crear_cosa(3);
	Cosa* cosa4 = crear_cosa(4);
	Cosa* cosa5 = crear_cosa(5);
	Cosa* cosa6 = crear_cosa(6);

	abb_t* abb = arbol_crear(comparar_cosas, destructor_de_cosas);
	arbol_insertar(abb, cosa3);
	arbol_insertar(abb, cosa5);
	arbol_insertar(abb, cosa4);
	arbol_insertar(abb, cosa1);
	arbol_insertar(abb, cosa2);

	assert_prueba("Raiz deberia ser 3", ((Cosa*)arbol_raiz(abb))->clave == 3);

	Cosa* aux = abb->nodo_raiz->derecha->elemento;
	assert_prueba("Nodo derecho deberia ser el 5", aux->clave == 5);

	aux = abb->nodo_raiz->izquierda->elemento;
	assert_prueba("Nodo izquierdo deberia ser el 1", aux->clave == 1);

	assert_prueba("Borro el nodo raiz con dos hijos (3)", arbol_borrar(abb, cosa3) == EXITO);
	assert_prueba("Nodo raiz deberia ser el 4", ((Cosa*)arbol_raiz(abb))->clave == 4);

	aux = abb->nodo_raiz->derecha->elemento;
	assert_prueba("Nodo derecho deberia seguir siendo el 5", aux->clave == 5);

	aux = (Cosa*)abb->nodo_raiz->derecha->izquierda;
	assert_prueba("El hijo derecho de la raiz ya no deberia tener hijo izquierdo", aux == NULL);

	arbol_borrar(abb, cosa5);
	aux = (Cosa*)abb->nodo_raiz->derecha;
	assert_prueba("Borro nodo sin hijos (5)", aux == NULL);

	arbol_borrar(abb, cosa1);
	aux = abb->nodo_raiz->izquierda->elemento;
	assert_prueba("Borro nodo con un solo hijo (1)", aux->clave == 2);

	arbol_insertar(abb, cosa6);
	aux = abb->nodo_raiz->derecha->elemento;
	assert_prueba("Inserto el 6, deberia ir a derecha de la raiz", aux->clave == 6);

	cosa1 = crear_cosa(1);
    int retorno_borrar_inexistente = arbol_borrar(abb, cosa1);
    assert_prueba("Borro un elemento que no esta en el arbol, deberia devolver ERROR", retorno_borrar_inexistente == ERROR);
	free(cosa1);


	while(!arbol_vacio(abb))
		arbol_borrar(abb, arbol_raiz(abb));

	assert_prueba("Borro todos los elementos, nodo raiz deberia ser null", abb->nodo_raiz == NULL);


	arbol_destruir(abb);

}


void test_volumen(){

	printf("\nPRUEBAS CON VOLUMENES: \n\n");
	Cosa* cosas[1000];
	abb_t* abb = arbol_crear(comparar_cosas, destructor_de_cosas);

	for (int i = 0; i < 1000; ++i)
		cosas[i] = crear_cosa(i);

	arbol_insertar(abb, cosas[500]);

	for (int i = 0; i < 1000; ++i){
		if(i != 500)
			arbol_insertar(abb, cosas[i]);
	}

	Cosa* aux = abb->nodo_raiz->elemento;
	assert_prueba("Inserto 1k de elementos, nodo raiz deberia ser 500", aux->clave == 500);


	arbol_borrar(abb, arbol_raiz(abb));
	aux = abb->nodo_raiz->elemento;
	assert_prueba("Borro la raiz, la nueva raiz deberia ser el 501", aux->clave == 501);

	aux = abb->nodo_raiz->izquierda->elemento;
	arbol_borrar(abb, aux);
	aux = abb->nodo_raiz->izquierda->elemento;
	assert_prueba("Borro nodo con 1 hijo (0)", aux->clave == 1);

	cosas[0] = crear_cosa(0);
	arbol_insertar(abb, cosas[0]);
	aux = abb->nodo_raiz->izquierda->izquierda->elemento;
	assert_prueba("Inserto el 0, ahora deberia ir a la izquierda del 1", aux->clave == 0);

	arbol_borrar(abb, abb->nodo_raiz->izquierda->elemento);
	aux = abb->nodo_raiz->izquierda->elemento;
	assert_prueba("Borro nodo izquierdo con 2 hijos (1)", aux->clave == 2);

	aux = abb->nodo_raiz->izquierda->izquierda->elemento;
	assert_prueba("El 0 deberia seguir estando a la izquierda del nuevo nodo izquierdo", aux->clave == 0);

	while(!arbol_vacio(abb))
		arbol_borrar(abb, arbol_raiz(abb));

	assert_prueba("Borro todos los elementos, nodo raiz deberia ser null", abb->nodo_raiz == NULL);

	arbol_destruir(abb);
}

void test_recorridos(){

	printf("\nPRUEBAS DE RECORRIDOS: \n\n");
	Cosa* cosas[50];
	abb_t* abb = arbol_crear(comparar_cosas, destructor_de_cosas);

	for (int i = 0; i < 50; ++i)
		cosas[i] = crear_cosa(i);

	arbol_insertar(abb, cosas[25]);

	for (int i = 0; i < 50; ++i){
		if(i != 25)
			arbol_insertar(abb, cosas[i]);
	}

	void* array[50];
	int tamanio_array = 50;
	int coincidencias = 0;
	int retorno = arbol_recorrido_inorden(abb, array, tamanio_array);
	for (int i = 0; i < 49; ++i){
		if(comparar_cosas(array[i], array[i + 1]) == -1)
			coincidencias++;
	}

	assert_prueba("Recorrer inorden deberia devolver un array ordenado ascendentemente", coincidencias == 49);
	assert_prueba("Recorrer inorden deberia devolver la cantidad de elementos insertados", retorno == 50);

	void* array2[25];
	int tamanaio_array2 = 25;
	int retorno2 = arbol_recorrido_inorden(abb, array2, tamanaio_array2);
	assert_prueba("Si recorro inorden con un array mas chico a la cantidad de elementos, deberia llenar el array y devolver su tamaño", retorno2 == 25);

	abb_t* abb2 = arbol_crear(comparar_cosas, destructor_de_cosas);
	Cosa* cosa1 = crear_cosa(1);
	Cosa* cosa2 = crear_cosa(2);
	Cosa* cosa3 = crear_cosa(3);
	Cosa* cosa4 = crear_cosa(4);
	Cosa* cosa5 = crear_cosa(5);

	arbol_insertar(abb2, cosa3);
	arbol_insertar(abb2, cosa1);
	arbol_insertar(abb2, cosa2);
	arbol_insertar(abb2, cosa5);
	arbol_insertar(abb2, cosa4);

	void* array3[5];
	int array_resultado[5] = {2,1,4,5,3};
	int tamanio_array3 = 5;
	int coincidencias_postorden = 0;

	int retorno_postorden = arbol_recorrido_postorden(abb2, array3, tamanio_array3);

	for(int i = 0; i < 5; i++){

		Cosa* aux = (Cosa*)array3[i];
		if(aux->clave == array_resultado[i])
			coincidencias_postorden++;
	}

	assert_prueba("Recorro postorden, deberia llenar el array en la forma esperada", coincidencias_postorden == 5);
	assert_prueba("Recorrer postorden deberia devolver la cantidad insertada", retorno_postorden == 5);

	void* array4[3];
	int tamanio_array4 = 3;
	int retorno_postorden2 = arbol_recorrido_postorden(abb2, array4, tamanio_array4);
	assert_prueba("Si recorro postorden con un array mas chico, deberia llenarlo y devolver su tamaño", retorno_postorden2 == 3);

	void* array5[5];
	int tamanio_array5 = 5;
	int array_resultado_preorden[5] = {3,1,2,5,4};
	int retorno_preorden = arbol_recorrido_preorden(abb2, array5, tamanio_array5);
	int coincidencias_preorden = 0;

	for(int i = 0; i < 5; i++){

		Cosa* aux = (Cosa*)array5[i];
		if(aux->clave == array_resultado_preorden[i])
			coincidencias_preorden++;
	}

	assert_prueba("Recorro preorden, deberia llenar el array en la forma esperada", coincidencias_preorden == 5);
	assert_prueba("Recorrer preorden deberia devolver la cantidad insertada", retorno_preorden == 5);

	void* array6[3];
	int tamanio_array6 = 3;
	int retorno_preorden2 = arbol_recorrido_postorden(abb2, array4, tamanio_array6);
	assert_prueba("Si recorro preorden con un array mas chico, deberia llenarlo y devolver su tamaño", retorno_preorden2 == 3);

	arbol_destruir(abb2);
	arbol_destruir(abb);


}

void pruebas_busqueda(){

	printf("\nTEST SOBRE BUSQUEDA: \n\n");

	Cosa* cosa1 = crear_cosa(1);
	Cosa* cosa2 = crear_cosa(2);
	Cosa* cosa3 = crear_cosa(3);
	Cosa* cosa4 = crear_cosa(4);
	Cosa* cosa5 = crear_cosa(5);
	Cosa* cosa6 = crear_cosa(6);
	Cosa* cosa7 = crear_cosa(7);

	abb_t* abb = arbol_crear(comparar_cosas, destructor_de_cosas);
	arbol_insertar(abb, cosa3);
	arbol_insertar(abb, cosa5);
	arbol_insertar(abb, cosa4);
	arbol_insertar(abb, cosa1);
	arbol_insertar(abb, cosa2);
	arbol_insertar(abb, cosa6);

	assert_prueba("Buscar un elemento que esta en el arbol deberia devolver el elemento", ((Cosa*)arbol_buscar(abb, cosa1))->clave == 1);
	assert_prueba("Buscar un elemento que no esta en el arbol deberia devolver NULL", arbol_buscar(abb, cosa7) == NULL);
	arbol_insertar(abb, cosa7);
	assert_prueba("Inserto un elemento que previamente no estaba, deberia devolver dicho elemento", ((Cosa*)arbol_buscar(abb, cosa7))->clave == 7);

	arbol_destruir(abb);
}

void print_test(){

	printf("\nOverall:\n");

	printf("Pruebas Corridas: %i\n", failure + success);
	printf("Pruebas Pasadas:" ANSI_COLOR_GREEN "%i \n" ANSI_COLOR_RESET , success);
	printf("Pruebas Fallidas:" ANSI_COLOR_RED "%i\n" ANSI_COLOR_RESET, failure);
}
