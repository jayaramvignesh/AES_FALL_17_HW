/********************************************
*   Authors: Vignesh Jayaram
*   Date Edited: 9 Sept 2017
*
*   File: circbuff.c
*
*   Description: Source file for circular buffer
*      
*    -Buffer_Full
*		 -Buffer_Empty
*		 -add_item
*		 -remove_item
*		 -Buffer_Init
*		 -Buffer_Flus
*		 -Buffer_Free
*		 -Buffer_Dump_length
*		 -Buffer_Dump_items
*  	 -Buffer_Size
*	
********************************************************/

#include "circbuff.h"

/*This functions checks of the buffer is full or not*/
states Buffer_Full(cirbuff_t *buff)
{		
    if(buff->no_of_items == buff->length)			//check if number of items is equal to the length of buffer
    {
        return FULL;
    }
    else
    {
        return AVAILABLE;
    }
}

/*This function check if the buffer is empty*/
states Buffer_Empty(cirbuff_t *buff)
{
    if(buff->no_of_items == 0)						//Check if no of items is equal to zero
    {
        return EMPTY;
    }
    else
    {
        return AVAILABLE;
    }
}

/*This function is used to add an element in the buffer*/
states add_item(cirbuff_t *buff, uint32_t data)
{
    if(Buffer_Full(buff))							//check if buffer is full
    {
        return FAIL;
    }

    *(buff->head) = data;							//Add data to the address where head points
    buff->head++;								//Increment the head pointer
    buff->no_of_items++;							//Increments the number of items after addition to buffer 
    if((buff->head) == buff->buffer + buff->length) 				//This statement prevents buffer overflow by bringing head back
    {
    	buff -> head = buff->buffer;			    			//back to the first element
    }
    return SUCCESS;
}

/*This function remove an item from the buffer*/
states remove_item(cirbuff_t *buff, uint32_t * removed_item)
{
    if(Buffer_Empty(buff))							//check if buffer is empty
    {
        return FAIL;
    }
    *removed_item = *(buff->tail);						//remove item from the buffer
    buff->tail++;								//Increment tail pointer
    buff->no_of_items--;							//Decrements the number after removal

    if((buff->tail) == buff->buffer + buff->length) 				//Brings the tail back to the first element
    {
	buff -> tail = buff->buffer;						//thus preventing buffer overflow
    }
    return SUCCESS;
}

/*This function initializes the circular buffer of a particular length*/
states Buffer_Init(cirbuff_t **buff,uint32_t **circ_buffer, uint32_t length)
{
	cirbuff_t *temp = *buff;
	
	*circ_buffer = (uint32_t *)calloc(length,sizeof(uint32_t));  		//dynamically creates the memory for the buffer for the given length
	temp = (cirbuff_t *)calloc(1,sizeof(cirbuff_t));			//dynamically creates the memory for the buffer structure
	
	if(temp == NULL || *circ_buffer == NULL)
	{
		return FAIL;
	}
	
	temp->buffer = *circ_buffer;					
	temp->head = temp->buffer;						//initialize the head and tail pointer
	temp->tail = temp->buffer;
	temp->length = length;
	temp->no_of_items = 0;							//initialize the number of elements to zero
	
	*buff = temp;
	return SUCCESS;
}

/*This function frees the allocated space for buffer*/
states Buffer_Free(cirbuff_t *buff, uint32_t *cbuffer )
{
	if (buff == NULL || cbuffer == NULL)
		return FAIL;
	
	free(buff);
	free(cbuffer);
	return SUCCESS;
}

/*This function removes all the item from the buffer*/
void Buffer_Flush(cirbuff_t *buff, uint32_t *value)
{
	uint32_t i,len;

	len = buff->no_of_items;

	for(i=0; i<len; i++)
        {
		remove_item(buff, value);
		value++;
	}
}

/*This function prints all the item from the buffer*/
states Buffer_Dump_length(cirbuff_t *buff)
{
    uint32_t len,num_items;
    len = buff->length;
    num_items = buff->no_of_items;

    if(len == 0 || num_items == 0)   
    {
	return FAIL;
    }   

    uint32_t *temp;
    temp = buff->buffer;
    printf("the items in circular buffer are: \n");
    
    while(len != 0)
    {
        printf("data at address %d is %d\n",temp,*temp);
	temp++;
        len--;
    }

    return SUCCESS;
}

/*This function prints all the item from the buffer*/
states Buffer_Dump_items(cirbuff_t *buff)
{
    uint32_t  num_items;
    num_items = buff->no_of_items;
    
    uint32_t len = buff->length;
    if(len == 0 || num_items == 0)
    {
	return FAIL;
    }

    uint32_t *temp;
    temp = buff->tail;

    printf("the items in circular buffer are: \n");
    
    while(num_items != 0)
    {
        printf("data at address %d is %d\n",temp,*temp);
        temp++;
        if(temp == buff->buffer + buff->length) 		//This statement prevents buffer overflow by bringing head back
	{
		    temp = buff->buffer;			//back to the first element
	}
        num_items--;
    }

    return SUCCESS;
}

/*This function returns the size of circular buffer*/
uint32_t Buffer_Size(cirbuff_t *buff)
{
    return buff->no_of_items;
}
