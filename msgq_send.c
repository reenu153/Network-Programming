#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include <string.h>

int main() {

	mqd_t q1;
	//Like pipes and FIFOs, all message queue operations are performed based on message queue descriptors (an mqd_t). In the QNX implementation, an mqd_t is a file descriptor.
	
	char msg1[20], msg2[20], msg3[20];
	int prty1, prty2, prty3;

	printf("Input message one : ");
	fgets(msg1, 30, stdin);
        printf("Input message two : ");
        fgets(msg2, 30, stdin);
        printf("Input message three : ");
        fgets(msg3, 30, stdin);
        printf("\nInput the priority of msg1: ");
        scanf("%d",&prty1);
        printf("Input the priority of msg2: ");
        scanf("%d",&prty2);
        printf("Input the priority of msg3: ");
        scanf("%d",&prty3);

	q1 = mq_open("/messages",O_CREAT|O_RDWR,0666,NULL);  //name,flag,mode,attribute
	if(q1 == -1) {
	 printf("Error");
	}

	//The mq_send() function puts a message of size msg_len, pointed to by msg_ptr(arg2) into the queue indicated by mq_des(arg1). The new message has a priority of msg_prio.
	
	mq_send(q1,msg1,strlen(msg1),prty1);
	mq_send(q1,msg2,strlen(msg2),prty2);
	mq_send(q1,msg3,strlen(msg3),prty3);

}

