/********************************************
*   Authors: Vignesh Jayaram
*   Date Edited: 9 Sept 2017
*
*   File: double_ll.h
*
*   Description: Header file for double linked list
*        
*    -dll_length
*		 -destroy_list
*		 -print_list
*		 -position_insert
*		 -position_delete
*
********************************************************/


#ifndef DOUBLE_LL_H_INCLUDED
#define DOUBLE_LL_H_INCLUDED

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

/*Double linked list Structure*/
struct node
{
  uint32_t data;
  struct node *next; // Pointer to next node in DLL
  struct node *prev; // Pointer to previous node in DLL
};

/*Enum to describe the function return values*/
typedef enum
{
	SUCCESS = 1,
	FAIL = 2
}states;

/*This function is used to find length of a double linked list*/
uint32_t dll_length(struct node* node);				

/*This function is used to destroy the contents of double linked list*/
states destroy_list(struct node **node);				

/*This function is used to print double linked list[forward and backward]*/
void print_list(struct node *node);					

/*This function adds a new node at given position*/
states position_insert(struct node** head_ref,uint32_t position_to_be_inserted,uint32_t data);

/*This function deletes node at given position*/
states position_delete(struct node **head_ref, uint32_t position_to_be_deleted, uint32_t* data_to_be_deleted);

/*Function to search the position of the data given*/
struct node* search_data(struct node **head_ref, uint32_t data_to_be_searched, uint32_t *data_present);

#endif // DOUBLE_LL_H_INCLUDED
