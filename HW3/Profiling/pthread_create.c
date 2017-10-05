/********************************************
*   Authors: vignesh jayaram
*   date edited: 5th Oct 2017
*
*   file: pthread_create.c
*
*   description: source file for pthread_create
*      
*      - thread_function
*   
*	
********************************************************/


#define _GNU_SOURCE

#include <pthread.h>
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


/*Thread function*/
void *thread_function(void *data) 
{
  printf("\nENTER: THREAD FUNCTION\n");
  pthread_exit(NULL);
}


int main(int argc , char *argv[])
{
  int32_t return_value;
  pthread_t thread1;
  
  clock_t start;
  clock_t end;

 /*starting time*/
  start= clock();
  
  printf("\nstart time %ld\n",start);
 
  /*create thread*/
  return_value = pthread_create(&thread1, NULL , thread_function,"hello");  
  if(return_value)
  {
       printf("\nERROR: THREAD CREATION\n");
       exit(-1);
  } 
  
  /*wait for child terminate*/
  pthread_join(thread1,NULL);
  
  /*end time*/
  end =  clock();
  printf("\nend time %ld\n",end);

  /*time to taken for create+function execution*/
  long int diff = (long)(end-start); 
  printf("\nTime taken for pthread_create is %ld\n\n",diff);

  /*exit*/
  pthread_exit(NULL);
  
  printf("\nEND OF PROGRAM\n");
  return 0;
}


 
