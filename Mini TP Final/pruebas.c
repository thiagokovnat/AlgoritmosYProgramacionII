#include "lista.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define ERROR -1
#define EXITO 0
#define ANSI_COLOR_GREEN "\x1b[1m\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[1m\x1b[31m"

void assert_prueba(char* mensaje, bool condicion){

	if(condicion)
		printf(ANSI_COLOR_GREEN"#OK, %s\n\n" ANSI_COLOR_RESET, mensaje);
	else
		printf(ANSI_COLOR_RED"FALLO.\n\n" ANSI_COLOR_RESET);
}

// -----------------------------------------------PRUEBAS LISTA-----------------------------------------------------------//
void siInsertoYBorroEnListaNULLDeberiaDevolverError(){

	printf("Test: Si inserto y borro en lista NULL deberia devolver error.\n");
	lista_t* lista = NULL;
	int contador = 0;
	int elem = 4;

	if(lista_insertar(lista, &elem) == ERROR)
		contador++;
	if(lista_borrar(lista) == ERROR)
		contador++;

	assert_prueba("devuelven error", contador == 2);
}

void siIntentoVerElUltimoEnListaVaciaDeberiaDevolverNULL(){

	printf("Test: Si intento ver ultimo en lista vacia deberia devolver NULL.\n");
	lista_t* lista = lista_crear();

	assert_prueba("devuelve NULL", lista_ultimo(lista) == NULL);
	lista_destruir(lista);
}

void siIntentoVerElementoEnPosicionEnListaVaciaDeberiaDevolverNULL(){

	printf("Test: Si intento ver posicion en lista vacia deberia devolver NULL.\n");
	lista_t* lista = lista_crear();

	assert_prueba("devuelve NULL", lista_elemento_en_posicion(lista, 4) == NULL);
	lista_destruir(lista);
}

void siInsertoElementosListaElementosDeberiaDevolverLaCantidadDeElementosInsertados(){

	printf("Test: Lista elementos deberia devolver la cantidad de elementos insertados.\n");
	lista_t* lista = lista_crear();
	int elem = 0;

	for (int i = 0; i < 5; ++i)
		lista_insertar(lista, &elem);

	assert_prueba("devuelve la cantidad insertada.", lista_elementos(lista) == 5);
	lista_destruir(lista);
}

void siInsertoYBorroMismaCantidadDeElementosListaVaciaDeberiaDevolverTrue(){
	
	printf("Test: Si inserto y borro misma cantidad de elementos lista vacia deberia devolver true.\n");
	lista_t* lista = lista_crear();
	int elem = 0;

	for (int i = 0; i < 5; ++i)
		lista_insertar(lista, &elem);

	for (int i = 0; i < 5; ++i)
		lista_borrar(lista);

	assert_prueba(" devuelve true", lista_vacia(lista));
	lista_destruir(lista);
}

void siInsertoElementosEnDistintasPoisicionesVerElementoPosicionDeberiaDevolverLosElementos(){

	printf("Test: Si inserto elementos en distintas posiciones ver elemento deberia devolverlos\n");
	lista_t* lista = lista_crear();
	int elem0 = 0, elem1 = 1, elem2 = 2, elem3 = 3, elem4 = 4, elem5 = 5;
	int contador = 0;

	lista_insertar(lista, &elem1);
	lista_insertar_en_posicion(lista, &elem0, 0);
	lista_insertar(lista, &elem4);
	lista_insertar_en_posicion(lista, &elem3, 2);
	lista_insertar_en_posicion(lista, &elem5, 100);
	lista_insertar_en_posicion(lista, &elem2, 4);

	if(*(int*)lista_elemento_en_posicion(lista, 0) == elem0)
		contador++;

	if(*(int*)lista_elemento_en_posicion(lista, 1) == elem1)
		contador++;

	if(*(int*)lista_elemento_en_posicion(lista, 2) == elem3)
		contador++;

	if(*(int*)lista_elemento_en_posicion(lista, 3) == elem4)
		contador++;

	if(*(int*)lista_elemento_en_posicion(lista, 4) == elem2)
		contador++;

	if(*(int*)lista_elemento_en_posicion(lista, 5) == elem5)
		contador++;

	assert_prueba("devuelve los elementos esperados", contador == 6);
	lista_destruir(lista);
}

