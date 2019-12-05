#include "pruebas.h"
#include "pila.h"
#include <stdbool.h>
#include <stdio.h>
#define ERROR -1

// ---------------------------------------------- PRUEBAS SOBRE PILAS VACIAS / NULAS --------------------------------------------------------------------------------

// pre: 
// pos: Imprime por pantalla si paso la prueba (Desapilar una pila vacia deberia devolver error)
void siIntentoDesapilarUnaPilaVaciaDeberiaDevolverError(){

	printf("Inicializando prueba (Desapilar pila vacia deberia devolver error)\n");

	pila_t* pila = pila_crear();
    if(!pila){
        printf("FALLO al inicializar la prueba");
        return;
    }
       

	int retorno = pila_desapilar(pila);

	if(retorno == ERROR)
		printf("-------------------------------#OK, Devuelve error.-----------------------------------------\n\n\n");
	else
		printf("-------------------------------FALLO-------------------------------\n\n");

	pila_destruir(pila);

}

// pre: 
// pos: Imprime por pantalla si paso la prueba (Si intento ver el tope de una pila vacia deberia devolver NULL)
void siIntentoVerElTopeDePilaVaciaDeberiaDevolverNULL(){

	printf("Inicializando prueba (Ver tope de pila vacia deberia devolver NULL)\n");

	pila_t* pila = pila_crear();
    if(!pila){
        printf("FALLO al inicializar la prueba");
        return;
    }

	void* elemento = pila_tope(pila);

	if(!elemento)
		printf("-------------------------------#OK, Devuelve NULL.------------------------------------------\n\n\n");
	else
		printf("-------------------------------FALLO-------------------------------\n\n");

	pila_destruir(pila);

}

// pre: 
// pos: Imprime por pantalla si paso la prueba (Apilar sobre pila nula devuelve error)
void siApiloSobrePilaNulaDeberiaDevolverError(){

	printf("Inicializando prueba (Apilar sobre pila nula deberia devolver error)\n");

	pila_t* pila = NULL;

	int elemento = 5;

	int retorno = pila_apilar(pila, &elemento);

	if(retorno == ERROR)
		printf("-------------------------------#OK, Devuelve error.-----------------------------------------\n\n\n");
	else
		printf("-------------------------------FALLO-------------------------------\n\n");

}
// --------------------------------------- PRUEBAS SOBRE APILAR Y DESAPILAR CON ELEMENTOS -------------------------------------------------------------------

// pre: 
// pos: Imprime por pantalla si paso la prueba (Si lleno cantidad inicial el tamaño deberia duplicarse)
void siLlenoLaCantidadInicialElTamanioDeberiaDuplicarse(){

	printf("Inicializando prueba (Llenar cantidad inicial deberia duplicar el tamanio de la pila)\n");

	pila_t* pila = pila_crear();
    if(!pila){
        printf("FALLO al inicializar la prueba");
        return;
    }
	
	int elemento1 = 0;

	for (int i = 0; i < 6; ++i){
		pila_apilar(pila, &elemento1);
	}

	if(pila->tamanio == 10)
		printf("-------------------------------#OK, Duplica tamanio.----------------------------------------\n\n\n");
	else
		printf("-------------------------------FALLO-------------------------------\n\n");

	pila_destruir(pila);

}

// pre: 
// pos: Imprime por pantalla si paso la prueba (Si apilo y desapilo la misma cantidad de elementos pila vacia deberia devolver TRUE)
void siApiloYDesapiloMismoVolumenPilaVaciaDeberiaDevolverTrue(){

	pila_t* pila = pila_crear();
    if(!pila){
        printf("FALLO al inicializar la prueba");
        return;
    }

	printf("\nInicializando prueba (Apilar y Desapilar mismo volumen deberia dejar la pila vacia)\n");
	int elemento1 = 1, elemento2 = 2, elemento3 = 3, elemento4 = 4;

	for(int i = 0; i < 100; i++){

		pila_apilar(pila, &elemento1);
		pila_apilar(pila, &elemento2);
		pila_apilar(pila, &elemento3);
		pila_apilar(pila, &elemento4);
	}

	for (int i = 0; i < 400; ++i){
		pila_desapilar(pila);
	}

	if(pila_vacia(pila))
		printf("-------------------------------#OK, Pila vacia.---------------------------------------------\n\n\n");
	else
		printf("-------------------------------FALLO-------------------------------\n\n");

	pila_destruir(pila);

}

// pre: 
// pos: Imprime por pantalla si paso la prueba (Si desapilo la mitad de elementos el tamaño deberia reducirse a la mitad)
void siDesapiloLaMitadDeElementosLaPilaDeberiaAchicarse(){

	printf("Inicializando prueba (Si desapilo la mitad de los elementos la pila deberia achicarse)\n");

	pila_t* pila = pila_crear();
    if(!pila){
        printf("FALLO al inicializar la prueba");
        return;
    }

	int elemento = 5;

	for (int i = 0; i < 10; ++i){

		pila_apilar(pila, &elemento);
	}

	for (int i = 0; i < 6; ++i){

		pila_desapilar(pila);
	}


	if(pila->tamanio == 5)
		printf("-------------------------------#OK, Pila se achico.-----------------------------------------\n\n\n");

	else
		printf("-------------------------------FALLO-------------------------------\n\n");

	pila_destruir(pila);

}

// pre: 
// pos: Imprime por pantalla si paso la prueba (Si apilo, al desapilar deberia ver los elementos en orden inverso)
void siApiloElementosYLosDesapiloDeberiaDevolverlosEnOrdenInverso(){

	printf("Inicializando prueba (Si apilo elementos, al desapilarlos deberia devolverlos en orden inverso)\n");

	pila_t* pila = pila_crear();
    if(!pila){
        printf("FALLO al inicializar la prueba");
        return;
    }

	int elementos[10] = {0,1,2,3,4,5,6,7,8,9};
	int coincidencias = 0;
	int* elemento_aux;

	for (int i = 0; i < 10; ++i){

		pila_apilar(pila,&elementos[i]);
	}

	for (int j = 10; j > 0; --j){
		
		elemento_aux = (int*) pila_tope(pila);

		if((*elemento_aux) == elementos[j - 1])
			coincidencias++;

		pila_desapilar(pila);
	}

	if(coincidencias == 10)
		printf("-------------------------------#OK, Los devuelve en orden inverso.--------------------------\n\n\n");
	else
		printf("-------------------------------FALLO-------------------------------\n\n");

	pila_destruir(pila);
}
