#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void insertionSort(int arrayLength, int *array)
{
  for (int i = 1; i < arrayLength; ++i)
  {
    int key = array[i];
    int j = i - 1;

    while (j >= 0 && array[j] > key)
    {
      array[j + 1] = array[j];
      j = j - 1;
    }
    array[j + 1] = key;
  }
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
    insertionSort(dataLength, dataArray);
    clock_t end_time = clock();

    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("|%-14s | %-24s | %10d | %9.5f | %14ld|\n", "Insert Sort", argv[fileIndex], dataLength, elapsed_time, memoryUsed);
  }

  return 0;
}