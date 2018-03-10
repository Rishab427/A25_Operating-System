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
void function(int *p)
{
    printf("thread %d \n",*p);
    pthread_mutex_lock(&mutex);
    printf("Modified value of Available %d \n",++a);
    pthread_cond_signal( &cond ); 
    pthread_mutex_unlock( & mutex );
    pthread_exit(0);  
}

void Safeseq(int P,int R,int processes[P], int avail[R], int maxm[][R],int allot[][R])
{
    int i;
    pthread_t th[P];
    bool sf=true;
    int need[P][R];

    calculateneed(P,R,need, maxm, allot);

  
    bool finish[P];

    for(i=0;i<P;i++)
       {
          finish[i]=false;
       } 

   
    int safeSeq[P];

    
    int work[R];
    for (i = 0; i < R ; i++)
        work[i] = avail[i];

     int count = 0;
     while (count < P)
     {
       int p;
         bool found = false;
         for (p = 0; p < P; p++)
         {
            
             if (finish[p] == false)
             {
               
                int j;
                 for (j = 0; j < R; j++)
                     if (need[p][j] > work[j])
                        break;

                
                 if (j == R)
                 {
                 	int k;
                     for ( k = 0 ; k < R ; k++)
                         work[k] =work[k]+allot[p][k];

                   
                     safeSeq[count++] = p;

                  
                     finish[p] = true;

                     found = true;
                }
            }
        }

   
         if (found == false)
         {
             printf("System is not in safe state (Deadlock)");
             sf=false;
             break;
        }
    }
    printf("Hurrah!System is in safe state.\nSafe"
          " sequence is: ");
          
    for (i = 0; i < P ; i++)
         printf("%d ",safeSeq[i]);
    printf("\n");
    int j=0,k=0,l=0;
 if(sf)
   {  
    pthread_t th[P];
    int g=0;
    for( i=0;i<P;i++)
     {
      g=safeSeq[i];
      pthread_create(&th[safeSeq[i]],NULL,function,&g);
      pthread_join(th[safeSeq[i]],NULL);
    }
     pthread_mutex_init(&mutex,NULL);
     while(a<=P)
    {
    pthread_cond_wait( & cond, & mutex ); 
    }
    pthread_mutex_unlock( & mutex );
  }
}
