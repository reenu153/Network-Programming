#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
int matA[4][4];
int matB[4][4];
int matC[4][4];
int step=0;
void* multi(void* arg)
{
    int c=step++;
    int *n= (int*)arg;
    int x= *n;
    for (int i = c; i < (c + 1) ; i++)
        for (int j = 0; j < x; j++)
            for (int k = 0; k < x; k++)
                matC[i][j] += matA[i][k] * matB[k][j];
}

int main()
{
    int x;
    printf("Input the side  of the matrix : \n");
    scanf("%d",&x);
    printf("Input the first matrix: \n");
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<x;j++)
        {
            scanf("%d",&matA[i][j]);
        }
    }
    printf("Input the second matrix: \n");
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<x;j++)
        {
            scanf("%d",&matB[i][j]);
        }
    }
    
    pthread_t t[x];
    
    for(int i=0;i<x;i++)
    {
        pthread_create(&t[i],NULL,multi,&x);
    }
    
    for(int i=0;i<x;i++)
    {
        pthread_join(t[i],NULL);
    }
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<x;j++)
        {
            printf("%d\t\n",matC[i][j]);
        }
        printf("\n");
    }
    
}

