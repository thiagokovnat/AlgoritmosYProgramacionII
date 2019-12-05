#include "juego_de_tronos.h"
#include "lista.h"
#include "cola.h"
#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIMULAR 'S'
#define LISTAR 'L'
#define QUIT 'Q'
#define EXTINTOS 'E'
#define AGREGAR_CASA 'A'

#define MAX_NOMBRE 50
#define ERROR -1
#define EXITO 0
#define ESPERANZA_VIDA 60
#define LECTURA "r"

typedef struct integrante{
	int edad;
}integrante_t;

extern char* strdup(const char*);

// pre: 
// pos: libera la memoria asociada a un integrante de una casa
void destruir_miembro(void* integrante){

	if(integrante)
		free(integrante);	
}

// pre:
// pos: crea una casa con el nombre, factor de envejecimiento y nacimiento dados
casa_t* crear_casa(char* nombre_casa, int factor_envejecimiento, int factor_nacimiento){

	casa_t* casa = malloc(sizeof(casa_t));
	if(!casa)
		return NULL;

	casa->nombre = nombre_casa;
	casa->factor_envejecimiento = factor_envejecimiento;
	casa->integrantes = lista_crear(destruir_miembro);
	casa->cantidad_integrantes = 0;

	if(!casa->integrantes){
		free(casa);
		return NULL;
	}

	casa->factor_nacimiento = factor_nacimiento;
	return casa;
}

// pre: casa existe
// pos: crea un miembro de la casa y lo inserta en la misma
int insertar_miembro(casa_t* casa, int edad){

	if(!casa)
		return ERROR;

	integrante_t* integrante = malloc(sizeof(integrante_t));
	if(!integrante)
		return ERROR;

	integrante->edad = edad;
	casa->cantidad_integrantes++;

	return lista_insertar(casa->integrantes, integrante);
}


// pre:
// pos: inserta la cantidad de nuevos miembros segun factor de nacimiento
void nacimientos_casas(casa_t* casa){

	if(casa->cantidad_integrantes == 0 || casa->factor_nacimiento == 0)
		return;

	int cantidad_a_insertar = (int) casa->cantidad_integrantes / casa->factor_nacimiento;
	for(int i = 0; i < cantidad_a_insertar; i++)
		insertar_miembro(casa, 0);	
}



// pre: tope esta entre 0 y el maximo del vector
// pos: devuelve TRUE si la casa ya esta en el vector.
bool casa_ya_esta(casa_t* casa, casa_t** array, size_t tope){

	if(!casa || !array)
		return false;

	bool encontro = false;
	int i = 0;

	while(i < tope && !encontro){
		if(strcmp(array[i]->nombre, casa->nombre) == 0)
			encontro = true;
		i++;
	}

	return encontro;
}

// pre:
// pos: muestra por pantalla la casa con mayor cantidad de integrantes.
void mostrar_ganador(abb_t* arbol, size_t cantidad_casas){

	if(!arbol)
		return;

	casa_t* casas[cantidad_casas];
	int cantidad_insertada = arbol_recorrido_inorden(arbol, (void**)casas, (int) cantidad_casas);
	size_t integrantes_maximos = 0;
	int posicion_ganadora = -1;


	for (int i = 0; i < cantidad_insertada; ++i){

		if(casas[i]->cantidad_integrantes > integrantes_maximos){
			integrantes_maximos = casas[i]->cantidad_integrantes;
			posicion_ganadora = i;
		}
	}

	if(posicion_ganadora != -1)
		printf("\n\n\t\tLa casa %s gobierna Westeros desde el Trono de Hierro\n\n\n", casas[posicion_ganadora]->nombre);
	else
		printf("\n\n\t\tMurieron todos, Westeros ahora es dominada por los caminantes blancos\n\n\n");

}

// pre:
// pos: devuelve TRUE si la casa pierde todos sus integranes, FALSE caso contrario.
bool envejecer_integrantes(casa_t* casa, lista_t* integrantes, int factor){

	if(!integrantes || lista_vacia(integrantes))
		return true;

	size_t* posiciones_a_borrar = malloc(lista_elementos(integrantes) * sizeof(size_t));
	if(!posiciones_a_borrar)
		return false;

	size_t tope = 0;
	size_t i = 0;

	lista_iterador_t* iter = lista_iterador_crear(integrantes);
	while(lista_iterador_tiene_siguiente(iter)){

		integrante_t* persona = lista_iterador_siguiente(iter);
		persona->edad += factor;

		if(persona->edad >= ESPERANZA_VIDA){
			posiciones_a_borrar[tope] = i;
			tope++;
		}
		i++;
	}

	lista_iterador_destruir(iter);

	for(size_t j = 0; j < tope; j++)
		lista_borrar_de_posicion(integrantes, posiciones_a_borrar[j] - j);


	casa->cantidad_integrantes -= tope;
	free(posiciones_a_borrar);
	if(casa->cantidad_integrantes == 0)
		return true;
	

	return false;
}

