// Preference is given to the writer. the constraint is added that no writer, once added to the queue, shall be kept waiting longer than absolutely necessary.
// This is also called writers-preference.

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

sem_t read_protect; //for controlling access to critical sessions in reading
sem_t write_protect; //for controlling access to critical sessions in writing
sem_t item_protect; //for controlling access to item

int item=0; //shared item
int write_waiting=0; //count of currently waiting write thread
int read_waiting=0; //count of currently waiting read thread

key_t key;
int shmid;

void* writer(void* tid) {
    int* id=(int*) tid;

    //write_waiting++; --> writing this statement here will starve the readers i.e. readers will only get a chance after all the writers have finished execution.
    //lock writer
    sem_wait(&write_protect);
    write_waiting++;

    //locking item
    sem_wait(&item_protect);

    key = ftok("shmfile",65);

    // shmget returns an identifier in shmid
    shmid = shmget(key,1024,0666|IPC_CREAT);

    // shmat to attach to shared memory
    int *num = (int*) shmat(shmid,(void*)0,0);

    item++;     // updating item
    *num = item;

    printf("Data written in memory: %d\n",*num);

    shmdt(num);

    sem_post(&item_protect);//unclocking item_protect

    write_waiting--; //removing current write thread from wait

    sem_post(&write_protect);

}

void* reader(void* tid) {

    int* id=(int*) tid;

    sem_wait(&read_protect);//locking read_waiting
    //critical session of read_waiting->start

    while(write_waiting);
    read_waiting++;

    sem_wait(&item_protect);
    //critical session of item->start

    key = ftok("shmfile",65);

    shmid = shmget(key,1024,0666|IPC_CREAT);

    int *num = (int*) shmat(shmid,(void*)0,0);

    printf("Data read from memory: %d\n",*num);

    sem_post(&item_protect);

    read_waiting--;
    //critical session of read_waiting->end
    sem_post(&read_protect);

}


void main() {
    //initialising all semaphores
    sem_init(&write_protect,0,1);
    sem_init(&read_protect,0,1);
    sem_init(&item_protect,0,1);

    int rnum, wnum;
    int a[10] = {1,2,3,4,5,6,7,8,9,10}; // numbers for Readers and Writers.

    pthread_t read[100]; //to store ids of read threads
    pthread_t write[100]; //to store ids of write threads

    printf("Enter the number of readers : ");
    scanf("%d", &rnum);
    printf("\nEnter the number of writers : ");
    scanf("%d", &wnum);
    printf("\n");

    //creating read & write threads
    for(int i = 0; i < rnum; i++) {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
    }

    for(int i = 0; i < wnum; i++) {
        pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
    }

    //making parent thread wait before semaphore & mutex is destroyed
    for(int i = 0; i < rnum; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < wnum; i++) {
        pthread_join(write[i], NULL);
    }

    //destroy semaphore and shared memory
    sem_destroy(&read_protect);
    sem_destroy(&write_protect);
    shmctl(shmid,IPC_RMID,NULL);
    pthread_exit(NULL);
}
