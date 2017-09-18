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

  /*Validate Length*/
  if(length == 0)
  {
    printf("length is zero\n");
    return 0;
  }
  
  /*Allocating memory required to store the integers[for both before and after sorting]*/
  int32_t* unsorted = malloc(length*sizeof(uint32_t));
	int32_t* sorted = malloc(length*sizeof(uint32_t));
  
  /*Check for NULL after malloc*/
  if(unsorted == NULL || sorted == NULL)
  {
    printf("/nERROR:MALLOC/n");
    return 0;
  }

	int i = 0;
	long int return_value;	
	
  /*Call function to fill the buffer with random int values*/ 
	random_int(unsorted,length);

	printf("\nArray before sorting \n");
	for(i=0; i<length; i++)
	{
		printf("%d\n",*(unsorted+i));
	}


  /*Sytem call*/
	return_value = syscall(334,unsorted,sorted,length);
	printf("\nreturn value is %ld\n",return_value);



	printf("\nArray after sorting: \n");
	for(i=0; i<length; i++)
	{
		printf("%d\n",*(sorted+i));
	}

  /*Free the allocated memory*/
  free(unsorted);
  free(sorted);


}


