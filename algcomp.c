#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "sort.h"
#include <string.h>

typedef enum SORTING_ALG
{
  BUBBLE,
  BUCKET,
  COUNT,
  INSERT,
  QUICK,
  SHAKER,
  ALL
} SORTING_ALG;

typedef struct
{
  char **files;
  int file_count;
  int is_reversed;
  char outFile[256];
  int has_outFile;
  SORTING_ALG algorithm;
} Param;

typedef struct
{
  char *fileName;
  char *sortingMethod;
  int dataLength;
  double elapsed_time;
  int memoryUsed;

} Result;

int validateArray(Param config, int *rawArray, int length)
{
  for (int i = 0; i < length - 1; i++)
  {
    if (config.is_reversed == 0 && rawArray[i] > rawArray[i + 1])
    {
      printf("%d %d\n", rawArray[i], rawArray[i + 1]);
      return 0;
    }
    else if (config.is_reversed == 1 && rawArray[i] < rawArray[i + 1])
    {
      printf("%d %d\n", rawArray[i], rawArray[i + 1]);
      return 0;
    }
  }
  return 1;
}
int getFileLength(FILE *fileRead)
{
  int lines = 0;
  char buffer[1024];
  while (fgets(buffer, sizeof(buffer), fileRead))
    lines++;
  return lines;
}
int *readFile(FILE *fileRead, int dataLength, long int *memory)
{
  if (fileRead == NULL)
    return NULL;
  int *array = (int *)malloc(sizeof(int) * dataLength);
  *memory += sizeof(int) * dataLength;

  for (int i = 0; i < dataLength; i++)
  {
    fscanf(fileRead, "%d\n", &(array[i]));
  }

  fclose(fileRead);
  return array;
}
void printHelp(const char *programName)
{
  printf(
      "Usage: %s [file1 file2 ...] [--reversed] [--out <output_file>] [--alg <algorithm>]\n\n"
      "Positional arguments:\n"
      "  file1 file2 ...        One or more input files to process\n\n"
      "Options:\n"
      "  --reversed             Process files in reversed order\n"
      "  --out <output_file>    Write output to <output_file>\n"
      "  --alg <algorithm>      Choose sorting algorithm to use\n"
      "                         Available algorithms:\n"
      "                           all     - Run all algorithms\n"
      "                           bubble  - Bubble Sort\n"
      "                           bucket  - Bucket Sort\n"
      "                           count   - Counting Sort\n"
      "                           insert  - Insertion Sort\n"
      "                           quick   - Quick Sort\n"
      "                           shaker  - Shaker Sort\n\n"
      "Examples:\n"
      "  %s input1.txt input2.txt --reversed\n"
      "  %s input.txt --out result.txt\n"
      "  %s input.txt --alg quick\n"
      "  %s input.txt --alg all --out sorted.txt\n",
      programName, programName, programName, programName, programName);
}

Param parseArguments(int argc, char *argv[])
{
  Param params = {0};
  params.files = malloc(sizeof(char *) * argc); // overallocate, shrink later
  params.file_count = 0;
  params.is_reversed = 0;
  params.has_outFile = 0;
  params.outFile[0] = '\0';
  params.algorithm = ALL;

  int i = 1;
  // First parse positional arguments (files)
  while (i < argc && strncmp(argv[i], "--", 2) != 0)
  {
    params.files[params.file_count++] = argv[i++];
  }

  // Now parse options
  while (i < argc)
  {
    if (strcmp(argv[i], "--reversed") == 0)
    {
      params.is_reversed = 1;
      i++;
    }
    else if (strcmp(argv[i], "--alg") == 0)
    {
      if (i + 1 >= argc)
      {
        fprintf(stderr, "Error: --alg requires a valid algorithm\n");
        exit(EXIT_FAILURE);
      }
      char algName[20];
      strcpy(algName, argv[++i]);

      if (strcmp(algName, "all") == 0)
      {
        params.algorithm = ALL;
      }
      else if (strcmp(algName, "bubble") == 0)
      {
        params.algorithm = BUBBLE;
      }
      else if (strcmp(algName, "bucket") == 0)
      {
        params.algorithm = BUCKET;
      }
      else if (strcmp(algName, "count") == 0)
      {
        params.algorithm = COUNT;
      }
      else if (strcmp(algName, "insert") == 0)
      {
        params.algorithm = INSERT;
      }
      else if (strcmp(algName, "quick") == 0)
      {
        params.algorithm = QUICK;
      }
      else if (strcmp(algName, "shaker") == 0)
      {
        params.algorithm = SHAKER;
      }
      else
      {
        fprintf(stderr, "Unknown algorithm: %s\n", algName);
        printHelp(argv[0]);
        exit(1); // Or handle error gracefully
      }
      i++;
    }
    else if (strcmp(argv[i], "--out") == 0)
    {
      if (i + 1 >= argc)
      {
        fprintf(stderr, "Error: --out requires a filename\n");
        exit(EXIT_FAILURE);
      }
      strncpy(params.outFile, argv[++i], sizeof(params.outFile) - 1);
      params.outFile[sizeof(params.outFile) - 1] = '\0';
      params.has_outFile = 1;
      i++;
    }
    else
    {
      fprintf(stderr, "Unknown option: %s\n", argv[i]);
      exit(EXIT_FAILURE);
    }
  }

  return params;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printHelp(argv[0]);
    printf("Please include the required file\n");
    return 1;
  }

  Param params = parseArguments(argc, argv);
  int resultCount;
  if (params.algorithm == ALL)
    resultCount = 6 * params.file_count;
  else
    resultCount = params.file_count;
  Result *resultArray = (Result *)malloc(sizeof(Result) * resultCount);
  int resultIndex = 0;

  for (int fileIndex = 0; fileIndex < params.file_count; fileIndex++)
  {
    FILE *fileRead = fopen(params.files[fileIndex], "r");
    if (fileRead == NULL)
    {
      printf("Unable to open file.\n");
      return EXIT_FAILURE;
    }
    int fileLength = getFileLength(fileRead);
    long usedMemory = 0;
    int *dataArray = readFile(fileRead, fileLength, &usedMemory);
    int *clonedArray = (int *)malloc(sizeof(int) * fileLength);
    memcpy(clonedArray, dataArray, fileLength * sizeof(int));

    if (params.algorithm == ALL || params.algorithm == BUBBLE)
    {
      clock_t start_time = clock();
      bubbleSort(fileLength, clonedArray);
      clock_t end_time = clock();
      if (validateArray(params, clonedArray, fileLength) == 0)
      {
        printf("Failed to sort file\n");
        exit(EXIT_FAILURE);
      }
      double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

      strcpy(resultArray[resultIndex].fileName, params.files[fileIndex]);
      strcpy(resultArray[resultIndex].sortingMethod, "Bubble Sort");
      resultArray[resultIndex].dataLength = fileLength;
      resultArray[resultIndex].elapsed_time = elapsed_time;
      resultArray[resultIndex].memoryUsed = usedMemory;
      resultIndex++;
    }
  }
  return 0;
}