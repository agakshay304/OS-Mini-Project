#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void linearSearch(int *array, int size, int key)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (array[i] == key)
        {
            printf("Found %d at index %d in the array of size %d\n", key, i, size);
            return;
        }
    }
    printf("Could not find %d in the array of size %d\n", key, size);
}