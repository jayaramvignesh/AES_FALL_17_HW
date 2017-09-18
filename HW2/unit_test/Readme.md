HOMEWORK 2 - UNIT TESTS FOR CIRCULAR BUFFER AND DOUBLE LINKED LIST

"cmocka" framework is used for unit tests.

-> UNIT TEST FOR CIRCULAR BUFFER

Total 21 unit tests were performed for the different functions of circular buffer.

Different functions in circular buffer are:

-> buffer_init
-> buffer_free
-> buffer_size
-> buffer_dump_items
-> buffer_dump_length
-> buffer_full
-> buffer_empty
-> buffer_add
-> buffer_remove

1. All the functions were tested for positive testing
2. All the functions except buffer init were tested for passing NULL pointers
3. Buffer init function was tested when length is equal to zero
4. Buffer add function was tested for wrap around and as well as when buffer is full if it returns a    FAIL
5. Buffer remove function was tested for wrap around and as well as when buffer is empty if it return   a FAIL

-> UNIT TEST FOR DOUBLE LINKED LIST

Total 16 unit tests were performed for the different functions of double linked list

Different Functions for double linked list are:

-> add
-> remove
-> print_list
-> destroy_list
-> size_of_list

1. All the functions were tested for positive testing
2. All the functions except add were tested for passing NULL pointers
3. add function was tested for
   -> adding node to an empty list
   -> adding node at the head
   -> adding node in the middle
   -> adding node at the end
   -> to return FAIL, when trying to add node at a position greater than list
4. remove function was tested for
   -> to return FAIL, when removing from an empty list
   -> removing  node at the head
   -> removing node at the end
   -> removing node in the middle
   -> to return a FAIL, when removing a node which is not there in the list

