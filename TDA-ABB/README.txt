TDA-ABB
SOBRE LA IMPLEMENTACION

El arbol esta implementado con nodos simplementes enlazados, la estructura arbol cuenta con un puntero al nodo raiz, un comparador y un destructor. La estructura nodo cuenta con un puntero a un nodo izquierdo y otro puntero a un nodo derecho, ademas de un puntero a un elemento. El arbol se ordena bajo el siguiente criterio: Al insertar, si no hay ningun elemento, se inserta como nodo raiz. Luego, una vez que ya se tiene un nodo raiz, los nodos con elementos menores se ordenan del lado izquierdo, mientras que si los nodos cuentan con nodos mayores se ordenan del lado derecho. Al borrar, si el nodo no tiene hijos simplemente se borra ese nodo. Si el nodo a borrar tiene un solo hijo, se borra dicho nodo y la referencia del padre hacia ese nodo borrado se reemplaza por la del hijo del nodo borrado. En caso de que se quiera borrar un nodo con dos hijos, se reemplaza dicho nodo con el menor de los mayores.

PRIMITIVAS

Crear:

La funcion crear inicializa la estructura arbol reservando la memoria adecuada para el. Debe obligatoriamente recibir un puntero a una funcion para comparar los elementos que se desean guardar en el arbol. Ademas, en el caso de que los elementos a guardar se encuentren en memoria dinamica, se pide que se brinde una funcion destructora para liberar dicha memoria a la hora de borrar elementos. Devuelve un puntero al arbol creado, o NULL en caso de que no se haya podido crear. La firma de la funcion es la siguiente:

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor);

Destruir:

La funcion destruir libera toda la memoria asociada al arbol. En caso de que el arbol se encuentre con elementos, los borra. La firma de la funcion es la siguiente:

void arbol_destruir(abb_t* arbol);

Insertar:

La funcion insertar inserta ordenadamente un elemento. En caso de error devuelve -1, y si se ejecuto correctamente devuelve 0. La firma de la funcion es la siguiente:

 int arbol_insertar(abb_t* arbol, void* elemento);

Borrar:

La funcion borrar elimina el elemento pedido del arbol, dejandolo ordenado. Llama a la funcion destructora con el elemento a borrar. Devuelve 0 si se ejecuto correctamente, -1 en caso de error o de que el elemento no exista. La firma de la funcion es la siguiente:

int arbol_borrar(abb_t* arbol, void* elemento);

Buscar:

La funcion buscar devuelve el elemento buscado en caso de que exista dentro del arbol. En caso de que no exista devuelve NULL. La firma de la funcion es la siguiente:

void* arbol_buscar(abb_t* arbol, void* elemento);

Vacio:

La funcion vacio devuelve true en caso de que el arbol no tenga elementos, false en caso contrario. La firma de la funcion es la siguiente:

bool arbol_vacio(abb_t* arbol);

Raiz:

La funcion raiz devuelve el elemento almacenado en el nodo raiz en caso de que exista. Si no existe, devuelve NULL. La firma de la funcion es la siguiente:

void* arbol_raiz(abb_t* arbol);

Recorridos:

Las funciones de los recorridos recorren el arbol en la forma especificada y llenan un array con los elementos del arbol. En caso de que el array se llene, deja de insertar elementos en el. Devuelve la cantidad de elementos insertados. Las firmas de las funciones son las siguientes: 
INORDEN:

int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array);

POSTORDEN:

int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array);

PREORDEN:

int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array);

Con cada elemento:

La funcion con cada elemento recorre el arbol de la forma especificada y llama a la funcion dada con cada elemento, en caso de que la funcion devuelve true, deja de recorrer. El puntero extra se pasa como segundo parametro a la funcion. La firma de la funcion es la siguiente:

void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra);

