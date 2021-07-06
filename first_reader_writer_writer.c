#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<stdlib.h>
#define SEG_SIZE 1024

typedef struct Data70{
  
  sem_t critical70;
  int cnt70;
}SharedData70;


SharedData70 *data_ptr70;








void *writer(void *arg)
{   
    sem_wait(&(data_ptr70->critical70));
    data_ptr70->cnt70 = data_ptr70->cnt70+1;
    printf("cnt value modified by Writer ,new cnt = %d\n",data_ptr70->cnt70);
    sem_post(&(data_ptr70->critical70));

}




int main()
{  
  pthread_t write[5];
    
    

   
 
 

  key_t key = ftok("shmfile",65);
  int  shmid70= shmget(key, SEG_SIZE, 0666|IPC_CREAT);
   data_ptr70 = (SharedData70*)shmat(shmid70,NULL,0);

  
  
 
  
    for(int i = 0; i <5; i++) {
        pthread_create(&write[i], NULL, (void *)writer, NULL);
    }
   

    for(int i = 0; i <5; i++) {
        pthread_join(write[i], NULL);
    }
    

   
    sem_destroy(&(data_ptr70->critical70));

    return 0;
    
}
