#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
int A[10][10],B[10][10],C[10][10],m1,n1,m2,n2,i,j,k,prod;

void mult(void* arg)
{
    prod = A[i][k]*B[k][j];
    
}
void main()
{
    pthread_t id1;
    printf("Enter the no of rows of first matrix");
    scanf("%d",&n1);
    printf("\nEnter the no of columns of first matrix");
    scanf("%d",&m1);
    for(i=0;i<n1;i++)
    {
        for(j=0;j<m1;j++)
        { printf("\nEnter element at row %d column %d",i+1,j+1);
            scanf("%d",&A[i][j]);
        }
    }
    
    printf("\nEnter the no of rows of second matrix");
    scanf("%d",&n2);
    printf("\nEnter the no of columns of second matrix");
    scanf("%d",&m2);
    for(i=0;i<n2;i++)
    {
        for(j=0;j<m2;j++)
        { printf("\nEnter element at row %d column %d",i+1,j+1);
            scanf("%d",&B[i][j]);
        }
    }
    if(m1==n2)
    {
        for(i=0;i<n1;i++)
            for(j=0;j<m2;j++)
                C[i][j]=0;
        
        for(i=0;i<n1;i++)
            for(j=0;j<m2;j++)
                for(k=0;k<n2;k++)
                {
                    
                    pthread_create(&id1,NULL,mult,NULL);
                    pthread_join(id1,NULL);
                    C[i][j]+=prod;
                }
        
    }
    else
        printf("invalid");
    
    for(i=0;i<n1;i++)
    {
        printf("\n");
        for(j=0;j<m2;j++)
            printf("%d ",C[i][j]);
    }
    
}
