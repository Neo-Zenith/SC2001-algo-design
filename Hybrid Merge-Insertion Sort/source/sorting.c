#include <stdio.h>
#include <stdlib.h>

void mergeSort(int **Arr, int start, int end, long long *keyComparisons);
void swap(int **Arr, int i, int j);
void insertionSort(int **Arr, int start, int end, long long *keyComparisons);
void merge(int **Arr, int start, int end, int pivot, long long *keyComparisons);
void mergeInsertionSort(int **Arr, int start, int end, int S, long long *keyComparisons);

// Swap the element at index i and index j
// int **Arr == Array to be sorted
// int i, int j == indexes of the elements to be swapped
void swap(int **Arr, int i, int j)
{
    int temp = (*Arr)[i];
    (*Arr)[i] = (*Arr)[j];
    (*Arr)[j] = temp;
}

// Insertion Sort algorithm
// int **Arr == Array to be sorted
// int start == starting index
// int end == ending index
// long long *keyComparisons == a pointer that points to the integer storing the total number of key comparisons
void insertionSort(int **Arr, int start, int end, long long *keyComparisons)
{
    for (int i = start + 1; i <= end; i ++)
    {
        for (int j = i; j > start; j --)
        {
            (*keyComparisons) ++;
            if ((*Arr)[j] < (*Arr)[j - 1])
            {
                swap(Arr, j, j - 1);
            }
            else
            {
                break;
            }
        }
    }
}

// Merge function
// int **Arr == Array to be sorted
// int start == starting index
// int end == ending index
// int pivot == mid point of the Array which marks the split between the two subarrays
// long long *keyComparisons == a pointer that points to the integer storing the total number of key comparisons
void merge(int **Arr, int start, int end, int pivot, long long *keyComparisons)
{
    int *sortedArray = (int *) malloc(sizeof(int) * ((end - start) + 1));

    int i = start;
    int j = pivot + 1;
    int k = 0;

    while (i <= pivot && j <= end)
    {
        (*keyComparisons) ++;
        if ((*Arr)[i] < (*Arr)[j])
        {
            sortedArray[k ++] = (*Arr)[i ++];
        }
        else if ((*Arr)[i] > (*Arr)[j])
        {
            sortedArray[k ++] = (*Arr)[j ++];
        }
        else
        {
            sortedArray[k ++] = (*Arr)[i ++];
            sortedArray[k ++] = (*Arr)[j ++];
        }
    }
    
    while (i <= pivot)
    {
        sortedArray[k ++] = (*Arr)[i ++];
    }
    
    while (j <= end)
    {
        sortedArray[k ++] = (*Arr)[j ++];
    }

    k = 0;
    for (int i = start; i <= end; i ++)
    {
        (*Arr)[i] = sortedArray[k ++];
    }

    free(sortedArray);
}

// Hybrid Merge Insertion Sort algorithm
// int **Arr == Array to be sorted
// int start == starting index
// int end == ending index
// int S == threshold value
// long long *keyComparisons == a pointer that points to the integer storing the total number of key comparisons
void mergeInsertionSort(int **Arr, int start, int end, int S, long long *keyComparisons)
{
    if (start >= end)
    {
        return;
    }

    int pivot = (start + end) / 2;

    if (end - start > S)
    {
        mergeInsertionSort(Arr, start, pivot, S, keyComparisons);
        mergeInsertionSort(Arr, pivot + 1, end, S, keyComparisons);

        merge(Arr, start, end, pivot, keyComparisons);
    }

    else
    {
        insertionSort(Arr, start, end, keyComparisons);
    }
}

// Merge Sort algorithm
// int **Arr == Array to be sorted
// int start == starting index
// int end == ending index
// long long *keyComparisons == a pointer that points to the integer storing the total number of key comparisons
void mergeSort(int **Arr, int start, int end, long long *keyComparisons)
{
    if (start >= end)
    {
        return;
    }

    int pivot = (start + end) / 2;

    mergeSort(Arr, start, pivot, keyComparisons);
    mergeSort(Arr, pivot + 1, end, keyComparisons);

    merge(Arr, start, end, pivot, keyComparisons);
}
