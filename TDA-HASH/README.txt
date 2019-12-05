TDA HASH:
El hash esta implementado usando un sistema de resolucion de colisiones de estilo abierto, usando la estructura de la lista para esto. El usuario se hara responsable de la alocacion de memoria para el elemento asociado a la clave. Sin embargo, la implementacion permite utilizar un destructor para liberar la memoria asociada a dicho elemento en caso de que asi se quiera. El hash utiliza un factor de rehasheo de 3, dado que al ser implementacion de estilo abierta, la operacion no es tan critica. Sin embargo, se hace para evitar una degeneracion de complejidad temporal a O(n) y mantener, en lo posible, una busqueda e insercion lo mas cercano a O(1).


PRIMITIVAS:

HASH CREAR:  hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad)
Inicializa la estructura del hash, reservando la memoria necesaria para dicha estructura. Devuelve un puntero a la estructura inicializada o devuelve NULL en caso de error.

HASH INSERTAR:  int hash_insertar(hash_t* hash, const char* clave, void* elemento)
Inserta un elemento con la clave dada y el elemento asociado a ella. En caso de que la clave ya exista, libera el elemento previo y asocia el nuevo a la clave. Devuelve 0 si se ejecuto correctamente, -1 caso contrario.

HASH QUITAR:  int hash_quitar(hash_t* hash, const char* clave)
Libera el elemento asociado a la clave dada. Devuelve 0 si se ejecuto correctamente, -1 en caso de error.

HASH CONTIENE:  bool hash_contiene(hash_t* hash, const char* clave)
Devuelve TRUE en caso de que exista un elemento en el hash con la clave dada, FALSE en caso contrario.

HASH OBTENER:   void* hash_obtener(hash_t* hash, const char* clave)
Devuelve el elemento asociado a la clave dada. En caso de error o de que no exista dicho elemento, devuelve NULL.

HASH CANTIDAD:  size_t hash_cantidad(hash_t* hash)
Devuelve la cantidad de elementos almacenados actualmente en el hash. En caso de que el hash sea NULL, devuelve 0.

HASH DESTRUIR:  void hash_destruir(hash_t* hash)
Libera toda la memoria asociada al hash.


ITERADOR EXTERNO
Ademas, se brinda un iterador externo para recorrer la estructura hash.

PRIMITIVAS ITERADOR:

ITERADOR CREAR: hash_iterador_t* hash_iterador_crear(hash_t* hash)
Inicializa la estructura del iterador, reservando la memoria necesaria para dicha estructura. Devuelve un puntero a la estructura inicializada o NULL en caso de error. 

ITERADOR TIENE SIGUIENTE:   bool hash_iterador_tiene_siguiente(hash_iterador_t* iterador)
Devuelve TRUE si todavia hay elementos por recorrer en el hash. FALSE en caso contrario o de error.

ITERADOR SIGUIENTE: void* hash_iterador_siguiente(hash_iterador_t* iterador)
Devuelve la proxima clave almacenada en el hash. Devuelve NULL en caso de error o si no habia mas claves.

ITERADOR DESTRUIR:  void hash_iterador_destruir(hash_iterador_t* iterador)
Libera toda la memoria asociada a la estructura del iterador.

