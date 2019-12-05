#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "cuervo_tres_ojos.h"

#define ERROR -1
#define LECTURA "r"
#define CANTIDAD_CAMPOS_VISIONES 4



// PRECONDICIONES: EL USUARIO INGRESARA EL TIPO DE DATO QUE SE ESPERA, ES DECIR, NO INGRESARA UN CARACTER CUANDO SE ESPERA UN ENTERO (O VICEVERSA)
// POSTCONDICIONES: EL PROGRAMA CARGARA LAS VISIONES AL CUERVO, LAS TRANSMITIRA SEGUN EL CRITERIO DEL USUARIO Y MOSTRARA POR PANTALLA AQUELLAS QUE CUMPLAN EL CRITERIO DEL USUARIO

// pre: 
// pos: devuelve TRUE si la casa protagonista es Targaryen, FALSE en caso contrario
bool criterio_targaryen(vision_t vision){

	return ((strcmp(vision.casa_protagonista, "Targaryen") == 0));
}

// pre: 
// pos: devuelve TRUE si el protagonista es Jon Snow, FALSE en caso contrario
bool criterio_snow(vision_t vision){

	return ((strcmp(vision.protagonista, "Jon Snow") == 0));	
}

// pre: 
// pos: devuelve TRUE si el protagonista es Tyrion Lannister, FALSE en caso contrario
bool criterio_lannister(vision_t vision){

	return ((strcmp(vision.protagonista, "Tyrion Lannister") == 0));
}



// pre: visiones ya fue abierto
// pos: agrega las visiones del archivo en el vector de visiones del cuervo
int cargar_visiones(cuervo_tres_ojos_t* cuervo, FILE* visiones){

	vision_t vision;
	int retorno = 0;
	int leidos = fscanf(visiones, "%[^;];%[^;];%[^;];%c\n", vision.protagonista, vision.casa_protagonista, vision.descripcion, &vision.epoca);

	while((leidos == CANTIDAD_CAMPOS_VISIONES) && (retorno == 0)){

		retorno = agregar_vision(cuervo, vision);
		leidos = fscanf(visiones, "%[^;];%[^;];%[^;];%c\n", vision.protagonista, vision.casa_protagonista, vision.descripcion, &vision.epoca);
	}

	
	if( (leidos != -1) || (retorno == ERROR)){
		printf("Error al cargar las visiones al cuervo. \n");
		return ERROR;
	}


	return 0;
}


// pre:
// pos: lista las visiones segun los distintos criterios
void listar_visiones(cuervo_aprendiz_t* aprendiz){

	bool (*es_listable_targaryen)(vision_t) = &criterio_targaryen;
	bool (*es_listable_snow)(vision_t) = &criterio_snow;
	bool (*es_listable_lannister)(vision_t) = &criterio_lannister;


	listar_visiones_transmitidas(*aprendiz, (*es_listable_targaryen));	
	listar_visiones_transmitidas(*aprendiz, (*es_listable_snow));
	listar_visiones_transmitidas(*aprendiz, (*es_listable_lannister));

}


int main(){

	FILE* visiones = fopen("visiones.txt",LECTURA);
	if(visiones == NULL)
		return ERROR;

	cuervo_tres_ojos_t* cuervo = invocar_cuervo("Three Eyed Raven");
	if(cuervo == NULL){
		printf("Error al invocar al cuervo\n");
		fclose(visiones);
		return ERROR;
	}

	cuervo_aprendiz_t* cuervo_aprendiz = invocar_aprendiz("Brandon Stark");
	if(cuervo_aprendiz == NULL){
		printf("Error al invocar al aprendiz\n");
		fclose(visiones);
		destruir_cuervo(cuervo);
		return ERROR;
	}
	
	int retorno_cargar = cargar_visiones(cuervo, visiones);
	if(retorno_cargar == ERROR){
		destruir_cuervo(cuervo);
		destruir_aprendiz(cuervo_aprendiz);
		fclose(visiones);
		return ERROR;
	}

	fclose(visiones);
		
	bool (*es_transmisible_targaryen)(vision_t) = &criterio_targaryen;
	bool (*es_transmisible_snow)(vision_t) = &criterio_snow;
	bool (*es_transmisible_lannister)(vision_t) = &criterio_lannister;

	

	int retorno_aux = transmitir_visiones(cuervo, cuervo_aprendiz, (*es_transmisible_targaryen));
	if(retorno_aux == ERROR){
		destruir_cuervo(cuervo);
		destruir_aprendiz(cuervo_aprendiz);
	}

	retorno_aux = transmitir_visiones(cuervo, cuervo_aprendiz, (*es_transmisible_snow));
	if(retorno_aux == ERROR){
		destruir_cuervo(cuervo);
		destruir_aprendiz(cuervo_aprendiz);
	}
	
	retorno_aux = transmitir_visiones(cuervo, cuervo_aprendiz, (*es_transmisible_lannister));
	if(retorno_aux == ERROR){
		destruir_cuervo(cuervo);
		destruir_aprendiz(cuervo_aprendiz);
	}
		
	listar_visiones(cuervo_aprendiz);	
	destruir_cuervo(cuervo);
	destruir_aprendiz(cuervo_aprendiz);

	return 0;
}