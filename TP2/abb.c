#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "abb.h"

#define ERROR -1
#define EXITO 0

/*
 * Crea el arbol y reserva la memoria necesaria de la estructura.
 * Comparador se utiliza para comparar dos elementos.
 * Destructor es invocado sobre cada elemento que sale del arbol,
 * puede ser NULL indicando que no se debe utilizar un destructor.
 *
 * Devuelve un puntero al arbol creado o NULL en caso de error.
 */
abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){

	if(!comparador)
		return NULL;

	abb_t* abb = malloc(sizeof(abb_t));
	if(!abb)
		return NULL;

	abb->nodo_raiz = NULL;
	abb->comparador = comparador;
	abb->destructor = destructor;

	return abb;
}

// pre:
// pos: crea un nodo con referencia a sus hijos como NULL, inserta el elemento en el y devuelve un puntero a dicho nodo. Devuelve NULL si hubo error.
nodo_abb_t* crear_nodo(void* elemento){

	nodo_abb_t* nodo = malloc(sizeof(nodo_abb_t));
	if(!nodo)
		return NULL;

	nodo->elemento = elemento;
	nodo->izquierda = NULL;
	nodo->derecha = NULL;

	return nodo;
}


// pre:
// pos: devuelve 0 si el puntero al nodo es distinto de NULL, -1 en caso contrario.
int comprobar_insercion(nodo_abb_t* nodo){

	if(!nodo)
		return ERROR;

	return EXITO;
}


// pre: comparador no es NULL. Raiz es la referencia al nodo actual.
// pos: inserta un elemento en el arbol ordenadamente, los elementos mas chicos iran a la izquierda y los mas grandes a la derecha para todo nodo.
int arbol_insertar_recursivo(nodo_abb_t** raiz, void* elemento, abb_comparador comparador){

	if(!comparador)
		return ERROR;

	if(!(*raiz)){
 		(*raiz) = crear_nodo(elemento);
 		return comprobar_insercion((*raiz));
 	}

	if(comparador((*raiz)->elemento, elemento) > 0){

		if(!(*raiz)->izquierda){
			(*raiz)->izquierda = crear_nodo(elemento);
			return comprobar_insercion((*raiz)->izquierda);
		}
		else
			return arbol_insertar_recursivo(&(*raiz)->izquierda, elemento, comparador);
	}

	else{

		if(!(*raiz)->derecha){
			(*raiz)->derecha = crear_nodo(elemento);
			return comprobar_insercion((*raiz)->derecha);
		}
		else
			return arbol_insertar_recursivo(&(*raiz)->derecha, elemento, comparador);

	}
}

/*
 * Inserta un elemento en el arbol.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 * El arbol admite elementos con valores repetidos.
 */
 int arbol_insertar(abb_t* arbol, void* elemento){

 	if(!arbol)
 		return ERROR;

 	return arbol_insertar_recursivo(&arbol->nodo_raiz, elemento, arbol->comparador);
 }



 // pre: padre es la referencia al nodo actual.
 // pos: devuelve un puntero al nodo mas izquierdo (el de clave mas pequeña) y asigna al padre la referencia al hijo derecho del nodo mas chico.
 nodo_abb_t* obtener_minimo(nodo_abb_t* nodo, nodo_abb_t** padre){

 	if(!nodo)
 		return NULL;

 	if(!nodo->izquierda){
 		(*padre) = nodo->derecha; // Si no tiene hijo derecho, asignaria NULL.
 		return nodo;
 	}


 	return obtener_minimo(nodo->izquierda, &nodo->izquierda);
 }

 // pre: comparador no es NULL. Padre es la referencia al nodo actual.
 // pos: borra el nodo que contiene a elemento. Deja el arbol ordenado.
  int arbol_borrar_recursivo(nodo_abb_t* nodo, void* elemento, abb_comparador comparador, abb_liberar_elemento destructor, nodo_abb_t** padre){

  	if(!comparador || !nodo)
  		return ERROR;

  	if(comparador(nodo->elemento, elemento) > 0)
  		return arbol_borrar_recursivo(nodo->izquierda, elemento, comparador, destructor, &nodo->izquierda);

  	if(comparador(nodo->elemento, elemento) < 0)
 		return arbol_borrar_recursivo(nodo->derecha, elemento, comparador, destructor, &nodo->derecha);


 	nodo_abb_t* nodo_a_borrar = nodo;

 	if(!nodo_a_borrar->derecha && !nodo_a_borrar->izquierda){ 
 		(*padre) = NULL;
 		destructor(nodo_a_borrar->elemento);
 		free(nodo_a_borrar);
 	}

 	else if(!nodo_a_borrar->izquierda || !nodo_a_borrar->derecha){ 

 		if(!nodo_a_borrar->izquierda){
 			(*padre) = nodo_a_borrar->derecha;
 			destructor(nodo_a_borrar->elemento);
 			free(nodo_a_borrar);
 		}

 		else{
 			(*padre) = nodo_a_borrar->izquierda;
 			destructor(nodo_a_borrar->elemento);
 			free(nodo_a_borrar);
 		}
 	}

 	else if(nodo_a_borrar->izquierda != NULL && nodo_a_borrar->derecha != NULL){ 

 		nodo_abb_t* aux = obtener_minimo(nodo_a_borrar->derecha, &nodo_a_borrar->derecha);
 		(*padre) = aux;
 		aux->derecha = nodo_a_borrar->derecha;
 		aux->izquierda = nodo_a_borrar->izquierda;

 		if(aux->derecha == aux)
 			aux->derecha = NULL;

 		if(aux->izquierda == aux)
 			aux->izquierda = NULL;

 		destructor(nodo_a_borrar->elemento);
 		free(nodo_a_borrar);
 	}

 	return EXITO;
  }

 /*
  * Busca en el arbol un elemento igual al provisto (utilizando la
  * funcion de comparación) y si lo encuentra lo quita del arbol.
  * Adicionalmente, si encuentra el elemento, invoca el destructor con
  * dicho elemento.
  * Devuelve 0 si pudo eliminar el elemento o -1 en caso contrario.
  */
 int arbol_borrar(abb_t* arbol, void* elemento){

 	if(!arbol)
 		return ERROR;

 	return arbol_borrar_recursivo(arbol->nodo_raiz, elemento, arbol->comparador, arbol->destructor, &arbol->nodo_raiz);

 }

