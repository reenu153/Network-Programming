#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct student{
  int roll;
  int marks;
}student;

int main() {
    int i, n;
    // ftok to generate unique key
    key_t key = ftok("shmfile",65);
  
    // shmget returns an identifier in shmid
    int shmid = shmget(key,1024,0666|IPC_CREAT);
  
    // shmat to attach to shared memory
    //char *str = (char*) shmat(shmid,(void*)0,0);
    
    student *stud = (student*) shmat(shmid,(void*)0,0);
    
    printf("Input the no of children :");
    scanf("%d", &n);

    for(i=0;i<n;i++)
    {
	stud[i].roll=i+1;
    	printf("\nInput the marks of student %d: ",i+1);
    	scanf("%d",&stud[i].marks);
    }
    stud[i].roll=-1;
    stud[i].marks=-1;
    shmdt(stud);

    return 0;
}
