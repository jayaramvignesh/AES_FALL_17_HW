#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define COUNT_DONE 10
#define COUNT1 3
#define COUNT2 6

int counter = 0;

pthread_mutex_t count_mutex;
pthread_cond_t count_cond;

void *function1()
{
  for(;;)
  {
    /*--------------PTHREAD_MUTEX_LOCK---------------*/
    pthread_mutex_lock(&count_mutex);
	  counter++;

    /*if count is less than 3  or greater than 6 then signal condition*/
    if(counter < COUNT1 || counter > COUNT2)
    {
      /*---------------PTHREAD_COND_BROADCAST----------------*/
      pthread_cond_broadcast(&count_cond);
    }
    
    
	  printf("FUNCTION 1: COUNTER VALUE = %d \n",counter);
	  
    /*-------------PTHREAD_MUTEX_UNLOCK----------------*/
    pthread_mutex_unlock(&count_mutex);
	  sleep(1);

    if(counter >= COUNT_DONE)
	  {
		  pthread_exit(NULL);
	  }
  
  }
}

void *function2()
{
  for(;;)
  {

    /*--------------PTHREAD_MUTEX_LOCK---------------*/
    /* If PTHREAD_MUTEX_TRYLOCK is used, then it does not block the function.
       It either succeeds and gets the lock or it fails.*/
    pthread_mutex_lock(&count_mutex);
    
    /*Wait when counter is greater than 3 and less than 6*/
    while(counter >= COUNT1 && counter <= COUNT2)
    {
       /*--------------PTHREAD_COND_WAIT-----------------*/
       pthread_cond_wait(&count_cond,&count_mutex); 
    } 
	  
    counter++;
	  printf("FUNCTION 2: COUNTER VALUE = %d \n",counter);
	  
    /*--------------PTHREAD_MUTEX_UNLOCK---------------*/
    pthread_mutex_unlock(&count_mutex);

	  if(counter >= COUNT_DONE)
	  {
		  pthread_exit(NULL);
	  }
  
  }
}


int main()
{
  pthread_t thread1,thread2;

  /*----------------PTHREAD_MUTEX_INIT------------------------*/
  if(pthread_mutex_init(&count_mutex,NULL)!=0)
  {
      printf("\n MUTEX INIT FAILED \n");
      return -1;
  }

  /*----------------PTHREAD_COND_INIT------------------------*/
  if(pthread_cond_init(&count_cond,NULL)!=0)
  {
      printf("\n CONDITION INIT FAILED \n");
      return -1;
  }


  int iret1,iret2;
  
  if((iret1 = pthread_create(&thread1, NULL, &function1,NULL)))
  {
	  printf("Thread 1 creation failed\n");
  }
  
  if((iret2 = pthread_create(&thread2, NULL, &function2, NULL)))
  {
	  printf("Thread 2 creation failed\n");
  }
  
  /*main thread waits till parent thread terminates*/
  pthread_join(thread1,NULL);
  pthread_join(thread2,NULL);  
  
  /*---------------PTHREAD_MUTEX_DESTROY-------------------*/
  pthread_mutex_destroy(&count_mutex);

  /*---------------PTHREAD_COND_DESTROY--------------------*/
  pthread_cond_destroy(&count_cond);

  pthread_exit(NULL);

}