// pre:
// pos: devuelve TRUE si la casa pierde todos sus integrantes ese año.
bool casa_muere(casa_t* casa){

	if(!casa)
		return true;

	if(envejecer_integrantes(casa, casa->integrantes, casa->factor_envejecimiento))
		return true;

	return false;

}

// pre: anios es positivo
// pos: corre la simulacion, muestra por pantalla a la casa que gobierne el reino.
int simular_juego(juego_t* juego, int anios){

	if(!juego)
		return ERROR;

	if(juego->cantidad_casas == 0){
		printf("\n\n\t\tNo hay casas vivas actualmente\n\n\n");
		return EXITO;
	}

	casa_t** casas = malloc(juego->cantidad_casas * sizeof(casa_t*));
	if(!casas)
		return ERROR;

	casa_t** casas_a_borrar = malloc(juego->cantidad_casas * sizeof(casa_t*));
	if(!casas_a_borrar)
		return ERROR;

	size_t tope_casas = 0;
	arbol_recorrido_inorden(juego->arbol, (void**)casas, (int) juego->cantidad_casas);
	int anios_transcurridos = 0;


	while(anios_transcurridos < anios){

		for (int i = 0; i < juego->cantidad_casas; ++i){
			if(casa_muere(casas[i])){
				if(!casa_ya_esta(casas[i], casas_a_borrar, tope_casas)){
					casas_a_borrar[tope_casas] = casas[i];
					tope_casas++;	
				}
			}
			else
				nacimientos_casas(casas[i]);		
		}

		anios_transcurridos++;
	}

	for(int j = 0; j < tope_casas; j++){
		casa_t* casa_cola = crear_casa(strdup(casas_a_borrar[j]->nombre), 0, 0); 
		cola_encolar(juego->extinguidos, casa_cola);
		arbol_borrar(juego->arbol, casas_a_borrar[j]);
	}
	
	juego->cantidad_casas -= tope_casas;
	mostrar_ganador(juego->arbol, juego->cantidad_casas);
	free(casas);
	free(casas_a_borrar);

	return EXITO;
} 

// pre:
// pos: destruye la estructura casa
void destruir_casa(void* casa){

	if(!casa)
		return;

	free(((casa_t*)casa)->nombre);
	lista_destruir(((casa_t*)casa)->integrantes);
	free(casa);
}

// pre:
// pos: compara la estructura casa
int comparar_casas(void* casa1, void* casa2){

	if(strcmp(((casa_t*)casa1)->nombre, ((casa_t*)casa2)->nombre) == 0)
		return 0;

	if(strcmp(((casa_t*)casa1)->nombre, ((casa_t*)casa2)->nombre) > 0)
		return 1;

	else
		return -1;
}

// pre:
// pos: devuelve un puntero a la estructura juego inicializada, o NULL en caso de error
juego_t* inicializar_juego(){

	juego_t* nuevo_juego = malloc(sizeof(juego_t));
	if(!nuevo_juego)
		return NULL;

	nuevo_juego->arbol = arbol_crear(comparar_casas, destruir_casa);
	if(!nuevo_juego->arbol){
		free(nuevo_juego);
		return NULL;
	}

	nuevo_juego->extinguidos = cola_crear(destruir_casa);
	if(!nuevo_juego->extinguidos){ 
		arbol_destruir(nuevo_juego->arbol);
		free(nuevo_juego);
		return NULL;
	}

	nuevo_juego->cantidad_casas = 0;

	return nuevo_juego;
}

// pre:
// pos: libera la memoria asociada al juego
void destruir_juego(juego_t* juego){

	if(!juego)
		return;

	arbol_destruir(juego->arbol);
	cola_destruir(juego->extinguidos);
	free(juego);
}

// pre: nombre_archivo existe
// pos: agrega las casas e integrantes del archivo dado por nombre_archivo
void agregar_casa(juego_t* juego, char* nombre_archivo){

	if(!juego)
		return;

	FILE* archivo_casas = fopen(nombre_archivo, LECTURA);
	if(!archivo_casas){
		printf("ERROR, dicho archivo no existe!\n");
		return;
	}

	char determinar_caracter;
	int leidos = fscanf(archivo_casas, "%c;", &determinar_caracter);
	casa_t* casa = NULL; 
	casa_t* aux = NULL; 

	while(leidos == 1){

		if(determinar_caracter == 'C'){

			int factor_nacimiento, factor_envejecimiento;
			char nombre_casa[MAX_NOMBRE];

			fscanf(archivo_casas, "%[^;];%i;%i\n", nombre_casa, &factor_envejecimiento, &factor_nacimiento);
			casa = crear_casa(strdup(nombre_casa), factor_envejecimiento, factor_nacimiento);
			aux = arbol_buscar(juego->arbol, casa);

			if(aux == NULL){
				arbol_insertar(juego->arbol, casa);
				juego->cantidad_casas++;
			}
			else{
				free(casa->nombre);
				lista_destruir(casa->integrantes);
				free(casa);
				casa = aux;
			}
		}

		else if(determinar_caracter == 'I'){
			char nombre[MAX_NOMBRE];
			int edad;
			fscanf(archivo_casas, "%[^;];%i\n", nombre, &edad);
			if(casa)
				insertar_miembro(casa, edad);
		}

		leidos = fscanf(archivo_casas, "%c;", &determinar_caracter);
	}

	fclose(archivo_casas);
}

