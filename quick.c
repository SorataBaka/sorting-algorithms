#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int partition(int *array, int minIndex, int maxIndex)
{
  int pivot = array[maxIndex];
  int i = minIndex - 1;
  for (int j = minIndex; j <= maxIndex - 1; j++)
  {
    if (array[j] < pivot)
    {
      i++;
      int temp = array[i];
      array[i] = array[j];
      array[j] = temp;
    }
  }

  int temp = array[i + 1];
  array[i + 1] = array[maxIndex];
  array[maxIndex] = temp;
  return i + 1;
}

void quickSort(int *array, int minIndex, int maxIndex, long int *memoryUsed)
{
  if (minIndex < maxIndex)
  {
    int pivot = partition(array, minIndex, maxIndex);
    quickSort(array, minIndex, pivot - 1, memoryUsed);
    quickSort(array, pivot + 1, maxIndex, memoryUsed);
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Please include the required files");
    return 1;
  }
  // Header
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
    long int memoryUsed = 0;

    int *dataArray = (int *)malloc(sizeof(int) * dataLength);
    memoryUsed += sizeof(int) * dataLength;

    for (int i = 0; i < dataLength; i++)
    {
      fscanf(fileRead, "%d\n", &(dataArray[i]));
      if (dataArray[i] > maxValue)
        maxValue = dataArray[i];
    }
    fclose(fileRead);
    clock_t start_time = clock();
    quickSort(dataArray, 0, dataLength - 1, &memoryUsed);
    clock_t end_time = clock();

    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Data row
    printf("|%-14s | %-24s | %10d | %9.5f | %14ld|\n", "Quick Sort", argv[fileIndex], dataLength, elapsed_time, memoryUsed);
  }

  return 0;
}
