#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void bucketSort(int maxValue, int arrayLength, int *array, long int *memoryUsed)
{
  int *buckets = (int *)malloc(sizeof(int) * maxValue);
  *memoryUsed += sizeof(int) * maxValue;
  for (int i = 0; i < arrayLength; i++)
  {
    buckets[array[i] - 1]++;
  }
  int index = 0;
  for (int i = 0; i < maxValue; i++)
  {
    while (buckets[i] > 0)
    {
      array[index++] = i + 1;
      buckets[i]--;
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
    bucketSort(maxValue, dataLength, dataArray, &memoryUsed);
    clock_t end_time = clock();

    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("|%-14s | %-24s | %10d | %9.5f | %14ld|\n", "Bucket Sort", argv[fileIndex], dataLength, elapsed_time, memoryUsed);
  }

  return 0;
}