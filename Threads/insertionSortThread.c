#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 50

// shared globals
int unsorted[SIZE];
int sorted[SIZE];

// structures to hold function parameters for pthread calls
struct mergeInsertionParams
{
    int begin;
    int mid;
    int end;
};

struct insertionSortParams
{
    int start;
    int end;
};

// function prototypes
void fillArray(int size);
void *mergeInsertion(void *args);
void *insertionSort(void *args);
void printArray(int *list, int size);

/**
 * Main function
 */
// int main() {
//     return 0;
// }

/**
 * Fills unsorted array with random ints
 * @param size is the size of the array
 */
void fillArray(int size)
{
    int i;
    srand(time(NULL));
    for (i = 0; i < size; i++)
        unsorted[i] = rand() % 100;
}

/**
 * mergeInsertions two sorted halves of the unsorted[] array into sorted[]
 *
 * @param begin index of first element in first sublist
 * @param mid index of the first element in the second sublist
 * @param end index of the last element in the second sublist
 */
void *mergeInsertion(void *args)
{
    // unpack parameters
    struct mergeInsertionParams *params = (struct mergeInsertionParams *)args;
    int begin = params->begin,
        mid = params->mid,
        end = params->end;

    int i = begin, j = mid, tpos = begin;

    while (i < mid && j <= end)
    {
        if (unsorted[i] < unsorted[j])
            sorted[tpos++] = unsorted[i++];
        else
            sorted[tpos++] = unsorted[j++];
    }

    // still elements left over in first list. copy over
    while (i < mid)
        sorted[tpos++] = unsorted[i++];

    // still elements left over in first list. copy over
    while (j <= end)
        sorted[tpos++] = unsorted[j++];
    return NULL;
}

/**
 * Insertion sort
 *
 * @param index of the first element in unsorted sublist
 * @param index of the last element in unsorted sublist
 */
void *insertionSort(void *args)
{
    struct insertionSortParams *params = (struct insertionSortParams *)args;
    int start = params->start,
        end = params->end;

    int i = start, j, itemToInsert;

    // everything to the left of i is sorted
    while (i <= end)
    {
        itemToInsert = unsorted[i]; // a must, or else unsorted[i] gets overwritten when shifting elements

        // since everything in this sequence is sorted,
        // starting from i, and going in reverse order, shift the elements to the right
        // until an element less than unsorted[i] is found
        j = i - 1;
        while (j >= start && itemToInsert < unsorted[j])
        {
            unsorted[j + 1] = unsorted[j];
            j--;
        }
        // insert the element into s[j]
        unsorted[j + 1] = itemToInsert;
        i++;
    }
    return NULL;
}

/**
 * Prints the given array
 */
void printArray(int *list, int size)
{
    int i;
    for (i = 0; i < size - 1; i++)
        printf("%d, ", list[i]);
    printf("%d\n", list[i]);
}