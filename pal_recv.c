//read string from the queue and check if palindrome
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
mqd_t q2;
char *str;
struct mq_attr *attr1;
int len;
int flag=0;

attr1 = malloc(sizeof(struct mq_attr));

q2 = mq_open("/palindrome",O_RDWR);

if(q2 == -1)
{
 printf("Error");
}

//The mq_receive() function is used to receive the oldest of the highest priority messages in the queue specified by mqdes. The priori>
str = malloc(10*sizeof(char));
mq_getattr(q2, attr1);

mq_receive(q2,str,attr1->mq_msgsize,NULL);
printf("Message received is: %s\n",str);

len=strlen(str)-1;
//printf("String length=%d",len);
for(int i=0 ; i<=len/2 ; i++)
{
if(str[i] != str[len-i-1])
{
	flag= -1;
	break;
}
}
if(flag != -1)
	printf("The string is palindrome.\n");
else
	printf("The string is NOT palindrome.\n");
}
