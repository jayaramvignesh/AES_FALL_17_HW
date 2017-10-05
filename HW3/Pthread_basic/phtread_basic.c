/********************************************
*   Authors: vignesh jayaram
*   date edited: 5th Oct 2017
*
*   file: phtread_basic.c
*
*   description: source file for clone and exec
*      
*      - thread_function
*   
*	
********************************************************/


#include <pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

#define NO_THREADS 4
#define NUM 4
#define RAND_VALUE 1000000

pthread_attr_t thread_attr;

void *thread_function(void *tid)
{
  long thread_id,i,j,result;
  size_t stack_size_value;

  /*----------------PTHREAD_SELF()-----------*/
  printf("\nreturn value of pthread_self is %ld\n",pthread_self());

  /*getting the thread id*/
  thread_id = (long)tid;

  /*----------PTHREAD_ATTR_GET()-------------*/
  /*using get attr to get the stacksize of thread*/
  pthread_attr_getstacksize(&thread_attr,&stack_size_value);

  printf("\nThread %ld: Size of stack is %zu bytes \n",thread_id,stack_size_value);

  /*Random execution*/
  for(i = 0; i< 100000;i++)
  {
     for(j=0;j< 100000;j++)
     {
	      result = RAND_VALUE*i*j;
     }
  }

  /*-------PTHREAD_EXIT(NULL)------*/
  /*terminating the calling thread*/
  pthread_exit(NULL);
}


int main(int argc , char *argv[])
{
  pthread_t threads[NO_THREADS];
  int return_value;
  long i;

  /*initializing threads with default attributes*/
  pthread_attr_init(&thread_attr);


  /*----------PTHREAD_ATTR_GET_DEFAULT()--------------*/
  /*getting default attribute values and printing them*/
  int32_t detached_state; 
  pthread_attr_getdetachstate(&thread_attr,&detached_state);

  size_t guard_size;
  pthread_attr_getguardsize(&thread_attr,&guard_size);

  int32_t sched_policy;
  pthread_attr_getschedpolicy(&thread_attr,&sched_policy);

  /*getting default stack size*/
  size_t stack_size_set;
  pthread_attr_getstacksize(&thread_attr,&stack_size_set);

  printf("\nDEFAULT ATTRIBUTES ARE:\n");
  
  /*check if detached state is JOINABLE or DETACHED*/
  if(detached_state == 0)
  {
    printf("\ndefault state for pthread is JOINABLE\n ");
  }
  
  printf("\ndefault guard size is %zu\n",guard_size);
  
  /*check for scheduling policy*/
  if(sched_policy == 0)
  {
    printf("\ndefault scheduling policy for pthread is SCHED_OTHER\n");
  }

  printf("\nThe default size of stack is %zu bytes\n",stack_size_set);


  /*---------------PTHREAD_ATTR_SET()--------------*/
  /*setting stack size value*/
  stack_size_set =  sizeof(double)*NUM*NUM*RAND_VALUE;
  pthread_attr_setstacksize(&thread_attr,stack_size_set);
  printf("\nsize of stack required now is %zu bytes\n",stack_size_set);


  /*----------------PTHREAD_CREATE()----------*/
  /*creating threads*/
  printf("\nThread creation\n");
  for(i = 0; i < NO_THREADS; i++)
  { 
    return_value = pthread_create(&threads[i], &thread_attr, thread_function, (void *)i);
    if(return_value)
    {
        printf("\nERROR: THREAD CREATION\n");
        exit(-1);
    } 

  } 
  
  
  /*----------PTHREAD_JOIN()---------------*/
  for(i = 0; i < NO_THREADS; i++)
  { 
    pthread_join(threads[i],NULL);
  }

  printf("\nNumber of threads created is %ld\n",i);
  
  pthread_exit(NULL);
  
  return 0;
}


  
