TDA-PILA:

    Se incluyen en el zip los siguientes archivos: 1) pila.h, es la biblioteca para la pila, incluye las primitivas de la pila. 2) pila.c, es la implementacion de pila.h (vease --FUNCIONES DE LA PILA--) 3) pruebas.h, biblioteca que incluye las primitivas de las pruebas. 4) pruebas.c, implementacion de las pruebas en pruebas.h (vease --PRUEBAS--) 5) minipruebas_pila_vd.c, lote de pruebas proveidas por la catedra. 5) makefile, archivo que contiene comandos para la compilacion (vease --COMPILACION--)

FUNCIONES DE LA PILA:

 1) Crear:
    La funcion pila_crear() devuelve un puntero a la estructura pila inicializada. Inicializa la pila con un tamaño para 10 elementos y el tope en 0. En caso de que no pueda crear la pila, devuelve NULL. La firma de la funcion es la siguiente:

pila_t* pila_crear();

 2) Apilar
    La funcion pila_apilar() apila el elemento recibido dentro del vector elementos de la pila. Si la pila se llena, el tamaño de la pila se duplica. Devuelve 0 si pudo apilar,  -1 si hubo un error. La firma de la funcion es la siguiente:

int pila_apilar(pila_t* pila, void* elemento);

3) Desapilar
    La funcion pila_desapilar() desapila el ultimo elemento del vector elementos de la pila. En caso de que al desapilar el vector quede en un 50% lleno, el tamaño del mismo se reducirá a la mitad. Devuelve 0 si pudo desapilar correctamente, -1 en caso contrario. La firma de la funcion es la siguiente:

int pila_desapilar(pila_t* pila);

4) Tope
    La funcion pila_tope() devuelve un puntero al ultimo elemento contenido dentro del vector elementos de la pila. En caso de que la pila este vacía devuelve **NULL**.
La firma de la funcion es la siguiente:

void* pila_tope(pila_t* pila);

5) Vacia
    La funcion pila_vacia() devuelve TRUE en caso de que la pila este vacia (o sea nula) y FALSE en caso contrario. La firma de la funcion es la siguiente:

bool pila_vacia(pila_t* pila);

6) Cantidad
    La funcion pila_cantidad() devuelve la cantidad de elementos actualmente almazenados en el vector de elementos de la pila. Devuelve -1 si hubo un error y 0 si la pila es nula. La firma de la funcion es la siguiente:

int pila_cantidad(pila_t* pila);

7) Destruir
    La funcion pila_destruir() destruye la estructura de la pila y libera toda la memoria asociada a ella. La firma de la funcion es la siguiente:

void pila_destruir(pila_t* pila);



COMPILACIÓN:

    Se debe compilar con la siguiente linea de compilacion:

gcc test.c pruebas.c pila.c -o pila_vd -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

    Igualmente, se brinda un *makefile* el cual puede simplificar las tareas de compilacion y chequeo de perdida de memoria. Dentro de dicho archivo se incluyen los siguientes comandos:

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
    
    Se incluye una biblioteca llamada pruebas.h, con su debida implementacion en pruebas.c. Dicho archivo contiene un lote de pruebas que contemplan los casos limite del funcionamiento de la pila. Esto es, pruebas sobre pilas vacias y pilas nulas. Ademas, se prueban los casos intermedios y mas cotidianos del uso de la pila: apilamiento y desapilamiento en volumenes de distintos tamaños. En el caso de que se quieran añadir pruebas propias, pueden crear una nueva biblioteca que añada las pruebas que se crea necesarias. Luego, en un archivo nuevo se incluye dicha biblioteca (y si lo desean la biblioteca prueba.h que se incluye) y se llama a las funciones pruebas que deseen dentro del main de dicho archivo. Sin embargo, si solo se desea correr las pruebas que se incluyen, basta con hacer uso del makefile (vease --COMPILACION, 2) TEST--)
