#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "Threads/mergeSortThread.c"
#include "Threads/insertionSortThread.c"
#include "Threads/linearSearchThread.c"
#include "Threads/binarySearchThread.c"
#include "Threads/quickSortThread.c"

void mergeSortRun()
{
        int i;
        NODE n;
        // generating random numbers in array
        srand(time(NULL));
        printf("Unsorted Array:\n");
        for (i = 0; i < MAX_SIZE; i++)
        {
                array[i] = rand() % 100;
                printf("%d ", array[i]);
        }
        printf("\n");

        n.i = 0;
        n.j = MAX_SIZE - 1;
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

        for (i = 0; i < MAX_SIZE; i++)
                printf("%d ", array[i]);

        printf("\n");

        // calculating time taken in applying merge sort
        printf("Time taken: %f\n", (endingTime - startingTime) / (double)CLOCKS_PER_SEC);
        pthread_exit(NULL);
}

void insertionSortRun()
{
        // fill the unsorted array
        fillArray(SIZE);
        printArray(unsorted, SIZE);

        // define the indices of the two sublists
        int start1 = 0,
            end1 = SIZE / 2,
            start2 = end1 + 1,
            end2 = SIZE - 1;

        // 2 sorting threads, and 1 merge thread
        pthread_t threads[3];

        // prepare sorting params and fire off sorting threads
        struct insertionSortParams sArgs[2];
        clock_t startingTime, endingTime;
        startingTime = clock();
        sArgs[0].start = start1;
        sArgs[0].end = end1;
        pthread_create(&threads[0], NULL, insertionSort, &sArgs[0]); // deal with first sublist

        sArgs[1].start = start2;
        sArgs[1].end = end2;
        pthread_create(&threads[1], NULL, insertionSort, &sArgs[1]); // deal with second sublist

        // wait for sorting threads to terminate
        pthread_join(threads[0], NULL);
        pthread_join(threads[1], NULL);

        endingTime = clock();

        // prepare params and fire off merging thread
        struct mergeInsertionParams mArgs;
        mArgs.begin = start1;
        mArgs.mid = start2;
        mArgs.end = end2;
        pthread_create(&threads[2], NULL, mergeInsertion, &mArgs); // merge the sublists into sorted[]!

        // wait for merging thread to terminate
        pthread_join(threads[2], NULL);

        // main thread prints out the sorted array
        printArray(sorted, SIZE);

        printf("Time taken: %f\n", (endingTime - startingTime) / (double)CLOCKS_PER_SEC);
}

void quickSortRun()
{
        int n;
        n = 90;
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
        printf("Time Taken : %.4f", (double)t / (double)CLOCKS_PER_SEC);
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
}

int main()
{
        int choice;
        do
        {
                printf("1. Merge Sort\n");
                printf("2. Insertion Sort\n");
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
                        insertionSortRun();
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
