/********************************************
*   Authors: Vignesh Jayaram
*   Date Edited: 9 Sept 2017
*
*   File: circbuff.h
*
*   Description: header file for circbuff.h
*           
*    -Buffer_Full
*		 -Buffer_Empty
*		 -add_item
*		 -remove_item
*		 -Buffer_Init
*		 -Buffer_Flush
*		 -Buffer_Free
*		 -Buffer_Dump_length
*		 -Buffer_Dump_items
*  	 -Buffer_Size
*	
********************************************************/

#ifndef CIRCBUFF_H_INCLUDED
#define CIRCBUFF_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define LENGTH 9

/*This structure contains the variables for the buffer*/
typedef struct {
	uint32_t* buffer;		//pointer to the circular buffer
	uint32_t* head;			//pointer to the head of the buffer
	uint32_t* tail;			//pointer to the tail of the buffer
	uint32_t length;		//Total length of the buffer
	uint32_t no_of_items;		//number of items present in the buffer
}cirbuff_t;


/*Enumeration for the state of the buffer*/
typedef enum {
    AVAILABLE = 0,
	FULL = 1,
	EMPTY = 2,
	SUCCESS = 3,
	FAIL = 4
}states;


/*This functions checks of the buffer is full or not*/
states Buffer_Full(cirbuff_t *buff);

/*This function check if the buffer is empty*/
states Buffer_Empty(cirbuff_t *buff);

/*This function is used to add an element in the buffer*/
states add_item(cirbuff_t *buff, uint32_t data);

/*This function remove an item from the buffer*/
states remove_item(cirbuff_t *buff, uint32_t *removed_item);

/*This function initializes the circular buffer of a particular length*/
states Buffer_Init(cirbuff_t **buff,uint32_t **circ_buffer, uint32_t length);

/*This function removes all the item from the buffer*/
void Buffer_Flush(cirbuff_t *buff, uint32_t *value);

/*This function frees the allocated space for buffer*/
states Buffer_Free(cirbuff_t *buff, uint32_t *cbuffer );

/*This function prints the entire buffer*/
states Buffer_Dump_length(cirbuff_t *buff);

/*This function prints all the item from the buffer*/
states Buffer_Dump_items(cirbuff_t *buff);

/*This function returns the size of circular buffer*/
uint32_t Buffer_Size(cirbuff_t *buff);


#endif // CIRCBUFF_H_INCLUDED
