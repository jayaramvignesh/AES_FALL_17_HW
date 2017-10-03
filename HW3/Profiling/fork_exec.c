#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<stdbool.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/times.h>
#include<time.h>


int main()
{
  
  /*list to pass*/
  char* task_list[] = { "./hello", "-l", "/", NULL};


  clock_t start;
  clock_t end;

  pid_t child_process_id;


  /*starting time*/
  start= clock();
  printf("\nstart time %ld\n",start);

  /*calculate id*/
  child_process_id = fork();

  if(child_process_id == -1)
  {
    printf("\nERROR:FORK\n");
    exit(1);
   }
  else if(child_process_id == 0)
  {
    /*call exec command*/
    printf("\nCHILD PROCESS: STARTED!!\n");
    execvp(task_list[0],task_list);
  }
  else
  {
     /*wait child process to terminate*/
     if(waitpid(child_process_id,NULL,0) == -1)
     {
        printf("\nERROR: WAITPID\n");
        exit(1);
     }

    end =  clock();
    printf("\nend time %ld\n",end);

    /*time taken for fork+exec */
    printf("\nTOTAL TIME TAKEN %ld\n",(end-start));
  
     printf("\nEND OF PROGRAM\n");
 }
}


