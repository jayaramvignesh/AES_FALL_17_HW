#include<string.h>
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include<linux/kernel.h>
#include<sys/syscall.h>
#include<unistd.h>

#define BUFFER_LENGTH 256

/*function to create random integers*/
void random_int(int32_t *unsorted,uint32_t length)
{
	srand(0);
	for(int i=0; i<length; i++)
	{
		*(unsorted+i) = (rand()%1000);
	}

}


int main()
{
  
  uint32_t length = BUFFER_LENGTH;

  /*Check if length is equal to zero*/
  if(length == 0)
  { 
    printf("length is zero");
    return 0;
  }

  int32_t* unsorted = malloc(length*sizeof(uint32_t));
  int32_t* sorted = malloc(length*sizeof(uint32_t));
 
  /*Check if pointers are equal to NULL*/
  if(unsorted == NULL || sorted == NULL)
  {
    printf("/nERROR:MALLOC/n");
    return 0;
  }

  int i = 0;
  long int return_value;	
	
  random_int(unsorted,length);

  printf("\nArray before sorting \n");
  for(i=0; i<length; i++)
  {
	printf("%d\n",*(unsorted+i));
  }

  /*Positive testing of system call*/
  return_value = syscall(334,unsorted,sorted,length);
  printf("\nreturn value is %ld\n",return_value);


  printf("\nArray after sorting: \n");
  for(i=0; i<length; i++)
  {
	printf("%d\n",*(sorted+i));
  }


  /*Testing of function when wrong inputs are passed*/
  int32_t *a = NULL;
  uint32_t l = 0; 

  return_value = syscall(334,a,sorted,length);
  printf("\nWhen pointer to store unsorted numbers is NULL, return value is %ld\n",return_value);

  return_value = syscall(334,unsorted,a,length);
  printf("\nWhen pointer to store sorted numbers is NULL, return value is %ld\n",return_value);

  return_value = syscall(334,unsorted,sorted,l);
  printf("\nWhen length is 0, return value is %ld\n",return_value);

  /*Free the allocated memory*/
  free(unsorted);
  free(sorted);
}


