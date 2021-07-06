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

	printf("Pipe1 failed");
	return;

   }

  if(pipe(p2)==-1)

   {

	printf("Pipe2 failed");
	return;

   }

  p=fork();

  if(p<0)

   {

	printf("Fork() failed");
	return;

   }

  else if(p>0)

    	{

     	close(p1[0]);

     	char str[100],ans[100];
     	int l,c,w;

     	printf("Enter the string ");
     	scanf("%[^~]",str);
     	write(p1[1],str,(strlen(str)+1));
     	close(p1[1]);
     	wait(NULL);
     	read(p2[0],&ans,100);
  	printf("%s",ans);
     	close(p2[0]);
    	}

   	else
    	{
     	close(p1[1]);
     	char str[100],ans[10],f;
     	int i=0,c=0,w=1,l=1;
     	FILE *fptr;
     	fptr=fopen("output.txt","w");

     	if(fptr==NULL)

      	{
       	printf("error");
       	exit(1);
      	}

     	read(p1[0],str,100);
     	while(str[i]!='\0')
      	{
       	if(str[i]=='\n')
        	{

        	l++;        	     	 
        	}

       	else if(str[i]==' ')
             	w++;
            	else
             	c++;
       	i++;

      	}

    	close(p1[0]);
     	close(p2[0]); 	 

     	fprintf(fptr,"l=%d\n",l);
        fprintf(fptr,"w=%d\n",w);
     	fprintf(fptr,"c=%d\n",c);

     	fclose(fptr);
     	fptr=fopen("output.txt","r");

     	while((f=getc(fptr))!=EOF)

      	{
       	if(write(p2[1],&f,1)<1)

       	{

        	printf("Writing from file failed");
        	exit(EXIT_FAILURE);

       	}

      	}

    	close(p2[1]);
    	fclose(fptr);
    	exit(0);
    	}

 }
