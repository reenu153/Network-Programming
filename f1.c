#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
if(fork()&&fork())
{
fork();
printf("inside");
fork();
}
printf("out");
}
