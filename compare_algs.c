#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "sort.h"
void refreshArray(int *rawArray, int *dataArray, int length)
{
  for (int i = 0; i < length; i++)
    dataArray[i] = rawArray[i];
}
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Please include the required files");
    return 1;
  }
  printf("|%-14s | %-24s | %10s | %9s | %14s|\n", "Algorithm", "File", "Input Size", "Time(s)", "Memory(b)");
  for (int fileIndex = 1; fileIndex < argc; fileIndex++)
  {
    char *fileName = argv[fileIndex];
    FILE *fileRead = fopen(fileName, "r");
    if (fileRead == NULL)
    {
      printf("File not found.. Exiting\n");
      return 1;
    }
    int dataLength = 100000;
    int maxValue = 0;
    long int rawMemory = 0;

    int *rawArray = (int *)malloc(sizeof(int) * dataLength);
    rawMemory += sizeof(int) * dataLength;
    for (int i = 0; i < dataLength; i++)
    {
      fscanf(fileRead, "%d\n", &(rawArray[i]));
      if (rawArray[i] > maxValue)
        maxValue = rawArray[i];
    }
    fclose(fileRead);

    long int memoryUsed = rawMemory;

    int *dataArray = (int *)malloc(sizeof(int) * dataLength);
    refreshArray(rawArray, dataArray, dataLength);
    memoryUsed = rawMemory;

    // Start here
    clock_t bubble_start_time = clock();
    bubbleSort(dataLength, dataArray);
    clock_t bubble_end_time = clock();

    double elapsed_time = (double)(bubble_end_time - bubble_start_time) / CLOCKS_PER_SEC;

    printf("|%-14s | %-24s | %10d | %9.5f | %14ld|\n", "Bubble Sort", argv[fileIndex], dataLength, elapsed_time, memoryUsed);

    refreshArray(rawArray, dataArray, dataLength);
    memoryUsed = rawMemory;

    clock_t bucket_start_time = clock();
    bucketSort(maxValue, 100, dataLength, dataArray, &memoryUsed);
    clock_t bucket_end_time = clock();

    elapsed_time = (double)(bucket_end_time - bucket_start_time) / CLOCKS_PER_SEC;

    printf("|%-14s | %-24s | %10d | %9.5f | %14ld|\n", "Bucket Sort", argv[fileIndex], dataLength, elapsed_time, memoryUsed);

    refreshArray(rawArray, dataArray, dataLength);
    memoryUsed = rawMemory;

    clock_t count_start_time = clock();
    countSort(maxValue, dataLength, dataArray, &memoryUsed);
    clock_t count_end_time = clock();

    elapsed_time = (double)(count_end_time - count_start_time) / CLOCKS_PER_SEC;

    printf("|%-14s | %-24s | %10d | %9.5f | %14ld|\n", "Count Sort", argv[fileIndex], dataLength, elapsed_time, memoryUsed);

    refreshArray(rawArray, dataArray, dataLength);
    memoryUsed = rawMemory;

    clock_t insertion_start_time = clock();
    insertionSort(dataLength, dataArray);
    clock_t insertion_end_time = clock();

    elapsed_time = (double)(insertion_end_time - insertion_start_time) / CLOCKS_PER_SEC;

    printf("|%-14s | %-24s | %10d | %9.5f | %14ld|\n", "Insertion Sort", argv[fileIndex], dataLength, elapsed_time, memoryUsed);

    refreshArray(rawArray, dataArray, dataLength);
    memoryUsed = rawMemory;

    clock_t quick_start_time = clock();
    quickSort(dataArray, 0, dataLength - 1, &memoryUsed);
    clock_t quick_end_time = clock();

    elapsed_time = (double)(quick_end_time - quick_start_time) / CLOCKS_PER_SEC;

    printf("|%-14s | %-24s | %10d | %9.5f | %14ld|\n", "Quick Sort", argv[fileIndex], dataLength, elapsed_time, memoryUsed);

    refreshArray(rawArray, dataArray, dataLength);
    memoryUsed = rawMemory;

    clock_t shaker_start_time = clock();
    shakerSort(dataLength, dataArray);
    clock_t shaker_end_time = clock();

    elapsed_time = (double)(shaker_end_time - shaker_start_time) / CLOCKS_PER_SEC;

    printf("|%-14s | %-24s | %10d | %9.5f | %14ld|\n", "Shaker Sort", argv[fileIndex], dataLength, elapsed_time, memoryUsed);
  }

  return 0;
}