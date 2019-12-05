Trabajo Practico N2 - Juego de Tronos:

Sobre como utilizarlo:
     Se incluye dentro del .zip el archivo juego_de_tronos.h, para utilizar el simulador, basta con crear un archivo .c e incluir dicha biblioteca. Dentro del main del archivo llamar a la funcion menu() incluida en la biblioteca. Esta funcion se encargara de tomar el input del usuario, procesarlo y llamar a las funciones que corren el modo deseado por el usuario.

Sobre la implementacion: 
    El trabajo practico utiliza las estructuras de la lista, cola y abb implementados previamente. Se agrego un destructor para la cola y la lista por cuestiones de simplicidad a la hora de implementar la simulacion. A pesar de que los archivos de las casas poseen un nombre para cada integrante de las casas, decidi no utilizarlo dentro de la implementacion del struct integrante, dado que en ningun momento del trabajo practico se utiliza el nombre del integrante. Sin embargo, en el caso de que en un futuro se quisiera implementar una funcion que utilize el nombre, basta con agregar un char* nombre dentro del struct integrante y agregarle un parametro a la funcion que crea un integrante que represente el nombre de dicho integrante. El vector que se crea en la linea 144 es creado en memoria dinamica dado que, si no fuese asi, para numeros de integrantes muy altos habria Stack Overflow por crear un vector de tamaño muy grande. Lo mismo para los vectores de la linea 205 y 209 y 425.

Sobre su uso:

    SIMULAR:
        Se llama con la letra S, simula el paso del tiempo dentro del reino. Pide al usuario que ingrese la cantidad de años a simular. Luego de que se complete la simulacion (Dependiendo la cantidad de integrantes de cada casa y sus factores, el tiempo de ejecucion de esta funcion puede variar) informa al usuario que casa es la que tiene mayor cantidad de integrantes (La que gobierna el reino).

    AGREGAR:
        Se llama con la letra A, le pide al usuario que ingrese la ruta a un archivo que contenga las casas a agregar a la simulacion con sus correspondientes factores e integrantes. Se pide que el archivo este en formato csv en la siguiente forma: C;Nombre Casa;Factor Envejecimiento; Factor Nacimiento (Para las casas) Luego, si la casa tiene integrantes se deben listar de la siguiente manera: I;Nombre Integrante;Edad.  Si el nombre del archivo no existe, o hubo un error al leer el archivo, se lo informa al usuario.
    
    LISTAR:
        Se llama con la letra L, lista todas las casas del reino en orden descendente de cantidad de integrantes.

    EXTINTOS:
        Se llama con la letra E, le muestra al usuario las casas que se extinguieron durante la ejecucion de la simulacion en el orden en las que fueron desapareciendo. En caso de error, se lo informa al usuario.


