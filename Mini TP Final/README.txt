MINI TP Final: Reimplementar una lista utilizando unicamente la estructura pila.

Sobre la implementacion:
    La lista esta implementada utilizando unicamente la estructura de la pila. Se utlizo la estructura de la pila implementada previamente, por lo que los casos limites de dicha estructura estan contemplados en su implementacion. En cuanto a decisiones personales a la hora de implementar la lista, decidi utilizar lo mas posible la estructura de la pila. Es decir, por mas que habia casos en los que podria haber utilizado un vector (Por ejemplo, para guardar temporalmente elementos), decidi utilizar una pila dado que era el objetivo del trabajo practico. Esto se puede ver en la implementacion de la insercion y borrado en una posicion especifica. En los casos en los que si utilizo vectores, los creo en memoria dinamica. Tome esta decision dado que, en el caso de que posea una cantidad de elementos muy grande, si no lo crease en el heap tendria Stack Overflow por el tamaño de dicho vector.
    El iterador externo tambien esta implementado utilizando la estructura de la pila. Esta pila esta en el orden inverso de la pila original de la lista. Esto facilita el chequeo de si tiene siguiente o devolver el proximo elemento, dado que las primitivas de la pila permiten acceder al ultimo elemento, desapilarlo y saber si dicha pila esta vacia o no.
    

Sobre la compilacion:
    Dentro del .zip se incluye un makefile el cual contiene 3 comandos: Compile, Test y Valgrind. Compile, como dice su nombre, simplemente compila el trabajo con los flags determinados por CFLAGS del makefile. El comando Test corre las pruebas incluidas en la biblioteca pruebas.h. Por ultimo, el comando Valgrind corre las mismas pruebas del comando Test pero con los chequeos de perdida y accesos invalidos de memoria correspondientes.


PRIMITIVAS:

    Crear: Inicializa la estructura de la lista, llamando a la funcion pila_crear() para inicializar la estructura de la pila que se utiliza dentro de la lista. Devuelve NULL en caso de error. En caso de que se ejecute correctamente, devuelve un puntero a la estructura inicializada.

    Insertar: Inserta el elemento dado (Puede ser un elemento NULL) en la ultima posicion de la lista. Utiliza la primitiva pila_apilar. Devuelve 0 si se ejecuto correcamente, -1 caso contrario.

    Insertar en posicion: Inserta el elemento dado (Puede ser un elemento NULL) en la posicion dada, donde 0 es insertar como primer elemento. Si la posicion es mayor a la cantidad de elementos actualmente almacenados en la lista, inserta en la ultima posicion. Utiliza la primitiva pila_apilar() y una pila auxiliar.

    Borrar: Borra el ultimo elemento de la lista, utilizando la primitiva pila_desapilar().

    Borrar de posicion: Borra el elemento en la posicion dada, donde 0 es borrar el primer elemento. Si la posicion es mayor a la cantidad de elementos almacenados actualmente en la lista, se borra la ultima posicion. Utiliza la primitiva pila_desapilar y una pila auxiliar.

    Elemento en posicion: Devuelve el elemento en la posicion dada, donde 0 es el primer elemento. Si la posicion es mayor a la cantidad de elementos almacenados actualmente, devuelve NULL. Utiliza una pila auxiliar.

    Ultimo: Devuelve el ultimo elemento de la lista, NULL si esta vacia. Utiliza la estructura pila_tope.

    Vacia: Devuelve true si la lista esta vacia o es nula. Utiliza la primitiva pila_vacia.

    Elementos: Devuelve la cantidad de elementos actualmente almacenados en la lista, 0 en caso de que sea nula. Utiliza la primitiva pila_cantidad.

    Destruir: Libera toda la memoria asociada a la estructura de la lista y de la pila. Utiliza la primitiva pila_destruir.

ITERADOR EXTERNO:

    Crear: Inicializa la estructura del iterador, reservando la memoria necesaria para el. Utiliza una pila que contiene los elementos de la lista en orden inverso. Devuelve un puntero a la estructura inicializada o NULL en caso de error.

    Tiene siguiente: Devuelve true si hay elementos por recorrer con el iterador. Utiliza la estructura pila_vacia.

    Siguiente: Devuelve el proximo elemento en la lista en caso de que no este vacia. Si esta vacia, devuelve NULL. Utiliza la primitiva pila_desapilar y pila_tope.

    Destruir: Libera la memoria asociada a la estructura del iterador y de la pila que utiliza. Usa la primitiva pila_destruir.
