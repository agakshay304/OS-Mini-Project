#include <stdio.h>
// #include <malloc.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void *sortArr(void *num)
{
    int i, j, temp, cast, first = 0, last;

    // Casting
    cast = (intptr_t)num;

    // Calculating first and last element
    first = (cast * 50);
    last = first + 49;

    // printf("first %d , last %d \n", first, last);

    /*    SORTING */
    for (i = first; i < last - 1; i++)
    {
        for (j = first; j < last + first - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    /*    SORTING */
    int count = 0;
    for (i = first; i < last; i++)
    {
        if (arr[i] == 0)
        {
            count++;
        }
    }
    if (count == last - first)
    {
        return NULL;
    }
    else
    {
        for (i = first; i < last; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}