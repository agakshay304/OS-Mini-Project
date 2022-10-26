#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void binarySearch(int *array, int size, int key)
{
    int low = 0;
    int high = size - 1;
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (array[mid] == key)
        {
            printf("Found %d at index %d in the array of size %d\n", key, mid, size);
            return;
        }
        else if (array[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    printf("Could not find %d in the array of size %d\n", key, size);
}