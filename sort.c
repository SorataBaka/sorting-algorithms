#include "sort.h"
void bucketSort(int maxValue, int bucket_count, int arrayLength, int *array, long int *memoryUsed)
{
  int BUCKET_COUNT = bucket_count;
  int range = maxValue / BUCKET_COUNT + 1;

  // Allocate bucket array
  int **buckets = (int **)malloc(BUCKET_COUNT * sizeof(int *));
  int *bucketSizes = (int *)calloc(BUCKET_COUNT, sizeof(int));
  int *bucketCapacities = (int *)malloc(BUCKET_COUNT * sizeof(int));

  *memoryUsed += BUCKET_COUNT * sizeof(int *); // pointers to buckets
  *memoryUsed += BUCKET_COUNT * sizeof(int);   // bucketSizes
  *memoryUsed += BUCKET_COUNT * sizeof(int);   // bucketCapacities

  for (int i = 0; i < BUCKET_COUNT; i++)
  {
    bucketCapacities[i] = 10;
    buckets[i] = (int *)malloc(bucketCapacities[i] * sizeof(int));
    *memoryUsed += bucketCapacities[i] * sizeof(int);
  }

  // Distribute input array into buckets
  for (int i = 0; i < arrayLength; i++)
  {
    int val = array[i];
    int bucketIndex = (val - 1) / range;
    if (bucketSizes[bucketIndex] == bucketCapacities[bucketIndex])
    {
      // Reallocate if bucket is full
      bucketCapacities[bucketIndex] *= 2;
      buckets[bucketIndex] = (int *)realloc(buckets[bucketIndex], bucketCapacities[bucketIndex] * sizeof(int));
      *memoryUsed += bucketCapacities[bucketIndex] / 2 * sizeof(int); // Add only the newly allocated part
    }
    buckets[bucketIndex][bucketSizes[bucketIndex]++] = val;
  }

  // Sort each bucket and concatenate
  int index = 0;
  for (int i = 0; i < BUCKET_COUNT; i++)
  {
    insertionSort(bucketSizes[i], buckets[i]);
    for (int j = 0; j < bucketSizes[i]; j++)
    {
      array[index++] = buckets[i][j];
    }
    free(buckets[i]);
  }

  free(buckets);
  free(bucketSizes);
  free(bucketCapacities);
}
void bubbleSort(int arrayLength, int *array)
{
  for (int i = 0; i < arrayLength; i++)
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
void countSort(int maxValue, int arrayLength, int *array, long int *memoryUsed)
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
void shakerSort(int arrayLength, int *array)
{
  int swapped = 1;
  int direction = 0; // 0 for from left 1 for from right
  while (swapped)
  {
    swapped = 0;
    if (direction == 0)
    {
      for (int i = 0; i < arrayLength - 2; i++)
      {
        if (array[i] > array[i + 1])
        {
          swapped = 1;
          int temp = array[i];
          array[i] = array[i + 1];
          array[i + 1] = temp;
        }
      }
      direction = 1;
    }
    else if (direction == 1)
    {
      for (int i = arrayLength - 1; i > 0; i--)
      {
        if (array[i] < array[i - 1])
        {
          swapped = 1;
          int temp = array[i - 1];
          array[i - 1] = array[i];
          array[i] = temp;
        }
      }
      direction = 0;
    }
  }
}