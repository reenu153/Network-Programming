#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SEG_SIZE 1024

typedef struct StudentDetails {
  char name[10];
  char id[5];
  int rank;
}StudentDet;

int toInt(char* operand) {
  int val=0;
  int temp=0;
  int len=strlen(operand);
  for(int i=0;i<len;i++) {
    val*=10;
    val+=(operand[i]-'0');
  }
  return val;
}

void cleanString(char* str) {
  int str_len=strlen(str);
  if(str[str_len-1]=='\n') {
    str[str_len-1]='\0';
  }
}

void displayDetails(StudentDet* s_details, int n) {
  for(int i=0;i<n;i++) {
    printf("\nStudent no: %d\n",i+1);
    printf("Name: %s\n",s_details[i].name);
    printf("ID: %s\n",s_details[i].id);
    printf("Rank: %d\n",s_details[i].rank);

  }
}

void get_string(char* str) {

  fgets(str,50,stdin);
  if(strcmp(str,"\n")==0) {
    fgets(str,50,stdin);
  }
  int str_len=strlen(str);
  if(str[str_len-1]=='\n') {
    str[str_len-1]='\0';
  }
}
int splitAllStudents(char* str,StudentDet* s_details) {
  int l=0;
  int i=0;
  while(str[i]!='\0') {
    while(str[i]!=';') {
      int k=0;
      char name[10];
      char id[5];
      char rank_str[5];
      while(str[i]!='|') {
        name[k]=str[i];
        k++;
        i++;
      }
      name[k]='\0';
      i++;
      k=0;
      while(str[i]!='|') {
        id[k]=str[i];
        k++;
        i++;
      }
      id[k]='\0';
      i++;
      k=0;
      while(str[i]!=';') {
        rank_str[k]=str[i];
        k++;
        i++;
      }
      rank_str[k]='\0';
      strcpy(s_details[l].name,name);
      strcpy(s_details[l].id,id);
      s_details[l].rank=toInt(rank_str);
      l++;
    }
    i++;
  }
  return l;
}
void swap(StudentDet* std1, StudentDet* std2)
{
    StudentDet temp;
    strcpy(temp.name,std1->name);
    strcpy(temp.id,std1->id);
    temp.rank=std1->rank;

    strcpy(std1->name,std2->name);
    strcpy(std1->id,std2->id);
    std1->rank=std2->rank;

    strcpy(std2->name,temp.name);
    strcpy(std2->id,temp.id);
    std2->rank=temp.rank;

}
void bubbleSort(StudentDet* s_details, int n)
{
   int i, j;
   for (i = 0; i < n-1; i++) {
     for (j = 0; j < n-i-1; j++){
       if (s_details[j].rank > s_details[j+1].rank){
         swap(&s_details[j], &s_details[j+1]);
       }
     }
   }
}

void main() {
  char str[100];
  int n;
  StudentDet* s_details = (StudentDet*)malloc(10*sizeof(StudentDet));
  key_t key = ftok("shmfile",65);
  int  shmid = shmget(key, SEG_SIZE, 0666|IPC_CREAT);
  char *data_ptr = (char*) shmat(shmid,NULL,0);
  cleanString(data_ptr);

  printf("Data read from memory: %s\n",data_ptr);

  n=splitAllStudents(data_ptr, s_details);
  displayDetails(s_details,n);

  printf("After sorting\n\n");
  bubbleSort(s_details,n);
  displayDetails(s_details,n);
  shmdt(str); //detaching str from segment

    // destroy the shared memory
  shmctl(shmid,IPC_RMID,NULL); //destroying the created segment

  printf("Successful\n");

}
