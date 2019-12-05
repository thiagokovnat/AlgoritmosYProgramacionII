#include "hash.h"
#include "hash_iterador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pruebas.h"

int main(){

  test_hash_nulos();
  test_insercion_borrado_busqueda();
  test_iterador();
  print_count();
}