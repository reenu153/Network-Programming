#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
mqd_t q2;
char *msg;
struct mq_attr *attr1;
int prty;
attr1 = malloc(sizeof(struct mq_attr));

q2 = mq_open("/messages",O_RDWR);

if(q2 == -1) 
{
 printf("Error");
}

//The mq_receive() function is used to receive the oldest of the highest priority messages in the queue specified by mqdes. The priority of the message received is put in the location pointed to by msg_prio, the data itself in the location pointed to by msg_ptr, and the size received is returned.

msg = malloc(10*sizeof(char));
mq_getattr(q2, attr1);

mq_receive(q2,msg,attr1->mq_msgsize,&prty);
printf("Message = %s has Priority= %d\n",msg,prty);


mq_receive(q2,msg,attr1->mq_msgsize,&prty);
printf("Message = %s has Priority= %d\n",msg,prty);


mq_receive(q2,msg,attr1->mq_msgsize,&prty);
printf("Message = %s has Priority= %d\n",msg,prty);

}
