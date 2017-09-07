/********************************************
*   Authors:  Vignesh Jayaram
*   Date Edited: 9 Sept 2017
*
*   File: double_ll.c
*
*   Description: Source file for double linked list
*        
*    -dll_length
*		 -destroy_list
*		 -print_list
*		 -position_insert
*		 -position_delete
*
********************************************************/

#include "double_ll.h"

/*This function is used to find length of a double linked list*/
uint32_t dll_length(struct node* node)
{
  uint32_t count=0;
  if(node == NULL)
  {
    return 0;
  }
  else if (node != NULL)
  {
    while(node!=NULL)				//increment count till last node
    {
      count++;
      node = node->next;
    }
    return count;
  }
  else
  {
    return 0;
  }
}


/*This function is used to destroy the contents of double linked list*/
states destroy_list(struct node **head_ref)
{
  struct node* node = *head_ref;
    if(node == NULL)
      return FAIL;
	
	struct node *last;
    printf("\n Destroying the list\n");

    while (node != NULL)
    {
        last = node;
        node = node->next;
        free(last);									//Free the node from dynamic memory
        *head_ref = NULL;
    }

}


/*This function is used to print double linked list[forward and backward]*/
void print_list(struct node *node)
{
    struct node *last;

    printf("\nTraversal in forward direction \n");
    while (node != NULL)
    {
        printf(" %d ", node->data);
        last = node;
        node = node->next;
    }

    printf("\nTraversal in reverse direction \n");
    while (last != NULL)
    {
        printf(" %d ", last->data);
        last = last->prev;
    }
    printf("\n");
}

/*This function adds a new node at given position*/
states position_insert(struct node** head_ref,uint32_t position_to_be_inserted,uint32_t data)
{
  struct node *temp_node=*head_ref;
  struct node* node_prev=NULL;

  struct node *new_node=(struct node*)malloc(sizeof(struct node));
  if(new_node == NULL)
  {	
	return FAIL;
  }
  new_node->data=data;																		//Assign the data to the new node

  int length_dll= dll_length(temp_node);													//find the length of linked list
  int count=0;


  if(temp_node == NULL)
  {
        *head_ref = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
        return SUCCESS;
  }
 
  if(position_to_be_inserted > length_dll)
  {
	  return FAIL;
  }
  else if(position_to_be_inserted==0)	//If position is 0, then new node is head 
  {					//Modify next of new node as current head and previous as NULL
     new_node->next = *head_ref;															
     new_node->prev = NULL;
     temp_node->prev = new_node;
     *head_ref = new_node;
     return SUCCESS;
  }
  else if(position_to_be_inserted< length_dll)
  {

    while(count!=(position_to_be_inserted))//traverse till the position the new node has to be added
    {						//modify the next and previous
      node_prev=temp_node;
      temp_node=temp_node->next;
      count++;
    }
    new_node->next=temp_node;
    new_node->prev=temp_node->prev;
    temp_node->prev=new_node;
    node_prev->next=new_node;
    return SUCCESS;
  }

  if(position_to_be_inserted == length_dll)							//Check if new node has to be added at last
 {    									//if yes then modify next of new node to NULL and previous to the current last node
      while(temp_node->next != NULL)
     {

         temp_node = temp_node->next;
     }
     new_node->data = data;
     new_node->prev = temp_node;
     new_node->next = NULL;
     temp_node->next = new_node;
     return SUCCESS;
  }
}

/*This function deletes node at given position*/
states position_delete(struct node **head_ref, uint32_t position_to_be_deleted, uint32_t* data_to_be_deleted)
{
   
    struct node *temp_node=*head_ref;			
 
     int length_dll= dll_length(temp_node);													//Length of double linked list
     int count = 0;	

	
     if(*head_ref == NULL || position_to_be_deleted > length_dll)	//Return FAIL if linked list empty
     {
	   return FAIL;
     }
    											

    if(position_to_be_deleted == 0)												//check if node to be deleted is head
    {
	      *head_ref = temp_node->next;					//if yes,then new head is the next node of current head
        temp_node->next->prev = NULL;			//and previous node of the new head will be NULL
        *data_to_be_deleted = temp_node->data;
        free(temp_node);									//free the allocated memory for the node
        return SUCCESS;
    }

    if(position_to_be_deleted < (length_dll-1))								
    {
      while(count!=(position_to_be_deleted))	//traverse till the position of the node to be deleted
      {
        temp_node=temp_node->next;
        count++;
      }

      temp_node->prev->next = temp_node->next;							//modify next and previous accordingly
      temp_node->next->prev = temp_node->prev;
      *data_to_be_deleted = temp_node->data;
      free(temp_node);																		//free the allocated memory for the node
      return SUCCESS;
    }

    if(position_to_be_deleted == (length_dll-1))											//check if the position of the node to be deleted is last
    {
      while(temp_node->next != NULL)			
      {
          temp_node = temp_node->next;
      }

	  temp_node->prev->next = NULL;														//if yes then modify the next of second last node to NULL
	  free(temp_node);																		//Free the allocated memory
	  return SUCCESS;
    }
}

/*Function to search the position of the data given*/
struct node* search_data(struct node **head_ref, uint32_t data_to_be_searched, uint32_t *data_present)	
{
    int count = 0;

    struct node *temp_node=*head_ref;
    int length_dll= dll_length(temp_node);													//Find the length of linked list
    while(temp_node->data != data_to_be_searched)											//Traverse the list till the data is found
    {
        temp_node = temp_node->next;
        count++;
    }

    *data_present = count;
    return temp_node;																		//Return node at which the data is present
}
