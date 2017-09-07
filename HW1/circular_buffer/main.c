#include "circbuff.h"

int main()
{
    cirbuff_t *cbuffer = NULL;
    uint32_t *circ_buffer = NULL;
    uint32_t length_buff = LENGTH;

    Buffer_Init(&cbuffer,&circ_buffer, length_buff);
    Buffer_Dump_length(cbuffer);


    add_item(cbuffer, 10);
    add_item(cbuffer, 20);
    add_item(cbuffer, 30);
    add_item(cbuffer, 40);
    add_item(cbuffer, 50);
    add_item(cbuffer, 60);


    int no_items;
    no_items = Buffer_Size(cbuffer);
    printf("\nNo of items in buffer is %d\n",no_items);
    Buffer_Dump_length(cbuffer);

    uint32_t item;
    remove_item(cbuffer,&item);
    printf("item removed is %d\n",item);
    remove_item(cbuffer,&item);
    printf("item removed is %d\n",item);
    remove_item(cbuffer,&item);
    printf("item removed is %d\n",item);
    
    no_items = Buffer_Size(cbuffer);
    printf("\nNo of items in buffer is %d\n",no_items);
    Buffer_Dump_items(cbuffer);


    add_item(cbuffer, 11);
    add_item(cbuffer, 12);
    add_item(cbuffer, 13);
    add_item(cbuffer, 14);
    add_item(cbuffer, 15);
    add_item(cbuffer, 16);

    no_items = Buffer_Size(cbuffer);
    printf("\nNo of items in buffer is %d\n",no_items);
    Buffer_Dump_length(cbuffer);


    remove_item(cbuffer,&item);
    printf("item removed is %d\n",item);
    remove_item(cbuffer,&item);
    printf("item removed is %d\n",item);
    remove_item(cbuffer,&item);
    printf("item removed is %d\n",item);
    remove_item(cbuffer,&item);
    printf("item removed is %d\n",item);
    remove_item(cbuffer,&item);
    printf("item removed is %d\n",item);
    remove_item(cbuffer,&item);
    printf("item removed is %d\n",item);
    remove_item(cbuffer,&item);
    printf("item removed is %d\n",item);
    


    no_items = Buffer_Size(cbuffer);
    printf("\nNo of items in buffer is %d\n",no_items);
    Buffer_Dump_items(cbuffer);

    no_items = Buffer_Size(cbuffer);
    printf("\nNo of items in buffer is %d\n",no_items);
    Buffer_Dump_length(cbuffer);

    Buffer_Free(cbuffer,circ_buffer);
}

