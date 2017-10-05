/********************************************
*   Authors: vignesh jayaram
*   date edited: 5th Oct 2017
*
*   file: clone_exec.c
*
*   description: source file for clone and exec
*      
*      - child_function
*   
*	
********************************************************/



#define _GNU_SOURCE

#include <sched.h>
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


#define STACK_SIZE (1024*1024)

/*function process calls after forking*/
int child_function(char *arg, char** task_list)
{
   /*call exec*/
   printf("\nCHILD PROCESS: STARTED!!\n");
   execvp(arg,task_list);
}


int main()
{
  
  char *stack;
  char *stack_head;

  /*create a stack on heap*/
  stack = (char *)malloc(STACK_SIZE);

  if(stack == NULL)
  {
    printf("ERROR: MALLOC");
  }

  stack_head = stack + STACK_SIZE - 1;


  /*list to pass*/
  char* task_list[] = { "ls","./hello", "-l", "/", NULL};


  clock_t start;
  clock_t end;

  pid_t child_process_id;

  /*starting time*/
  start= clock();
  
  printf("\nstart time %ld\n",start);
 
  /*create a proces using clone*/
  child_process_id = clone(child_function,stack_head,SIGCHLD,task_list[1],task_list);

  if(child_process_id == -1)
  {
    printf("\nERROR:FORK\n");
    exit(1);
 }

 /*wait for child process to terminate*/
 if(waitpid(child_process_id,NULL,0) == -1)
 {
      printf("\nERROR: WAITPID\n");
      exit(1);
  }

 end =  clock();
 printf("\nend time %ld\n",end);

 /*calculate time taken for clone+exec*/
 long int diff = (long)(end-start); 
 printf("\nTime taken for clone and exec is %ld\n\n",diff);

 /*free allocated memory*/
 free(stack);
 return 0;

}