void siBorroElementosEnDistintasPosicionesVerElementoPosicionNoDeberiaDevolverEsosElementos(){

	printf("Test: Si borro elementos en distintas posiciones ver elemento no deberia devolverlos\n");
	lista_t* lista = lista_crear();
	int elem[5] = {0,1,2,3,4};
	int contador = 0;

	for (int i = 0; i < 5; ++i)
		lista_insertar(lista, &elem[i]);

	lista_borrar_de_posicion(lista, 0);
	lista_borrar_de_posicion(lista, 2);
	lista_borrar_de_posicion(lista, 1);


	if(*(int*)lista_elemento_en_posicion(lista, 0) == elem[1]){
		contador++;
	}


	if(*(int*)lista_elemento_en_posicion(lista, 1) == elem[4]){
		contador++;
	}

	assert_prueba("devuelve lo esperado", contador == 2);
	lista_destruir(lista);
}

// -------------------------------------------PRUEBAS ITERADOR EXTERNO/INTERNO-------------------------------------//

void siCreoUnIteradorConListaNulaDeberiaDevolverNULL(){

	printf("Test: Si creo un iterador con lista nula deberia devolver NULL\n");
	lista_t* lista = NULL;
	lista_iterador_t* iter = lista_iterador_crear(lista);

	assert_prueba("devuelve NULL", iter == NULL);
}


void siRecorroTodaLaListaConElIteradorDeberiaDevolverTodosLosElementos(){

	printf("Test: Si recorro toda la lista con el iterador, deberia devolver todos los elementos de la lista\n");
	lista_t* lista = lista_crear();
	int elem0 = 1;
	int tope = 0;
	
	for(int i = 0; i < 1000; i++)
		lista_insertar(lista, &elem0);

	lista_iterador_t* iter = lista_iterador_crear(lista);

	while(lista_iterador_tiene_siguiente(iter)){
		
		if(lista_iterador_siguiente(iter) != NULL)
			tope++;
	}

	assert_prueba("devuelve todos los elementos", tope == 1000);
	lista_iterador_destruir(iter);
	lista_destruir(lista);
}


void siCreoUnIteradorSobreListaNoVaciaTieneSiguienteDeberiaDevolverTrue(){

	printf("Test: Si creo un iterador sobre una lista no vacia, tiene siguiente deberia devolver true\n");
	lista_t* lista = lista_crear();
	int elem0 = 1;
	lista_insertar(lista, &elem0);

	lista_iterador_t* iter = lista_iterador_crear(lista);
	assert_prueba("devuelve true", lista_iterador_tiene_siguiente(iter));

	lista_iterador_destruir(iter);
	lista_destruir(lista);
}


void tieneSiguienteDeberiaDevolverFalseSiEstoyEnElUltimoElemento(){

	printf("Test: Tiene siguiente deberia devolver false si estoy en el ultimo elemento\n");
	lista_t* lista = lista_crear();
	int elem0 = 1;
	lista_insertar(lista, &elem0);

	lista_iterador_t* iter = lista_iterador_crear(lista);
	lista_iterador_siguiente(iter);

	assert_prueba("devuelve false", !lista_iterador_tiene_siguiente(iter));
	lista_iterador_destruir(iter);
	lista_destruir(lista);
}

void mostrar_elemento(void* elemento){
  if(elemento)
    printf("%c", *(char*)elemento);
}


void imprimirElementosUsandoIteradorInterno(){

	lista_t* lista = lista_crear();
	char o = 'O', k = 'k', i = 'i', m = 'm', p = 'p', r = 'r', e = 'e', coma = ',';

	lista_insertar(lista, &o);
	lista_insertar(lista, &k);
	lista_insertar(lista, &coma);
	lista_insertar(lista, &i);
	lista_insertar(lista, &m);
	lista_insertar(lista, &p);
	lista_insertar(lista, &r);
	lista_insertar(lista, &i);
	lista_insertar(lista, &m);
	lista_insertar(lista, &e);

	printf("Test: Imprimo la lista usando el iterador interno (Deberia imprimir: Ok, imprime): ");
  	lista_con_cada_elemento(lista, mostrar_elemento);
  	printf("\n");

  	lista_destruir(lista);
}


