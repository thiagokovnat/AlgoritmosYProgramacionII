#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "cuervo_tres_ojos.h"

#define CANTIDAD_VISIONES_INICIALES  0
#define LECTURA "r"
#define FORMATO "%[^\;];%[^\;];%[^\;];%c\n"
#define CANTIDAD_CAMPOS_VISIONES 4
#define PASADO 'P'
#define COINCIDENCIA 0
#define ERROR -1
#define FUTURO 'F'

/*
 * Recibe el nombre del cuervo a invocar.
 * Creará la estructura cuervo_tres_ojos, reservando la memoria necesaria.
 * Devolverá la estructura con los topes de las visiones inicializados en 0.
 * En caso de no poder invocar al cuervo, devolverá NULL.
 */
cuervo_tres_ojos_t* invocar_cuervo(char* nombre){

	cuervo_tres_ojos_t* cuervo = malloc(sizeof(cuervo_tres_ojos_t));

	if(cuervo != NULL){
		
		strcpy(cuervo->nombre, nombre);

		cuervo->visiones_del_pasado = malloc(sizeof(vision_t));
		if(cuervo->visiones_del_pasado == NULL){
			free(cuervo);
			return NULL;
		}

		cuervo->visiones_del_futuro = malloc(sizeof(vision_t));
		if(cuervo->visiones_del_futuro == NULL){
			free(cuervo->visiones_del_pasado);
			free(cuervo);
			return NULL;
		}

		cuervo->cantidad_visiones_pasado = CANTIDAD_VISIONES_INICIALES;
		cuervo->cantidad_visiones_futuro = CANTIDAD_VISIONES_INICIALES;
	}

	return cuervo;
}

/*
 * Recibe el nombre del aprendiz a invocar.
 * Creará la estructura cuervo_aprendiz, reservando la memoria necesaria.
 * Devolverá la estructura con el tope de las visiones inicializado en 0.
 * En caso de no poder invocar al aprendiz, devolverá NULL.
 */
cuervo_aprendiz_t* invocar_aprendiz(char* nombre){

	cuervo_aprendiz_t* cuervo_aprendiz = malloc(sizeof(cuervo_aprendiz_t));
	
	if(cuervo_aprendiz != NULL){

		strcpy(cuervo_aprendiz->nombre, nombre);

		cuervo_aprendiz->visiones_adquiridas = malloc(sizeof(vision_t));
		if(cuervo_aprendiz->visiones_adquiridas == NULL){
			free(cuervo_aprendiz);
			return NULL;
		}

		cuervo_aprendiz->cantidad_visiones = CANTIDAD_VISIONES_INICIALES;
	}

	return cuervo_aprendiz;
	
}

// pre: tope toma un valor entre 0 y la cantidad maxima de registros que caben en la memoria que se tiene
// pos: aumenta el tamaño del vector visiones, agrega la vision_actual y tambien el tope del vector
int agregar_vision_general(vision_t** visiones, vision_t vision_actual, int* tope){

	int cantidad = (*tope) + 1;
	
	vision_t* aux = realloc((*visiones),(long unsigned int) cantidad * sizeof(vision_t));

	if(aux == NULL){
		perror("ERROR al agregar vision");
		return ERROR;
	}
	
	(*visiones) = aux;

	(*visiones)[(*tope)] = vision_actual;

	(*tope)++;

	return 0;
}

/*
 * Agrega una vision al vector de visiones correspondiente.
 * Reservando la memoria necesaria para ella.
 * Devolverá 0 si pudo agregarla o -1 si no pudo.
 */
int agregar_vision(cuervo_tres_ojos_t* cuervo, vision_t vision){

	int retorno = 0;

	if(vision.epoca == PASADO){

		retorno = agregar_vision_general(&cuervo->visiones_del_pasado, vision, &cuervo->cantidad_visiones_pasado);

		if(retorno == ERROR){
			printf("Error al agregar vision\n");
			return ERROR;
		}
		
		return 0;
	}

	else if(vision.epoca == FUTURO){

		int retorno = agregar_vision_general(&cuervo->visiones_del_futuro, vision, &cuervo->cantidad_visiones_futuro);

		if(retorno == ERROR){
			printf("Error al agregar vision\n");
			return ERROR;
		}
		
		return 0;
	}

	else{
		printf("Error al agregar vision debido a formato invalido \n");
		return ERROR;
	}
}

