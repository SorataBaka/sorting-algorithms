#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void bubbleSort(int arrayLength, int *array)
{
  for (int i = 0; i < arrayLength - 1; i++)
  {
    for (int j = i + 1; j < arrayLength; j++)
    {
      if (array[j] < array[i])
      {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
      }
    }
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
    bubbleSort(dataLength, dataArray);
    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("|%-14s | %-24s | %10d | %9.5f | %14ld|\n", "Bubble Sort", argv[fileIndex], dataLength, elapsed_time, memoryUsed);
  }

  return 0;
}