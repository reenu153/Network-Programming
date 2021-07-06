#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

void main()
 {
  int p1[2],p2[2];
  pid_t p;
  if(pipe(p1)==-1)
   {
    printf("Pipe1 failed\n");
    return;
   }
  if(pipe(p2)==-1)
   {
    printf("Pipe2 failed\n");
    return;
   }
  p=fork();
  if(p<0)
   {
    printf("Fork() failed\n");
    return;
   }
  else if(p>0)
        {
         close(p1[0]);
         char s[100];
         printf("\nEnter the string ");
         scanf("%[^\n]%*c",s);
         write(p1[1],s,strlen(s)+1);
         close(p1[1]);
         wait(NULL);
         read(p2[0],s,100);
         close(p2[0]);
         close(p2[1]);
         close(p1[1]);
         printf("\nConcatenated string is %s",s);
        }
       else
       {
        close(p1[1]);
        char c[100],s[100];
        int i,k;
        read(p1[0],s,100);
        printf("\nEnter the remaining part");
        scanf("%[^\n]%*c",c);
        k=strlen(s);
        for(i=0;i<strlen(c);i++)
         s[k++]=c[i];
        s[k]='\0';
        write(p2[1],s,strlen(s)+1);
        close(p2[1]);
        close(p1[1]);
        close(p1[0]);
        exit(0);
       }
 }
