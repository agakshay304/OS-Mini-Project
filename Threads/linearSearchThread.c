#include <stdio.h>
#include <pthread.h>
#define MAX 16
#define THREAD_MAX 4
int array[MAX] = {1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220};
int key=7;
int flag = 0; // flag to indicate that item is found in the array or not
int current_thread = 0;
void *ThreadSearch(void *args)
{ // This is linear search function. It will be running using all threads
    int num = current_thread++;
    for (int i = num * (MAX / 4); i < ((num + 1) * (MAX / 4)); i++)
    {
        if (array[i] == key)
            flag = 1; // set flag if key is found
    }
}
