#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

void insertionSort(int arr[], int n);
void merge(int arr[], int low1, int high1, int high2);

void mergeSort(int arr[], int low, int high)
{
    int i, len = (high - low + 1);

    // Using insertion sort for small sized array
    if (len <= 5)
    {
        insertionSort(arr + low, len);
        return;
    }

    pid_t lpid, rpid;
    lpid = fork();
    if (lpid < 0)
    {
        // Lchild proc not created
        perror("Left Child Proc. not created\n");
        _exit(-1);
    }
    else if (lpid == 0)
    {
        // printf("Left Process Running \n ");
        mergeSort(arr, low, low + len / 2 - 1);
        _exit(0);
    }
    else
    {
        rpid = fork();
        if (rpid < 0)
        {
            // Rchild proc not created
            perror("Right Child Proc. not created\n");
            _exit(-1);
        }
        else if (rpid == 0)
        {
            // printf("Right Process Running \n ");
            mergeSort(arr, low + len / 2, high);
            _exit(0);
        }
    }

    int status;

    // Wait for child processes to finish
    waitpid(lpid, &status, 0);
    waitpid(rpid, &status, 0);

    // Merge the sorted subarrays
    merge(arr, low, low + len / 2 - 1, high);
}

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Method to merge sorted subarrays
void merge(int arr[], int low1, int high1, int high2)
{
    // We can directly copy  the sorted elements in the final array, no need for a temporary sorted array.
    int count = high2 - low1 + 1;
    int sortedArray[count];
    int i = low1, k = high1 + 1, m = 0;
    while (i <= high1 && k <= high2)
    {
        if (arr[i] < arr[k])
            sortedArray[m++] = arr[i++];
        else if (arr[k] < arr[i])
            sortedArray[m++] = arr[k++];
        else if (arr[i] == arr[k])
        {
            sortedArray[m++] = arr[i++];
            sortedArray[m++] = arr[k++];
        }
    }

    while (i <= high1)
        sortedArray[m++] = arr[i++];

    while (k <= high2)
        sortedArray[m++] = arr[k++];

    int arr_count = low1;
    for (i = 0; i < count; i++, low1++)
        arr[low1] = sortedArray[i];
}

// To check if array is actually sorted or not
void isSorted(int arr[], int len)
{
    if (len == 1)
    {
        printf("Sorting Done Successfully\n");
        return;
    }

    int i;
    for (i = 1; i < len; i++)
    {
        if (arr[i] < arr[i - 1])
        {
            printf("Sorting Not Done\n");
            return;
        }
    }
    printf("Sorting Done Successfully\n");
    return;
}

// To fill randome values in array for testing purpose
void TakingInput(int arr[], int len)
{
    // Create randomly generated array
    int i;
    for (i = 0; i < len; i++)
    {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    return;
}