// pre:
// pos: devuelve TRUE si las visiones son iguales, FALSE en caso contrario.
bool son_visiones_identicas(vision_t vision_actual, vision_t vision){

	if(strcmp(vision_actual.descripcion, vision.descripcion) == COINCIDENCIA){

		if(strcmp(vision_actual.protagonista, vision.protagonista) == COINCIDENCIA){

			if(strcmp(vision_actual.casa_protagonista, vision.casa_protagonista) == COINCIDENCIA){

				if(vision_actual.epoca == vision.epoca)
					return true;
			}
		}
	}

	return false;
}

// pre: 
// pos: devuelve TRUE si el cuervo aprendiz ya conoce de esa vision, FALSE en caso contrario.
bool posee_vision(cuervo_aprendiz_t* aprendiz, vision_t vision){

	bool posee_la_vision = false;
	int i = 0;

	while((!posee_la_vision) && (i < aprendiz->cantidad_visiones)){

		if(son_visiones_identicas(aprendiz->visiones_adquiridas[i], vision))
			posee_la_vision = true;
				
		i++;
	}

	return posee_la_vision;
}

/*
 * Transmitirá al aprendiz las visiones del pasado y del futuro del cuervo que sean 
 * transmisibles de acuerdo a la función recibida como parámetro.
 * En caso de que la visión a transmitir ya sea conocida por el aprendiz (repetida), 
 * no se agrega a las visiones del mismo.
 * Devolverá 0 si se transmitieron con eso, -1 en caso contrario
 */
int transmitir_visiones(cuervo_tres_ojos_t* cuervo, cuervo_aprendiz_t* aprendiz, bool (*es_transmisible)(vision_t)){

	int i = 0;
	int j = 0;
	int retorno = 0;

	while((i < cuervo->cantidad_visiones_pasado || j < cuervo->cantidad_visiones_futuro) && (retorno == 0)){

		
		if((i < cuervo->cantidad_visiones_pasado) && ((*es_transmisible)(cuervo->visiones_del_pasado[i])) && (!posee_vision(aprendiz, cuervo->visiones_del_pasado[i])))
			retorno = agregar_vision_general(&aprendiz->visiones_adquiridas, cuervo->visiones_del_pasado[i], &aprendiz->cantidad_visiones);

		if(retorno == 0){
			
			if((j < cuervo->cantidad_visiones_futuro) && ((*es_transmisible)(cuervo->visiones_del_futuro[j])) && (!posee_vision(aprendiz, cuervo->visiones_del_futuro[j])))
				retorno = agregar_vision_general(&aprendiz->visiones_adquiridas, cuervo->visiones_del_futuro[j], &aprendiz->cantidad_visiones);
		}

		i++;
		j++;
	}

	return retorno;
}

// pre: la vision es valida y es listable
// pos: muestra por pantalla la informacion de la vision
void imprimir_vision_transmitida(vision_t vision){
	
	printf("\nProtagonista: %s\n", vision.protagonista);
	printf("Casa del protagonista: Casa %s\n", vision.casa_protagonista);
	printf("Descripcion de la vision: %s\n", vision.descripcion);

	if(vision.epoca == PASADO)
		printf("Epoca: Pasado\n");
	else
		printf("Epoca: Futuro\n");
}

/*
 * Mostrará por pantalla las visiones adquiridas por el aprendiz.
 * Una visión se listará sólo si la función recibida como parámetro lo permite.
 */
void listar_visiones_transmitidas(cuervo_aprendiz_t aprendiz, bool (*es_listable)(vision_t)){

	for (int i = 0; i < aprendiz.cantidad_visiones; ++i){

		if((*es_listable)(aprendiz.visiones_adquiridas[i]))
			imprimir_vision_transmitida(aprendiz.visiones_adquiridas[i]);
	}

}

/*
 * Destruirá la estructura del cuervo, liberando la memoria reservada para él y sus visiones.
 * Devolverá  si pudo liberar la memoria o -1 si no pudo.
 */
int destruir_cuervo(cuervo_tres_ojos_t* cuervo){

	if(cuervo == NULL)
		return ERROR;
	
	free(cuervo->visiones_del_pasado);
	free(cuervo->visiones_del_futuro);
	free(cuervo);

	return 0;
}

/*
 * Destruirá la estructura del aprendiz, liberando la memoria reservada para él y sus visiones.
 * Devolverá  si pudo liberar la memoria o -1 si no pudo.
 */
int destruir_aprendiz(cuervo_aprendiz_t* aprendiz){

	if(aprendiz == NULL)
		return ERROR;

	free(aprendiz->visiones_adquiridas);
	free(aprendiz);
	
	return 0;
}