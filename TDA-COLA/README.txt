TDA-COLA:

    Se incluyen en el zip los siguientes archivos: 1) cola.h, es la biblioteca para la cola, incluye las primitivas de la cola. 2) cola.c, es la implementacion de cola.h (vease --FUNCIONES DE LA COLA--) 3) pruebas.h, biblioteca que incluye las primitivas de las pruebas. 4) pruebas.c, implementacion de las pruebas en pruebas.h (vease --PRUEBAS--) 5) minipruebas_cola.c, lote de pruebas proveidas por la catedra. 5) makefile, archivo que contiene comandos para la compilacion (vease --compilacion--)

FUNCIONES DE LA COLA:

 1) Crear:
    La funcion cola_crear() devuelve un puntero a la estructura cola inicializada. Inicializa la cola con los punteros al nodo inicio y nodo fin en NULL, y la cantidad en 0. En caso de que no pueda crear la cola, devuelve NULL. La firma de la funcion es la siguiente:

cola_t* cola_crear();

 2) Encolar
    La funcion cola_encolar() encola el elemento recibido dentro de un nuevo nodo de la cola. Devuelve 0 si pudo encolar,  -1 si hubo un error. La firma de la funcion es la siguiente:

int cola_encolar(cola_t* cola, void* elemento);

3) Desencolar
    La funcion cola_desencolar() desencola el primer nodo de la cola. Devuelve 0 si pudo desencolar correctamente, -1 en caso contrario. La firma de la funcion es la siguiente:

int cola_desencolar(cola_t* cola);

4) Primero
    La funcion cola_primero() devuelve un puntero al primer elemento dentro del primer nodo de la cola. En caso de que la cola este vacía devuelve NULL.
La firma de la funcion es la siguiente:

void* cola_primero(cola_t* cola);

5) Vacia
    La funcion cola_vacia() devuelve TRUE en caso de que la cola este vacia (o sea nula) y FALSE en caso contrario. La firma de la funcion es la siguiente:

bool cola_vacia(cola_t* cola);

6) Cantidad
    La funcion cola_cantidad() devuelve la cantidad de nodos que posee la cola. Devuelve -1 si hubo un error y 0 si la cola es nula o esta vacia. La firma de la funcion es la siguiente:

int cola_cantidad(cola_t* cola);

7) Destruir
    La funcion cola_destruir() destruye la estructura de la cola y libera toda la memoria asociada a ella. La firma de la funcion es la siguiente:

void cola_destruir(cola_t* cola);



COMPILACIÓN:

    Se debe compilar con la siguiente linea de compilacion:

gcc test.c pruebas.c cola.c -o cola_vd -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

    Igualmente, se brinda un makefile el cual puede simplificar las tareas de compilacion y chequeo de perdida de memoria. Dentro de dicho archivo se incluyen los siguientes comandos:

1) Compile
    Compila los archivos.  Se ejecuta con la siguiente linea:

make compile

2) Test
    Ejecuta las pruebas proveidas en el archivo test. Se ejecuta con la siguiente linea:

make test

3) Valgrind
    Corre las pruebas relacionadas a la perdida de memoria.  Se ejecuta con la siguiente linea:

make valgrind


PRUEBAS:
    
    Se incluye una biblioteca llamada pruebas.h, con su debida implementacion en pruebas.c. Dicho archivo contiene un lote de pruebas que contemplan los casos limite del funcionamiento de la cola. Esto es, pruebas sobre colas vacias y colas nulas. Ademas, se prueban los casos intermedios y mas cotidianos del uso de la cola: encolamiento y desencolamiento en volumenes de distintos tamaños. En el caso de que se quieran añadir pruebas propias, pueden crear una nueva biblioteca que añada las pruebas que se crea necesarias. Luego, en un archivo nuevo se incluye dicha biblioteca (y si lo desean la biblioteca prueba.h que se incluye) y se llama a las funciones pruebas que deseen dentro del main de dicho archivo. Sin embargo, si solo se desea correr las pruebas que se incluyen, basta con hacer uso del makefile (vease --compilacion, 2) TEST--)