// pre:
// pos: muestra por pantalla las casas extintas en el orden que fueron desapareciendo.
void mostrar_extintos(juego_t* juego){

	if(!juego)
		return;

	cola_t* cola_aux = cola_crear(destruir_casa);
	if(!cola_aux){
		printf("Hubo un error al mostrar las casas extintas!\n");
		return;
	}

	casa_t* aux = cola_primero(juego->extinguidos);
	while(aux){
		casa_t* casa_nueva = crear_casa(strdup(aux->nombre), 0, 0);
		cola_encolar(cola_aux, casa_nueva);
		printf("\n\t\tNombre casa extinta: %s\n", aux->nombre);
		cola_desencolar(juego->extinguidos);
		aux = cola_primero(juego->extinguidos);
	}

	cola_destruir(juego->extinguidos);
	juego->extinguidos = cola_aux;
}

// pre: tope es la cantidad de elementos en el vector
// pos: ordena el vector descendentemente
void sort(casa_t** casas, size_t tope){

	if(!casas)
		return;

	for (int i = 0; i < tope; ++i){
		size_t max = casas[i]->cantidad_integrantes;
		int pos = -1;
		for(int j = i + 1; j < tope; j++){

			if(casas[j]->cantidad_integrantes > max){
				max = casas[j]->cantidad_integrantes;
				pos = j;
			}
		}

		if(pos != -1){
				casa_t* temp = casas[i];
				casas[i] = casas[pos];
				casas[pos] = temp;
		}
	}
}

// pre:
// pos: lista las casas en orden descendente
void listar_casas(juego_t* juego){

	if(!juego)
		return;

	casa_t** casas = malloc(juego->cantidad_casas * sizeof(casa_t*));
	arbol_recorrido_inorden(juego->arbol, (void**)casas, (int) juego->cantidad_casas);
	sort(casas, juego->cantidad_casas);

	for(int i = 0; i < juego->cantidad_casas; i++)
		printf("\n\t\tCantidad de integrantes de la casa %s: %li \n", casas[i]->nombre, casas[i]->cantidad_integrantes);
	
	free(casas);
}

// pre: input es valido
// pos: llama al modo determinado dado el input del usuario
void determinar_modo(char input, juego_t* juego){

	if(input == SIMULAR){
		printf("Ingrese la cantidad de años a simular: \n");
		int anio_simulacion;
		scanf("%i", &anio_simulacion);
		while(anio_simulacion <= 0){
			printf("Numero invalido, ingrese nuevamente\n");
			scanf("%i", &anio_simulacion);
		}

		simular_juego(juego, anio_simulacion);
	}

	else if(input == AGREGAR_CASA){
		char nombre_archivo[MAX_NOMBRE];
		printf("Ingrese la ruta al archivo: \n");
		scanf(" %[^\n]", nombre_archivo);
		agregar_casa(juego, nombre_archivo);
	}

	else if(input == LISTAR)
		listar_casas(juego);
	
	else if(input == EXTINTOS)
		mostrar_extintos(juego);
}

// pre:
// pos: muestra las distintas opciones del programa y toma el input del usuario
void menu(){

	juego_t* juego = inicializar_juego();
	char input;  

	printf("\n\nBienvenido al Juego de Tronos, estos son los comandos para utilizar: \n");
	do{
		printf("\n  - S: Inicia la simulacion, devuelve la casa que controla el Trono de Hierro.\n");
		printf("  - A: Agrega una casa a la simulacion.\n");
		printf("  - L: Lista las casas actuales en orden descendente.\n");
		printf("  - E: Muestra las casas extintas en el orden que fueron desapareciendo.\n");
		printf("  - Q: Finaliza la ejecucion del programa.\n");
		printf("Ingrese un comando:\n");
		scanf(" %c", &input);
		while(input != 'S' && input != 'A' && input != 'L' && input != 'E' && input != 'Q'){
			printf("Comando invalido, ingrese nuevamente: \n");
			scanf(" %c", &input);
		}

		determinar_modo(input, juego);
	}while(input != 'Q');

	destruir_juego(juego);
}