#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include "Processes/mergeSortProcess.c"
#include "Processes/linearSearchProcess.c"
#include "Processes/binarySearchProcess.c"
#include "Processes/quickSortProcess.c"
#include "Processes/bubbleSortProcess.c"

void mergeSortRun()
{
    int shmid;
    key_t key = IPC_PRIVATE;
    int *shm_array;

    int length;

    printf("Enter No of elements of Array:");
    scanf("%d", &length);

    // Calculate segment length
    size_t SHM_SIZE = sizeof(int) * length;

    // Create the segment.
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        _exit(1);
    }

    // Now we attach the segment to our data space.
    if ((shm_array = shmat(shmid, NULL, 0)) == (int *)-1)
    {
        perror("shmat");
        _exit(1);
    }

    // Create a random array of given length
    srand(time(NULL));
    TakingInput(shm_array, length);
    printf("\n");
    // startingTime and endingTime for calculating time for merge sort
    clock_t startingTime, endingTime;
    startingTime = clock();

    // Sort the created array
    mergeSort(shm_array, 0, length - 1);

    endingTime = clock();
    // Check if array is sorted or not
    isSorted(shm_array, length);

    for (int i = 0; i < length; i++)
    {
        printf("%d ", shm_array[i]);
    }
    printf("\n");

    /* Detach from the shared memory now that we are
       done using it. */
    if (shmdt(shm_array) == -1)
    {
        perror("shmdt");
        _exit(1);
    }

    /* Delete the shared memory segment. */
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        _exit(1);
    }
    // calculating time taken in applying merge sort
    printf("Time taken: %f\n", (endingTime - startingTime) / (double)CLOCKS_PER_SEC);
    exit(0);
}

void bubbleSortRun()
{
    int shmid;
    key_t key = IPC_PRIVATE;
    int *shm_array;

    int length;

    printf("Enter No of elements of Array:");
    scanf("%d", &length);

    // Calculate segment length
    size_t SHM_SIZE = sizeof(int) * length;

    // Create the segment.
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        _exit(1);
    }

    // Now we attach the segment to our data space.
    if ((shm_array = shmat(shmid, NULL, 0)) == (int *)-1)
    {
        perror("shmat");
        _exit(1);
    }

    // Create a random array of given length
    srand(time(NULL));
    TakingInput(shm_array, length);
    printf("\n");
    // startingTime and endingTime for calculating time for bubble sort
    clock_t startingTime, endingTime;
    startingTime = clock();

    // Sort the created array
    bubbleSort(shm_array, length);

    endingTime = clock();
    // Check if array is sorted or not
    isSorted(shm_array, length);

    for (int i = 0; i < length; i++)
    {
        printf("%d ", shm_array[i]);
    }
    printf("\n");

    /* Detach from the shared memory now that we are
       done using it. */
    if (shmdt(shm_array) == -1)
    {
        perror("shmdt");
        _exit(1);
    }

    /* Delete the shared memory segment. */
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        _exit(1);
    }
    // calculating time taken in applying merge sort
    printf("Time taken: %f\n", (endingTime - startingTime) / (double)CLOCKS_PER_SEC);
    exit(0);
}

void linearSearchRun()
{
    int shmid;
    key_t key = IPC_PRIVATE;
    int *shm_array;

    int length;

    printf("Enter No of elements of Array:");
    scanf("%d", &length);

    // Calculate segment length
    size_t SHM_SIZE = sizeof(int) * length;

    // Create the segment.
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        _exit(1);
    }

    // Now we attach the segment to our data space.
    if ((shm_array = shmat(shmid, NULL, 0)) == (int *)-1)
    {
        perror("shmat");
        _exit(1);
    }

    // Create a random array of given length
    srand(time(NULL));
    TakingInput(shm_array, length);
    printf("\n");
    // startingTime and endingTime for calculating time for merge sort
    clock_t startingTime, endingTime;
    startingTime = clock();

    int toSearch;
    printf("Enter the key to search:");
    scanf("%d", &toSearch);
    linearSearch(shm_array, length, toSearch);
    endingTime = clock();

    /* Detach from the shared memory now that we are
       done using it. */
    if (shmdt(shm_array) == -1)
    {
        perror("shmdt");
        _exit(1);
    }

    /* Delete the shared memory segment. */
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        _exit(1);
    }
    // calculating time taken in applying linear search
    printf("Time taken: %f\n", (endingTime - startingTime) / (double)CLOCKS_PER_SEC);
    exit(0);
}

