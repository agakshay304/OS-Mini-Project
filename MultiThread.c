#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "Threads/mergeSortThread.c"
#include "Threads/insertionSortThread.c"
#include "Threads/linearSearchThread.c"
#include "Threads/binarySearchThread.c"
#include "Threads/quickSortThread.c"
#include "Threads/bubbleSortThread.c"

void mergeSortRun()
{
        int i, size;
        NODE n;
        // generating random numbers in array
        srand(time(NULL));
        printf("Enter No of elements of Array:\n");
        scanf("%d", &size);
        printf("Unsorted Array:\n");
        for (i = 0; i < size; i++)
        {
                array[i] = rand() % size;
                printf("%d ", array[i]);
        }
        printf("\n");

        n.i = 0;
        n.j = size - 1;
        pthread_t tid;

        int ret;
        // startingTime and endingTime for calculating time for merge sort
        clock_t startingTime, endingTime;
        startingTime = clock();
        ret = pthread_create(&tid, NULL, mergeSort, &n);
        if (ret)
        {
                printf("%d %s - unable to create thread - ret - %d\n", __LINE__, __FUNCTION__, ret);
                exit(1);
        }

        pthread_join(tid, NULL);
        endingTime = clock();
        printf("Sorted Array:\n");

        for (i = 0; i < size; i++)
                printf("%d ", array[i]);

        printf("\n");

        // calculating time taken in applying merge sort
        printf("Time taken: %f\n", (endingTime - startingTime) / (double)CLOCKS_PER_SEC);
        pthread_exit(NULL);
}

void bubbleSortRun()
{
        int i;
        int N;
        printf("Enter the number of elements in the array: ");
        scanf("%d", &N);
        srand(time(NULL));
        // Filling the array with random integers
        for (i = 0; i < N; i++)
        {
                arr[i] = rand() % 100;
        }
        printf("Unsorted Array:\n");
        for (i = 0; i < N; i++)
        {
                printf("%d ", arr[i]);
        }
        printf("\n");

        pthread_t sorters[2];
        clock_t startingTime, endingTime;
        startingTime = clock();
        printf("Sorted Array :\n");
        for (i = 0; i < 2; i++)
        {
                pthread_create(&sorters[i], NULL, sortArr, (int *)i);
                pthread_join(sorters[i], NULL);
        }
        endingTime = clock();
        printf("Time taken: %f\n", (endingTime - startingTime) / (double)CLOCKS_PER_SEC);
        pthread_exit(NULL);
}

void quickSortRun()
{
        int n;
        printf("Enter the number of elements: ");
        scanf("%d", &n);
        int i;
        srand(time(NULL));
        printf("Unsorted Array:\n");
        for (i = 0; i < n; i++)
        {
                quickarr[i] = rand() % 100;
                printf("%d ", quickarr[i]);
        }

        clock_t t = clock();
        int x = partition(quickarr, 0, n - 1);

        int left_position[2];
        left_position[0] = 0;
        left_position[1] = x - 1;

        int right_position[2];
        right_position[0] = x + 1;
        right_position[1] = n - 1;

        pthread_t left, right;

        pthread_create(&left, NULL, (void *)quicksort, left_position);
        pthread_create(&right, NULL, (void *)quicksort, right_position);

        pthread_join(left, NULL);
        pthread_join(right, NULL);
        t = clock() - t;

        printf("\nSorted Array : \n");
        for (int i = 0; i < n; i++)
        {
                printf("%d ", quickarr[i]);
        }
        printf("\n");
        printf("Time Taken : %.4f\n", (double)t / (double)CLOCKS_PER_SEC);
        pthread_exit(NULL);
}

void linearSearchRun()
{
        pthread_t thread[THREAD_MAX];
        clock_t startingTime, endingTime;
        startingTime = clock();
        for (int i = 0; i < THREAD_MAX; i++)
        { // create multiple threads
                pthread_create(&thread[i], NULL, ThreadSearch, (void *)NULL);
        }
        for (int i = 0; i < THREAD_MAX; i++)
        {
                pthread_join(thread[i], NULL); // wait untill all of the threads are completed
        }
        endingTime = clock();
        if (flag == 1)
                printf("Key found in the array\n");
        else
                printf("Key not found\n");
        printf("Time taken: %f\n", (endingTime - startingTime) / (double)CLOCKS_PER_SEC);
        pthread_exit(NULL);
}

void binarySearchRun()
{
        pthread_t threads[MAX_THREAD];
        clock_t startingTime, endingTime;
        startingTime = clock();

        for (int i = 0; i < MAX_THREAD; i++)
                pthread_create(&threads[i], NULL, binary_search, (void *)NULL);
        for (int i = 0; i < MAX_THREAD; i++)
                pthread_join(threads[i], NULL); // wait, to join with the main thread

        endingTime = clock();

        if (found == 1)
                printf("Key found in the array\n");
        else
                printf("Key not found\n");

        printf("Time taken: %f\n", (endingTime - startingTime) / (double)CLOCKS_PER_SEC);
        pthread_exit(NULL);
}

int main()
{
        int choice;
        do
        {
                printf("1. Merge Sort\n");
                printf("2. Bubble Sort\n");
                printf("3. Quick Sort\n");
                printf("4. Linear Search\n");
                printf("5. Binary Search\n");
                printf("6. Exit\n");
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
                        break;
                }
        } while (choice != 6);

        return 0;
}