// pre: comparador no es NULL.
// pos: devuelve el elemento buscado en caso de que este en el arbol, NULL en caso contrario.
void* arbol_buscar_recursivo(nodo_abb_t* raiz, void* elemento, abb_comparador comparador){

	if(!comparador)
		return NULL;

	if(!raiz)
		return NULL;

	if(comparador(raiz->elemento, elemento) > 0)
		return arbol_buscar_recursivo(raiz->izquierda, elemento, comparador);

	else if(comparador(raiz->elemento, elemento) < 0)
		return arbol_buscar_recursivo(raiz->derecha, elemento, comparador);

	else
		return raiz->elemento;
}

/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación).
 *
 * Devuelve el elemento encontrado o NULL si no lo encuentra.
 */
void* arbol_buscar(abb_t* arbol, void* elemento){

	if(!arbol || !arbol->nodo_raiz)
		return NULL;

	return arbol_buscar_recursivo(arbol->nodo_raiz, elemento, arbol->comparador);
}

/*
 * Devuelve el elemento almacenado como raiz o NULL si el árbol está
 * vacío.
 */
void* arbol_raiz(abb_t* arbol){

	if(!arbol || !arbol->nodo_raiz)
		return NULL;

	return arbol->nodo_raiz->elemento;
}


/*
 * Determina si el árbol está vacío.
 * Devuelve true si lo está, false en caso contrario.
 */
bool arbol_vacio(abb_t* arbol){

	if(!arbol || !arbol->nodo_raiz)
		return true;

	return false;
}


// pre:
// pos: recorre el arbol inorden y va llenando el array con los elementos, en caso de que no entren mas elementos deja de insertar.
void recorrido_inorden_recursivo(nodo_abb_t* nodo, void** array, int tamanio_array, int* elementos_insertados){

	if(!nodo || !array)
		return;

	if(nodo->izquierda)
		recorrido_inorden_recursivo(nodo->izquierda, array, tamanio_array, elementos_insertados);

	if((*elementos_insertados < tamanio_array)){

		array[(*elementos_insertados)] = nodo->elemento;
		(*elementos_insertados)++;
	}

	if(nodo->derecha)
		recorrido_inorden_recursivo(nodo->derecha, array, tamanio_array, elementos_insertados);

}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia inorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){

	if(!arbol || !array)
		return 0;

	int insertados = 0;
	recorrido_inorden_recursivo(arbol->nodo_raiz, array, tamanio_array, &insertados);
	return insertados;
}


// pre:
// pos: recorre el arbol preorden y va llenando el array con los elementos, en caso de que no entren mas elementos deja de insertar.
void recorrido_preorden_recursivo(nodo_abb_t* nodo, void** array, int tamanio_array, int* elementos_insertados){

	if(!nodo || !array)
		return;

	if((*elementos_insertados < tamanio_array)){

		array[(*elementos_insertados)] = nodo->elemento;
		(*elementos_insertados)++;
	}

	if(nodo->izquierda)
		recorrido_preorden_recursivo(nodo->izquierda, array, tamanio_array, elementos_insertados);

	if(nodo->derecha)
		recorrido_preorden_recursivo(nodo->derecha, array, tamanio_array, elementos_insertados);

}
/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia preorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array){

	if(!arbol || !array)
		return 0;

	int insertados = 0;
	recorrido_preorden_recursivo(arbol->nodo_raiz, array, tamanio_array, &insertados);
	return insertados;
}