void quickSortRun()
{
    int shmid;
    key_t key = IPC_PRIVATE;
    int *shm_array;

    int length;

    printf("Enter No of elements of Array:");
    scanf("%d", &length);

    // Calculate segment length
    size_t SHM_SIZE = sizeof(int) * length;

    // Create the segment.
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        _exit(1);
    }

    // Now we attach the segment to our data space.
    if ((shm_array = shmat(shmid, NULL, 0)) == (int *)-1)
    {
        perror("shmat");
        _exit(1);
    }

    // Create a random array of given length
    srand(time(NULL));
    TakingInput(shm_array, length);
    printf("\n");
    // startingTime and endingTime for calculating time for merge sort
    clock_t startingTime, endingTime;
    startingTime = clock();

    // Sort the created array
    quickSort(shm_array, 0, length - 1);

    endingTime = clock();
    // Check if array is sorted or not
    isSorted(shm_array, length);
    for (int i = 0; i < length; i++)
    {
        printf("%d ", shm_array[i]);
    }
    printf("\n");

    /* Detach from the shared memory now that we are
       done using it. */
    if (shmdt(shm_array) == -1)
    {
        perror("shmdt");
        _exit(1);
    }

    /* Delete the shared memory segment. */
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        _exit(1);
    }
    // calculating time taken in applying merge sort
    printf("Time taken: %f\n", (endingTime - startingTime) / (double)CLOCKS_PER_SEC);
    exit(0);
}

void binarySearchRun()
{
    int shmid;
    key_t key = IPC_PRIVATE;
    int *shm_array;

    int length;

    printf("Enter No of elements of Array:");
    scanf("%d", &length);

    // Calculate segment length
    size_t SHM_SIZE = sizeof(int) * length;

    // Create the segment.
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        _exit(1);
    }

    // Now we attach the segment to our data space.
    if ((shm_array = shmat(shmid, NULL, 0)) == (int *)-1)
    {
        perror("shmat");
        _exit(1);
    }

    // Create a random array of given length
    srand(time(NULL));
    TakingInput(shm_array, length);
    printf("\n");
    // startingTime and endingTime for calculating time for merge sort
    clock_t startingTime, endingTime;
    startingTime = clock();

    // Sort the created array
    mergeSort(shm_array, 0, length - 1);
    printf("After performing merge sort: ");
    for (int i = 0; i < length; i++)
    {
        printf("%d ", shm_array[i]);
    }
    printf("\n");
    int toSearch;
    printf("Enter the key to search:");
    scanf("%d", &toSearch);
    binarySearch(shm_array, length, toSearch);
    endingTime = clock();

    /* Detach from the shared memory now that we are
       done using it. */
    if (shmdt(shm_array) == -1)
    {
        perror("shmdt");
        _exit(1);
    }

    /* Delete the shared memory segment. */
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        _exit(1);
    }

    // calculating time taken in applying binary search
    printf("Time taken: %f\n", (endingTime - startingTime) / (double)CLOCKS_PER_SEC);
    exit(0);
}

int main()
{
    int choice;
    do
    {
        printf(" 1. Merge Sort \n 2. Bubble Sort \n 3. Quick Sort \n 4. Linear Search \n 5. Binary Search \n 6. Exit \n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            mergeSortRun();
            break;
        case 2:
            bubbleSortRun();
            break;
        case 3:
            quickSortRun();
            break;
        case 4:
            linearSearchRun();
            break;
        case 5:
            binarySearchRun();
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    } while (choice != 6);
    return 0;
}
