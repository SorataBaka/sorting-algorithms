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

typedef enum SORT_RESULT
{
  FILE_NAME,
  METHOD,
  LENGTH,
  TIME,
  MEMORY
} SORT_RESULT;

typedef struct
{
  char **files;
  int file_count;
  int is_reversed;
  char outFile[256];
  int has_outFile;
  int has_limit;
  int limit;
  SORTING_ALG algorithm;
  SORT_RESULT sortresult;
} Param;

typedef struct
{
  char fileName[200];
  char sortingMethod[20];
  int dataLength;
  double elapsed_time;
  int memoryUsed;

} Result;
int cmpFileName(const void *a, const void *b)
{
  return strcmp(((Result *)a)->fileName, ((Result *)b)->fileName);
}

int cmpMethod(const void *a, const void *b)
{
  return strcmp(((Result *)a)->sortingMethod, ((Result *)b)->sortingMethod);
}

int cmpLength(const void *a, const void *b)
{
  int la = ((Result *)a)->dataLength;
  int lb = ((Result *)b)->dataLength;
  return (la > lb) - (la < lb);
}

int cmpTime(const void *a, const void *b)
{
  double ta = ((Result *)a)->elapsed_time;
  double tb = ((Result *)b)->elapsed_time;
  return (ta > tb) - (ta < tb);
}

int cmpMemory(const void *a, const void *b)
{
  int ma = ((Result *)a)->memoryUsed;
  int mb = ((Result *)b)->memoryUsed;
  return (ma > mb) - (ma < mb);
}

