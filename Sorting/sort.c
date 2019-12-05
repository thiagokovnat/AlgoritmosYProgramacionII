#include "sort.h"
#include <stdio.h>


void merge(void** v,int inicio1, int fin1, int fin2, int (*es_menor)(void*, void*)){
 
  int inicio2 = fin1 + 1;
  
  while(inicio1 <= fin1 && inicio2 <= fin2){

    if(es_menor(v[inicio1], v[inicio2]))
      inicio1++;

    else{

      void* aux = v[inicio2];
      for(int i = inicio2; i > inicio1; i--)
	       v[i] = v[i - 1];

      v[inicio1] = aux;
      inicio1++;
      inicio2++;
      fin1++;
    }
  }
}

void mergeSort_interno(void** vector,int inicio, int fin, int (*es_menor)(void*, void*)){

  if(inicio == fin)
    return;
  
  int medio = (fin + inicio)/2;
  mergeSort_interno(vector, inicio, medio, es_menor);
  mergeSort_interno(vector, medio + 1, fin, es_menor);
  merge(vector, inicio, medio, fin, es_menor);
}

// pre: cantidad es la cantidad de elementos del array, es_menor es funcion comparadora
// pos: ordena el vector ascendentemente
void mergeSort(void** array, int cantidad, int (*es_menor)(void*, void*)){
	mergeSort_interno(array, 0, cantidad-1, es_menor);
}

// pre:
// pos: intercambia los contenidos de los apuntados por a y b
void swap(int* a, int* b){ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
  
// pre: inicio es pos inicial, fin la final
// pos: deja al pivote en la posicion correcta, ordena a los menores a el a la izquierda, mayores a la derecha
int pivotear(int arr[], int inicio, int fin){ 

    int pivote = arr[fin];    
    int i = (inicio - 1);  
  	

    for (int j = inicio; j <= fin - 1; j++){ 
   
        if (arr[j] < pivote){ 
            i++;    
            swap(&arr[i], &arr[j]); 
        } 
    } 

    swap(&arr[i + 1], &arr[fin]); 
    return (i + 1); 
} 
  
// pre: inicio es la primera pos del array, fin es la ultima
// pos: ordena el vector ascendentemente
void quickSort(int arr[], int inicio, int fin) { 

    if (inicio < fin){ 

        int pivote = pivotear(arr, inicio, fin); 
        quickSort(arr, inicio, pivote - 1); 
        quickSort(arr, pivote + 1, fin); 
    } 
} 

// pre: cantidad es la cantidad de elementos del array
// pos: ordena el vector ascendentemente
void selectionSort(int* array, int cantidad){

	if (!array)
		return;

	for(int i = 0; i < cantidad; i++){

		int max = array[i];
		int pos = i;

		for (int j = i + 1; j < cantidad; j++){

			if(array[j] < max){
				max = array[j];
				pos = j;
			}
		}

		swap(&array[i], &array[pos]);
	}
}

// pre: cantidad es la cantidad de elementos del array
// pos: ordena el vector ascendentemente
void bubbleSort(int* array, int cantidad){

	if(!array)
		return;

	for(int i = 0; i < cantidad; i++){

		for(int j = 0; j < cantidad - i - 1; j++){

			if(array[j] > array[j + 1])
				swap(&array[j], &array[j + 1]);
		}
	}
}

// pre: cantidad es la cantidad de elementos de arr
// pos: devuelve el numero maximo dentro de arr
int getMax(int arr[], int cantidad){ 

    int mx = arr[0]; 

    for (int i = 1; i < cantidad; i++) 
        if (arr[i] > mx) 
            mx = arr[i]; 

    return mx; 
} 
 
void countSort(int arr[], int n, int exp){ 

    int output[n];
    int i, count[10] = {0}; 
  
    for (i = 0; i < n; i++) 
        count[ (arr[i]/exp)%10 ]++; 
  
    for (i = 1; i < 10; i++) 
        count[i] += count[i - 1]; 
  
    for (i = n - 1; i >= 0; i--){ 
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
        count[ (arr[i]/exp)%10 ]--; 
    } 
  
    for (i = 0; i < n; i++) 
        arr[i] = output[i]; 
} 
  
// pre: cantidad es la cantidad de elementos del array
// pos: ordena el vector ascendentemente
void radixSort(int arr[], int cantidad){ 

    int m = getMax(arr, cantidad); 

    for (int exp = 1; m/exp > 0; exp *= 10) 
        countSort(arr, cantidad, exp); 
} 
