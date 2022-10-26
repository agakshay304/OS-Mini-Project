#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define NOOFTHREADS 2
#define MAX_SIZE 50
int array[MAX_SIZE];

typedef struct node
{
        int i;
        int j;
} NODE;

void merge(int i, int j)
{
        int mid = (i + j) / 2;
        int k = i;
        int l = mid + 1;

        int newarray[j - i + 1], newK = 0;

        while (k <= mid && l <= j)
        {
                if (array[k] > array[l])
                        newarray[newK++] = array[l++];
                else
                        newarray[newK++] = array[k++];
        }

        while (k <= mid)
        {
                newarray[newK++] = array[k++];
        }

        while (l <= j)
        {
                newarray[newK++] = array[l++];
        }

        for (k = 0; k < (j - i + 1); k++)
                array[i + k] = newarray[k];
}

void *mergeSort(void *a)
{
        NODE *p = (NODE *)a;
        NODE n1, n2;
        int mid = (p->i + p->j) / 2;
        pthread_t tid1, tid2;
        int ret;

        n1.i = p->i;
        n1.j = mid;

        n2.i = mid + 1;
        n2.j = p->j;

        if (p->i >= p->j)
                return 0;

        // creating first thread
        ret = pthread_create(&tid1, NULL, mergeSort, &n1);
        if (ret)
        {

                printf("%d %s - unable to create thread - ret - %d\n", __LINE__, __FUNCTION__, ret);
                exit(1);
        }

        // creating second thread
        ret = pthread_create(&tid2, NULL, mergeSort, &n2);
        if (ret)
        {
                printf("%d %s - unable to create thread - ret - %d\n", __LINE__, __FUNCTION__, ret);
                exit(1);
        }
        // joining the threads
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        merge(p->i, p->j);
        pthread_exit(NULL);
}