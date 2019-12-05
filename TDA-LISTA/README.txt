TDA-LISTA

Implementacion:
La lista esta implementada con nodos simplementes enlazados. La estructura lista cuenta con un puntero al nodo inicial, al nodo final y un contador de la cantidad de nodos presentes en la lista. Cada nodo tiene un elemento y una referencia al siguiente nodo. Se usa esta implementacion para hacer que operaciones como insertar y borrar el primero de la lista tengan complejidad computacional O(1). Ademas, la implementacion nos permite recorrer la lista en el orden en el que estan insertados los elementos en la lista.

Iterador:
Se brinda ademas un iterador externo para poder recorrer la lista. La estructura iterador cuenta con una referencia a la lista y una referencia al nodo actual.

PRIMITIVAS:
Lista:

Crear:

La funcion lista_crear() inicializa la estructura de la lista y devuelve un puntero a dicha estructura. Si hubo un error devuelve NULL. Inicializa la lista sin elementos, y con las referencias al nodo inicio y nodo fin apuntando a NULL. La firma de la funcion es la siguiente:

lista_t* lista_crear();

Destruir:

La funcion lista_destruir() libera toda la memoria asociada a la estructura lista. Si los elementos de la lista no fueron borrados previamente los borra. La firma de la funcion es la siguiente:

void lista_destruir(lista_t* lista);

Insertar:

La funcion lista_insertar() inserta un elemento en la ultima posicion de la lista creando un nuevo nodo. Apunta el nodo fin de la lista al nodo creado. Devuelve 0 si se ejecuto correctamente o -1 en caso contrario. La firma de la funcion es la siguiente:

int lista_insertar(lista_t* lista, void* elemento);

Insertar en posicion:

La funcion lista_insertar_en_posicion() inserta un elemento en la posicion indicada, donde 0 es insertar como primer elemento. En caso de que la posicion indicada sea mayor o igual al tamaño de la lista, la funcion se comporta como lista_insertar(). Devuelve 0 si se ejecuto correctamente, -1 en caso contrario. La firma de la funcion es la siguiente:

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion);

Borrar:

La funcion lista_borrar() borra el ultimo elemento de la lista, liberando la memoria asociada a dicho elemento. Apunta el nodo fin al nodo anterior al borrado. Devuelve 0 si se ejecuto correctamente, -1 en caso contrario. La firma de la funcion es la siguiente:

int lista_borrar(lista_t* lista);

Borrar de posicion:

La funcion lista_borrar_de_posicion() borra el elemento indicado por la posicion, donde 0 es el primer elemento, liberando la memoria asociada. En caso de que la posicion sea mayor o igual a la cantidad de elementos de la lista, la funcion se comporta como lista_borrar(). Devuelve 0 si se ejecuto correctamente, -1 en caso contrario. La firma de la funcion es la siguiente:

int lista_borrar_de_posicion(lista_t* lista, size_t posicion);

Elemento en posicion:

La funcion lista_elemento_en_posicion() devuelve un puntero al elemento en la posicion indicada. Si el elemento no existe devuelve NULL. La firma de la funcion es la siguiente:

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion)

Ultimo:

La funcion lista_ultimo() devuelve un puntero al ultimo elemento de la lista. Devuelve NULL si la lista esta vacia. La firma de la funcion es la siguiente:

void* lista_ultimo(lista_t* lista)

Vacia:

La funcion lista_vacia() devuelve true si la lista esta vacia o es nula. False en caso contrario. La firma de la funcion es la siguiente:

bool lista_vacia(lista_t* lista)

Elementos:

La funcion lista_elementos() devuelve la cantidad de elementos que tiene la lista. Devuelve 0 si es nula. La firma de la funcion es la siguiente:

size_t lista_elementos(lista_t* lista)

Destruir:

La funcion lista_destruir() libera toda la memoria asociada a la lista. La firma de la funcion es la siguiente:

void lista_destruir(lista_t* lista)

Con cada elemento:

La funcion lista_con_cada_elemento() recorre toda la lista e invoca a la funcion con dicho elemento para todo elemento. La firma de la funcion es la siguiente:

void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*))

Iterador Externo:
Crear:

La funcion lista_iterador_crear() crea un iterador asociado a la lista indicada. El iterador es valido mientras no se modifique la lista. Asigna el nodo corriente como NULL inicialmente. Devuelve NULL si la lista tambien es NULL. La firma de la funcion es la siguiente:

lista_iterador_t* lista_iterador_crear(lista_t* lista)

Tiene Siguiente:

La funcion lista_iterador_tiene_siguiente() devuelve true si el siguiente del corriente no es NULL. En caso de que corriente sea NULL, devuelve true si la lista no esta vacia y false en caso de que lo este. La firma de la funcion es la siguiente:

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador)

Siguiente:

La funcion lista_iterador_siguiente() avanza el corriente al siguiente nodo en caso de que haya siguiente. En caso de que corriente sea NULL, lo avanza al primer nodo de la lista. Devuelve un puntero al elemento del nodo despues de avanzar. La firma de la funcion es la siguiente:

void* lista_iterador_siguiente(lista_iterador_t* iterador)

Destruir:

La funcion lista_iterador_destruir() libera toda la memoria asociada al iterador. La firma de la funcion es la siguiente:

void lista_iterador_destruir(lista_iterador_t* iterador)


Compilacion:
Se brinda un makefile para facilitar la compilacion del TDA. El makefile tiene 3 comandos:

compile:
Compila los archivos con la siguiente linea: gcc -std=c99 -Wall -Werror -Wconversion -pedantic -Wtype-limits -g test.c pruebas.c lista.c -o prueba_vd

test:
Ejecuta las pruebas del archivo test.c

valgrind:
ejecuta la prueba de perdida de memoria sobre el archivo test.c

