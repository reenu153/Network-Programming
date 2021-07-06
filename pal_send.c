//accept a string from standard input,pass the string into the message queue
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <stdio.h>
#include <string.h>

int main() {

        mqd_t q1;
        //Like pipes and FIFOs, all message queue operations are performed based on message queue descriptors (an mqd_t). In the QNX i>
        char str[40];

        printf("Input a string : ");
        fgets(str, 30, stdin);
        q1 = mq_open("/palindrome",O_CREAT|O_RDWR,0666,NULL);  //name,flag,mode,attribute
        if(q1 == -1) 
	{
         printf("Error");
        }

        //The mq_send() function puts a message of size msg_len, pointed to by msg_ptr(arg2) into the queue indicated by mq_des(arg1).>
        mq_send(q1,str,strlen(str),0);

}

