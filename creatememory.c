#include <stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<stdlib.h>
#include <semaphore.h>
#define SEG_SIZE 1024

typedef struct Data70{
  
  sem_t critical70;
  int cnt70;
}SharedData70;

int main()
{
  key_t key70 = ftok("shmfile",65);
  int  shmid70 = shmget(key70, SEG_SIZE, 0666|IPC_CREAT);
  SharedData70 *data_ptr70 = (SharedData70*)shmat(shmid70,NULL,0);
  
  
  sem_init(&(data_ptr70->critical70),1,1);
  data_ptr70->cnt70=1;
  return 0;
}

