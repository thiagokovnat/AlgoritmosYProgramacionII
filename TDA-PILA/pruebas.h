#ifndef __PRUEBAS_H__
#define __PRUEBAS_H__

#include "pila.h"
#include <stdbool.h>
#include <stdio.h>


// ---------------------------------------------- PRUEBAS SOBRE PILAS VACIAS / NULAS --------------------------------------------------------------------------------

// pre: 
// pos: Imprime por pantalla si paso la prueba (Desapilar una pila vacia deberia devolver error)
void siIntentoDesapilarUnaPilaVaciaDeberiaDevolverError();


// pre: 
// pos: Imprime por pantalla si paso la prueba (Si intento ver el tope de una pila vacia deberia devolver NULL)
void siIntentoVerElTopeDePilaVaciaDeberiaDevolverNULL();

// pre: 
// pos: Imprime por pantalla si paso la prueba (Apilar sobre pila nula devuelve error)
void siApiloSobrePilaNulaDeberiaDevolverError();

// --------------------------------------- PRUEBAS SOBRE APILAR Y DESAPILAR CON ELEMENTOS -------------------------------------------------------------------

// pre: 
// pos: Imprime por pantalla si paso la prueba (Si lleno cantidad inicial el tamaño deberia duplicarse)
void siLlenoLaCantidadInicialElTamanioDeberiaDuplicarse();


// pre: 
// pos: Imprime por pantalla si paso la prueba (Si apilo y desapilo la misma cantidad de elementos pila vacia deberia devolver TRUE)
void siApiloYDesapiloMismoVolumenPilaVaciaDeberiaDevolverTrue();


// pre: 
// pos: Imprime por pantalla si paso la prueba (Si desapilo la mitad de elementos el tamaño deberia reducirse a la mitad)
void siDesapiloLaMitadDeElementosLaPilaDeberiaAchicarse();

// pre: 
// pos: Imprime por pantalla si paso la prueba (Si apilo, al desapilar deberia ver los elementos en orden inverso)
void siApiloElementosYLosDesapiloDeberiaDevolverlosEnOrdenInverso();	

#endif /* __PRUEBAS_H__ */

