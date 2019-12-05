#ifndef __SORT_H__
#define __SORT_H__

void mergeSort(void** array, int cantidad, int (*es_menor)(void*, void*));

void quickSort(int* array, int inicio, int fin);

void selectionSort(int* array, int cantidad);

void bubbleSort(int* array, int cantidad);

void radixSort(int arr[], int n);


#endif
