#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(int argc , char *argv[] )
{
    pid_t pid;
    
    if (argc != 2)
    {
        printf("arg missing or exceeding\n");
        exit(0);
    }
    if ( atoi ( argv[1] ) <0 )
    {
        printf("negative number entered %d", atoi(argv[1]));
        exit(0);
    }
    
    pid=fork();
    
    if ( pid<0 )
    {
        printf("failed to create child\n");
        exit(0);
    }
    
    else if ( pid==0 )
    {
       int n = atoi(argv[1]);
        for(int i=1;i<=n;i++)
        if(i%2!=0)
        printf("%d ",i);
        printf("\n");
  
    }
    else
    {
      wait(NULL);
      int  n = atoi(argv[1]);
        for(int i=0;i<=n;i++)
        if(i%2==0)
        printf("%d ",i);
    }
}
