#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SEG_SIZE 1024

//Student structure
typedef struct StudentDetails {
  char name[10];
  char id[5];
  int rank;
}StudentDet;

//reading input from stdin
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

//collecting details of n students
void collectStudentDetails(StudentDet* s_details, int n) {
  for(int i=1;i<=n;i++) {
    printf("\nDetails of Student %d\n",i);
    printf("Enter name: ");
    get_string(s_details[i-1].name);
    printf("Enter id: ");
    get_string(s_details[i-1].id);
    printf("Enter rank: ");
    scanf("%d",&s_details[i-1].rank);
  }
}

//displaying all the collected details
void displayDetails(StudentDet* s_details, int n) {
  for(int i=0;i<n;i++) {
    printf("\nStudent no: %d\n",i+1);
    printf("Name: %s\n",s_details[i].name);
    printf("ID: %s\n",s_details[i].id);
    printf("Rank: %d\n",s_details[i].rank);

  }
}
//combinging deatils of one student
void combineOneStudent(StudentDet stud,char* str) {
  sprintf(str,"%s|%s|%d;",stud.name,stud.id,stud.rank);
}

//combining all the deatils
void combineAllStudents(StudentDet* s_details, int n, char*str) {
  strcpy(str,"");
  char temp_str[20];
  for(int i=0;i<n;i++) {
    combineOneStudent(s_details[i],temp_str);
    strcat(str,temp_str);
  }
}

void main() {
  //char str[50];
  StudentDet* s_details;
  key_t key = ftok("shmfile",65);
  int  shmid = shmget(key, SEG_SIZE, 0666|IPC_CREAT);
  int n;
  char str[100];
  printf("Enter the number of students ");
  scanf("%d",&n);

  char *data_ptr = (char*) shmat(shmid,NULL,0);
  s_details = (StudentDet*)malloc(n*sizeof(StudentDet));
  collectStudentDetails(s_details, n);

  printf("Collected Details\n");
  displayDetails(s_details, n);
  combineAllStudents(s_details, n, data_ptr);
  //data_ptr=str;

  printf("Data send: %s\n",data_ptr );
  shmdt(data_ptr);
  printf("Successful\n");

}
