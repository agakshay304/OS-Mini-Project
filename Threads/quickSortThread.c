#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

int quickarr[10000000];
static int temp = 0;

void swap(int *quickarr, int i, int j)
{
    int temp = quickarr[i];
    quickarr[i] = quickarr[j];
    quickarr[j] = temp;
    return;
}

int partition(int *quickarr, int start, int end)
{
    int insert = start;
    int pivot = quickarr[end];
    for (int i = start; i <= end; i++)
    {
        if (quickarr[i] <= pivot)
        {
            swap(quickarr, i, insert++);
        }
    }
    return insert - 1;
}

void *quicksort(int position[])
{

    int start = position[0];
    int end = position[1];

    if (start >= end)
    {
        return NULL;
    }

    int pos = partition(quickarr, start, end);

    int left_position[2];
    left_position[0] = start;
    left_position[1] = pos - 1;

    int right_position[2];
    right_position[0] = pos + 1;
    right_position[1] = end;

    quicksort(left_position);
    quicksort(right_position);
    return NULL;
}