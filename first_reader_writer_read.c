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


pthread_mutex_t readers_critical;
int numreader = 0;





void *reader(void *rno)
{   
    
    pthread_mutex_lock(&readers_critical);
    numreader++;
    if(numreader == 1) {
        sem_wait(&(data_ptr70->critical70)); 
    }
    pthread_mutex_unlock(&readers_critical);
   
    printf("Reader  read cnt as %d\n",data_ptr70->cnt70);

    
    pthread_mutex_lock(&readers_critical);
    numreader--;
    if(numreader == 0) {
        sem_post(&(data_ptr70->critical70)); 
    }
    pthread_mutex_unlock(&readers_critical);
}




int main()
{  
  pthread_t read[10];
    pthread_mutex_init(&readers_critical, NULL);
    

   
 
 
 //SharedData* sdata;
  key_t key = ftok("shmfile",65);
  int  shmid70= shmget(key, SEG_SIZE, 0666|IPC_CREAT);
   data_ptr70 = (SharedData70*)shmat(shmid70,NULL,0);

  
  
 
  
    for(int i = 0; i < 10; i++) {
        pthread_create(&read[i], NULL, (void *)reader,NULL);
    }
   

    for(int i = 0; i < 10; i++) {
        pthread_join(read[i], NULL);
    }
    

    pthread_mutex_destroy(&readers_critical);
    sem_destroy(&(data_ptr70->critical70));

    return 0;
    
}
