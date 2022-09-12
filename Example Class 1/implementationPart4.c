#include "arrayGenerate.c"
#include "mergeInsertionSort.c"
#include "writeOutput.c"
#include "mergeSort.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_SIZE 1000

int main()
{
    writeFile("mergeInsertionSortPart4.csv", "Algorithm,Key comparisons,Execution time \n");

    for (int i = 0; i <= 100; i ++)
    {
        long long keyComparisons = 0;
        long long arraySize = 10000000;
        int s = log(arraySize) / log(2);

        int *Arr1 = (int *) malloc(sizeof(int) * arraySize);
        Arr1 = arrayGenerate(arraySize, MAX_SIZE); 

        clock_t begin = clock();
        mergeInsertionSort(&Arr1, 0, arraySize - 1, s, &keyComparisons);
        clock_t end = clock();
        free(Arr1);
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        writeStringOutput("mergeInsertionSortPart4.csv", "Merge-Insertion Sort", ",");
        writeLongOutput("mergeInsertionSortPart4.csv", keyComparisons, ",");
        writeDoubleOutput("mergeInsertionSortPart4.csv", time_spent, "\n");

        int *Arr2 = (int *) malloc(sizeof(int) * arraySize);
        Arr2 = arrayGenerate(arraySize, MAX_SIZE); 
        keyComparisons = 0;

        begin = clock(); 
        mergeSort(&Arr2, 0, arraySize - 1, &keyComparisons);
        end = clock();
        free(Arr2);
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        writeStringOutput("mergeInsertionSortPart4.csv", "Merge Sort", ",");
        writeLongOutput("mergeInsertionSortPart4.csv", keyComparisons, ",");
        writeDoubleOutput("mergeInsertionSortPart4.csv", time_spent, "\n");
    }
}