#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
int a=100;
pthread_mutex_t mutex;
pthread_cond_t cond;
void calculateneed(int P,int R,int need[P][R], int max[P][R],int allocation[P][R])
{
	int i,j;
    for ( i = 0 ; i < P ; i++)
        for ( j = 0 ; j < R ; j++)
            need[i][j] = max[i][j] - allocation[i][j];
    printf("need of processes\n");
    for (i = 0 ; i < P ; i++)
        {
          for ( j = 0 ; j < R ; j++)
              {
                   printf("%d ",need[i][j]);
              }
          printf("\n");
        }
}
