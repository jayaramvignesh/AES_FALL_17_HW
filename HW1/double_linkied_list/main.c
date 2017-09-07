/********************************************
*   Authors: Vignesh Jayaram
*   Date Edited: 9 Sept 2017
*
*   File: main.c
*
*   Description: main source file 
*              
*
********************************************************/

#include "double_ll.h"

int main()
{

    struct node* head = NULL;
    printf("\nInserting value 1000 at head ref\n");
    position_insert(&head,2,1000);
    print_list(head);

  printf("\nInserting value 10 at position 1\n");
  position_insert(&head,1,10);
  print_list(head);

  printf("\nInserting value 100 at position 0\n");
  position_insert(&head,0,100);
  print_list(head);

  printf("\nInserting value 500 at position 2\n");
  position_insert(&head,2,500);
  print_list(head);

  int length = dll_length(head);
  printf("\nlength of double linked list is %d\n",length);

  printf("\nInserting value 200 at position 1\n");
  position_insert(&head,1,200);
  print_list(head);

  uint32_t position_data = 0;
  struct node* position_data_present;

  position_data_present = search_data(&head,200,&position_data);
  printf("\nposition at which %d is present is %d and address of position is %d\n", position_data_present->data,position_data,(uint32_t*)position_data_present);

  length = dll_length(head);
  printf("\nlength of double linked list is %d\n",length);


  uint32_t data_to_be_deleted;
  printf("\nDeleting node at position 0\n");
  position_delete(&head,0,&data_to_be_deleted);
  printf("\ndata deleted from position 2 is %d\n",data_to_be_deleted);
  print_list(head);

  printf("\nDeleting node at position 2\n");
  position_delete(&head,2,&data_to_be_deleted);
  printf("\ndata deleted from position 2 is %d\n",data_to_be_deleted);
  print_list(head);

  length = dll_length(head);
  printf("\nlength of double linked list is %d\n",length);

  printf("\nDeleting node at position 3\n");
  position_delete(&head,3,&data_to_be_deleted);
  printf("\ndata deleted from position 2 is %d\n",data_to_be_deleted);
  print_list(head);

  destroy_list(&head);
  print_list(head);
  length = dll_length(head);
  printf("\nlength after destroy is %d\n",length);
 
}