// pre:
// pos: recorre el arbol postorden y va llenando el array con los elementos, en caso de que no entren mas elementos deja de insertar.
void recorrido_postorden_recursivo(nodo_abb_t* nodo, void** array, int tamanio_array, int* elementos_insertados){

	if(!nodo || !array)
		return;

	if(nodo->izquierda)
		recorrido_postorden_recursivo(nodo->izquierda, array, tamanio_array, elementos_insertados);

	if(nodo->derecha)
		recorrido_postorden_recursivo(nodo->derecha, array, tamanio_array, elementos_insertados);

	if((*elementos_insertados < tamanio_array)){

		array[(*elementos_insertados)] = nodo->elemento;
		(*elementos_insertados)++;
	}
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia postorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array){

	if(!arbol || !array)
		return 0;

	int insertados = 0;
	recorrido_postorden_recursivo(arbol->nodo_raiz, array, tamanio_array, &insertados);
	return insertados;
}


// pre:
// pos: borra todos los nodos del arbol.
void vaciar_arbol(abb_t* abb){

	if(!abb)
		return;

	while(!arbol_vacio(abb))
		arbol_borrar(abb, arbol_raiz(abb));
}

/*
 * Destruye el arbol liberando la memoria reservada por el mismo.
 * Adicionalmente invoca el destructor con cada elemento presente en
 * el arbol.
 */
void arbol_destruir(abb_t* arbol){

	if(!arbol)
		return;

	if(arbol->nodo_raiz)
		vaciar_arbol(arbol);
	

	free(arbol);
}

// pre:
// pos: recorre el arbol preorden, si la funcion devuelve true se deja de recorrer el arbol.
void preorden_cada_elemento(nodo_abb_t* nodo,  bool (*funcion)(void*, void*), void* extra, bool* estado){

	if(!nodo || !funcion)
		return;

	if(!(*estado) && funcion(nodo->elemento, extra)){
		(*estado) = true;
		return;
	}

	if(!(*estado))
		preorden_cada_elemento(nodo->izquierda, funcion, extra, estado);

	if(!(*estado))
		preorden_cada_elemento(nodo->derecha, funcion, extra, estado);

}

// pre:
// pos: recorre el arbol postorden, si la funcion devuelve true se deja de recorrer el arbol.
void postorden_cada_elemento(nodo_abb_t* nodo,  bool (*funcion)(void*, void*), void* extra, bool* estado){

	if(!nodo || !funcion )
		return;

	if(!(*estado))
		postorden_cada_elemento(nodo->izquierda, funcion, extra, estado);

	if(!(*estado))
		postorden_cada_elemento(nodo->derecha, funcion, extra, estado);

	if(!(*estado) && funcion(nodo->elemento, extra)){
		(*estado) = true;
		return;
	}

}

// pre:
// pos: recorre el arbol inorden, si la funcion devuelve true se deja de recorrer el arbol.
void inorden_cada_elemento(nodo_abb_t* nodo,  bool (*funcion)(void*, void*), void* extra, bool* estado){

	if(!nodo || !funcion)
		return;

	if(!(*estado))
		inorden_cada_elemento(nodo->izquierda, funcion, extra, estado);

	if(!(*estado) && funcion(nodo->elemento, extra)){
		(*estado) = true;
		return;
	}

	if(!(*estado))
		inorden_cada_elemento(nodo->derecha, funcion, extra, estado);

}

/*
 * Iterador interno. Recorre el arbol e invoca la funcion con cada
 * elemento del mismo. El puntero 'extra' se pasa como segundo
 * parámetro a la función. Si la función devuelve true, se finaliza el
 * recorrido aun si quedan elementos por recorrer. Si devuelve false
 * se sigue recorriendo mientras queden elementos.
 * El recorrido se realiza de acuerdo al recorrido solicitado.  Los
 * recorridos válidos son: ABB_RECORRER_INORDEN, ABB_RECORRER_PREORDEN
 * y ABB_RECORRER_POSTORDEN.
*/
void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){

	if(!arbol || !funcion)
		return;

	bool estado = false;

	if(recorrido == ABB_RECORRER_INORDEN)
		inorden_cada_elemento(arbol->nodo_raiz, funcion, extra, &estado);

	else if(recorrido == ABB_RECORRER_POSTORDEN)
		postorden_cada_elemento(arbol->nodo_raiz, funcion, extra, &estado);

	else if(recorrido == ABB_RECORRER_PREORDEN)
		preorden_cada_elemento(arbol->nodo_raiz, funcion, extra, &estado);

}
