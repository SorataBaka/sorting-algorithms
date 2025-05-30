#ifndef SORT_H
#define SORT_H

#include <stdlib.h>

void bubbleSort(int arrayLength, int *array);
void bucketSort(int maxValue, int bucket_count, int arrayLength, int *array, long int *memoryUsed);
void countSort(int maxValue, int arrayLength, int *array, long int *memoryUsed);
void insertionSort(int arrayLength, int *array);
void quickSort(int *array, int minIndex, int maxIndex, long int *memoryUsed);
void shakerSort(int arrayLength, int *array);
#endif