void sortResults(Result *results, int count, SORT_RESULT key)
{
  switch (key)
  {
  case FILE_NAME:
    qsort(results, count, sizeof(Result), cmpFileName);
    break;
  case METHOD:
    qsort(results, count, sizeof(Result), cmpMethod);
    break;
  case LENGTH:
    qsort(results, count, sizeof(Result), cmpLength);
    break;
  case TIME:
    qsort(results, count, sizeof(Result), cmpTime);
    break;
  case MEMORY:
    qsort(results, count, sizeof(Result), cmpMemory);
    break;
  }
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

  rewind(fileRead);
  int *array = (int *)malloc(sizeof(int) * dataLength);
  *memory += sizeof(int) * dataLength;

  for (int i = 0; i < dataLength; i++)
  {
    fscanf(fileRead, "%d", &(array[i]));
  }
  return array;
}
void printHelp(const char *programName)
{
  printf(
      "Usage: %s [file1 file2 ...] [--out <output_file>] [--alg <algorithm>] [--sortresult <field>] [--limit <N>]\n\n"
      "Positional arguments:\n"
      "  file1 file2 ...         One or more input files to process\n\n"
      "Options:\n"
      "  --out <output_file>     Write sorted output to a file named <algorithm>-<output_file>\n"
      "  --alg <algorithm>       Choose sorting algorithm to use. Available algorithms:\n"
      "                            all      Run all algorithms\n"
      "                            bubble   Bubble Sort\n"
      "                            bucket   Bucket Sort\n"
      "                            count    Counting Sort\n"
      "                            insert   Insertion Sort\n"
      "                            quick    Quick Sort\n"
      "                            shaker   Shaker Sort\n"
      "  --sortresult <field>    Sort result table by one of the following:\n"
      "                            file     Sort by file name\n"
      "                            method   Sort by sorting method\n"
      "                            length   Sort by data length\n"
      "                            time     Sort by execution time\n"
      "                            memory   Sort by memory usage\n"
      "  --limit <N>             Only read at most N numbers from each input file\n"
      "  --help                  Show this help message and exit\n\n"
      "Examples:\n"
      "  %s input.txt --out result.txt\n"
      "  %s input1.txt input2.txt --alg quick\n"
      "  %s input.txt --alg all --out sorted.txt --sortresult time --limit 1000\n",
      programName, programName, programName, programName);
}
int findMaxValue(int *array, int length)
{
  int max = array[0];
  for (int i = 0; i < length; i++)
  {
    if (array[i] > max)
      max = array[i];
  }
  return max;
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
  params.sortresult = FILE_NAME;

  int i = 1;
  // First parse positional arguments (files)
  while (i < argc && strncmp(argv[i], "--", 2) != 0)
  {
    params.files[params.file_count++] = argv[i++];
  }

  // Now parse options
  while (i < argc)
  {
    if (strcmp(argv[i], "--alg") == 0)
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
    else if (strcmp(argv[i], "--sortresult") == 0)
    {
      if (i + 1 >= argc)
      {
        fprintf(stderr, "Error: --sortresult requires a valid key\n");
        exit(EXIT_FAILURE);
      }
      char sortKey[20];
      strcpy(sortKey, argv[++i]);

      if (strcmp(sortKey, "file") == 0)
        params.sortresult = FILE_NAME;
      else if (strcmp(sortKey, "method") == 0)
        params.sortresult = METHOD;
      else if (strcmp(sortKey, "length") == 0)
        params.sortresult = LENGTH;
      else if (strcmp(sortKey, "time") == 0)
        params.sortresult = TIME;
      else if (strcmp(sortKey, "memory") == 0)
        params.sortresult = MEMORY;
      else
      {
        fprintf(stderr, "Unknown sort key: %s\n", sortKey);
        printHelp(argv[0]);
        exit(EXIT_FAILURE);
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
    else if (strcmp(argv[i], "--help") == 0)
    {
      printHelp(argv[0]);
      exit(EXIT_SUCCESS);
      i++;
    }
    else if (strcmp(argv[i], "--limit") == 0)
    {
      if (i + 1 >= argc)
      {
        fprintf(stderr, "Error: --limit requires a number\n");
        exit(EXIT_FAILURE);
      }
      params.has_limit = 1;
      params.limit = atoi(argv[++i]);
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
void printResultsTable(Result results[], int count)
{
  // Print header
  printf(
      "+----------------------+----------------+-------------+---------------+-------------+\n"
      "| File Name            | Sort Method    | Data Length | Time (sec)    | Memory (KB) |\n"
      "+----------------------+----------------+-------------+---------------+-------------+\n");

  // Print each result row
  for (int i = 0; i < count; ++i)
  {
    printf("| %-20s | %-14s | %-11d | %-13.6f | %-11.2d |\n",
           results[i].fileName,
           results[i].sortingMethod,
           results[i].dataLength,
           results[i].elapsed_time,
           results[i].memoryUsed);
  }

  // Print footer
  printf(
      "+----------------------+----------------+-------------+---------------+-------------+\n");
}
const char *getAlgName(SORTING_ALG alg)
{
  switch (alg)
  {
  case BUBBLE:
    return "bubble";
  case BUCKET:
    return "bucket";
  case COUNT:
    return "count";
  case INSERT:
    return "insert";
  case QUICK:
    return "quick";
  case SHAKER:
    return "shaker";
  case ALL:
    return "all";
  default:
    return "unknown";
  }
}
void printOut(SORTING_ALG alg, char *fileName, int *dataArray, int length)
{
  char outputFileName[300];
  const char *algName = getAlgName(alg);

  snprintf(outputFileName, sizeof(outputFileName), "%s-%s", algName, fileName);

  FILE *outFile = fopen(outputFileName, "w");
  if (!outFile)
  {
    perror("Failed to open output file");
    return;
  }

  for (int i = 0; i < length; i++)
  {
    fprintf(outFile, "%d\n", dataArray[i]);
  }

  fclose(outFile);
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
    int readlen = getFileLength(fileRead);
    int fileLength = !params.has_limit ? readlen : params.limit > readlen ? readlen
                                                                          : params.limit;
    long usedMemory = 0;
    int *dataArray = readFile(fileRead, fileLength, &usedMemory);
    int *clonedArray = (int *)malloc(sizeof(int) * fileLength);
    for (SORTING_ALG alg = BUBBLE; alg <= SHAKER; ++alg)
    {
      if (params.algorithm != ALL && params.algorithm != alg)
        continue;
      long tempMemory = 0;
      memcpy(clonedArray, dataArray, fileLength * sizeof(int));
      clock_t start_time, end_time;
      double elapsed_time = 0;
      switch (alg)
      {
      case BUBBLE:
        printf("Executing Bubble Sort on file %s\n", params.files[fileIndex]);
        start_time = clock();
        bubbleSort(fileLength, clonedArray);
        end_time = clock();
        elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        break;

      case BUCKET:
        printf("Executing Bucket Sort on file %s\n", params.files[fileIndex]);
        start_time = clock();
        bucketSort(findMaxValue(clonedArray, fileLength), /*bucket_count=*/2000, fileLength, clonedArray, &tempMemory);
        end_time = clock();
        elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        break;

      case COUNT:
        printf("Executing Count Sort on file %s\n", params.files[fileIndex]);
        start_time = clock();
        countSort(findMaxValue(clonedArray, fileLength), fileLength, clonedArray, &tempMemory);
        end_time = clock();
        elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        break;

      case INSERT:
        printf("Executing Insert Sort on file %s\n", params.files[fileIndex]);
        start_time = clock();
        insertionSort(fileLength, clonedArray);
        end_time = clock();
        elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        break;

      case QUICK:
        printf("Executing Quick Sort on file %s\n", params.files[fileIndex]);
        start_time = clock();
        quickSort(clonedArray, 0, fileLength - 1, &tempMemory);
        end_time = clock();
        elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        break;

      case SHAKER:
        printf("Executing Shaker Sort on file %s\n", params.files[fileIndex]);
        start_time = clock();
        shakerSort(fileLength, clonedArray);
        end_time = clock();
        elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        break;
      case ALL:
        break;
      }

      strcpy(resultArray[resultIndex].fileName, params.files[fileIndex]);

      switch (alg)
      {
      case BUBBLE:
        strcpy(resultArray[resultIndex].sortingMethod, "Bubble Sort");
        break;
      case BUCKET:
        strcpy(resultArray[resultIndex].sortingMethod, "Bucket Sort");
        break;
      case COUNT:
        strcpy(resultArray[resultIndex].sortingMethod, "Counting Sort");
        break;
      case INSERT:
        strcpy(resultArray[resultIndex].sortingMethod, "Insertion Sort");
        break;
      case QUICK:
        strcpy(resultArray[resultIndex].sortingMethod, "Quick Sort");
        break;
      case SHAKER:
        strcpy(resultArray[resultIndex].sortingMethod, "Shaker Sort");
        break;
      case ALL:
        break;
      }
      resultArray[resultIndex].dataLength = fileLength;
      resultArray[resultIndex].elapsed_time = elapsed_time;
      resultArray[resultIndex].memoryUsed = (int)(usedMemory + tempMemory);
      resultIndex++;
      if (params.has_outFile)
      {
        printOut(alg, params.outFile, clonedArray, fileLength);
      }
    }

    free(clonedArray);
  }
  sortResults(resultArray, resultCount, params.sortresult);
  printResultsTable(resultArray, resultIndex);

  return 0;
}