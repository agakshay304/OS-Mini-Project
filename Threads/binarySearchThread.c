#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 16
#define MAX_THREAD 4

int arr[] = {1, 6, 8, 11, 13, 14, 15, 19, 21, 23, 26, 28, 31, 65, 108, 220};
int ele = 100;
int part = 0;
int found = 0;

void *binary_search()
{
    // There are four threads, each will take 1/4th part of the list
    int thread_part = part++;
    int mid;
    int start = thread_part * (MAX / 4); // set start and end using the thread part
    int end = (thread_part + 1) * (MAX / 4);

    while (start < end && !found)
    { 
        // if some other thread has got the element, it will stop
        mid = (end - start) / 2 + start;
        if (arr[mid] == ele)
        {
            found = true;
            break;
        }
        else if (arr[mid] > ele)
            end = mid - 1;
        else
            start = mid + 1;
    }
}
