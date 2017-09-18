#include "circbuff.h"
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

/*Function to test for NULL ptr in buffer full funtion*/
void test_buffer_full_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  states return_value = Buffer_Empty(cbuffer);
  assert_int_equal(return_value, NULL_PTR);
}

/*Function to test for NULL ptr in buffer empty funtion*/
void test_buffer_empty_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  states return_value = Buffer_Full(cbuffer);
  assert_int_equal(return_value, NULL_PTR);
}

/*Function to test for NULL ptr in buffer add funtion*/
void test_buffer_add_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  states return_value = add_item(cbuffer,4);
  assert_int_equal(return_value, NULL_PTR);
}

/*Function to test for NULL ptr in buffer remove funtion*/
void test_buffer_remove_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t item;
  states return_value = remove_item(cbuffer,&item);
  assert_int_equal(return_value, NULL_PTR);
}

/*Function to test for NULL ptr in buffer free funtion*/
void test_buffer_free_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t* circ_buffer = NULL;
  states return_value = Buffer_Free(cbuffer,circ_buffer);
  assert_int_equal(return_value, NULL_PTR);
}

/*Function to test for NULL ptr in buffer dump{length} funtion*/
void test_buffer_dump_length_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  states return_value = Buffer_Dump_length(cbuffer);
  assert_int_equal(return_value, NULL_PTR);
}

/*Function to test for NULL ptr in buffer dump{items} funtion*/
void test_buffer_dump_items_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  states return_value = Buffer_Dump_items(cbuffer);
  assert_int_equal(return_value, NULL_PTR);
}

/*Function to test for NULL ptr in buffer size funtion*/
void test_buffer_size_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  states return_value = Buffer_Size(cbuffer);
  assert_int_equal(return_value, NULL_PTR);
}

/*Function to test for length=0 in buffer init  funtion*/
void test_buffer_init_length_ZERO(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 0;
  states return_value = Buffer_Init(&cbuffer,&circ_buffer,length_buff);
  assert_int_equal(return_value, LENGTH_ZERO);
}

/*positive test for buffer init function*/
void test_buffer_init(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 4;
  states return_value = Buffer_Init(&cbuffer,&circ_buffer,length_buff);
  assert_int_equal(return_value, SUCCESS);
}

/*positive test for buffer free function*/
void test_buffer_free(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 4;
  Buffer_Init(&cbuffer,&circ_buffer,length_buff);
  states return_value = Buffer_Free(cbuffer,circ_buffer);
  assert_int_equal(return_value, SUCCESS);
}

/*test to check if add fails when buffer full*/
void test_buffer_add_fail(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 5;
  Buffer_Init(&cbuffer,&circ_buffer,length_buff);
  add_item(cbuffer,10);
  add_item(cbuffer,20);
  add_item(cbuffer,30);
  add_item(cbuffer,40);
  add_item(cbuffer,50);
  states return_value = add_item(cbuffer,60);
  assert_int_equal(return_value, FAIL);
}

/*positive test for buffer add*/
void test_buffer_add_pass(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 10;
  Buffer_Init(&cbuffer,&circ_buffer,length_buff);
  add_item(cbuffer,10);
  add_item(cbuffer,20);
  add_item(cbuffer,30);
  add_item(cbuffer,40);
  add_item(cbuffer,50);
  states return_value = add_item(cbuffer,60);
  assert_int_equal(return_value, SUCCESS);
}

/*test to check if remove fails when buffer empty*/
void test_buffer_remove_fail(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 5;
  uint32_t item;   
  Buffer_Init(&cbuffer,&circ_buffer,length_buff); 
  add_item(cbuffer,10);
  add_item(cbuffer,20);
  add_item(cbuffer,30);
  add_item(cbuffer,40);
  remove_item(cbuffer,&item);
  remove_item(cbuffer,&item);
  remove_item(cbuffer,&item);
  remove_item(cbuffer,&item);
  states return_value = remove_item(cbuffer,&item);
  assert_int_equal(return_value, FAIL);
}

/*positive test for buffer remove function*/
void test_buffer_remove_pass(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 5;
  uint32_t item;   
  Buffer_Init(&cbuffer,&circ_buffer,length_buff); 
  add_item(cbuffer,10);
  add_item(cbuffer,20);
  add_item(cbuffer,30);
  add_item(cbuffer,40);
  remove_item(cbuffer,&item);
  remove_item(cbuffer,&item);
  states return_value = remove_item(cbuffer,&item);
  assert_int_equal(return_value, SUCCESS);
}

/*function to test if buffer is empty*/
void test_buffer_empty_1(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 4;
  uint32_t item;   
  Buffer_Init(&cbuffer,&circ_buffer,length_buff); 
  add_item(cbuffer,10);
  add_item(cbuffer,20);
  add_item(cbuffer,30);
  add_item(cbuffer,40);
  remove_item(cbuffer,&item);
  remove_item(cbuffer,&item);
  remove_item(cbuffer,&item);
  remove_item(cbuffer,&item);
  states return_value = Buffer_Empty(cbuffer);
  assert_int_equal(return_value, EMPTY);
}

/*to test empty buffer function when item is available*/
void test_buffer_empty_2(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 4;
  uint32_t item;   
  Buffer_Init(&cbuffer,&circ_buffer,length_buff); 
  add_item(cbuffer,10);
  add_item(cbuffer,20);
  add_item(cbuffer,30);
  add_item(cbuffer,40);
  remove_item(cbuffer,&item);
  remove_item(cbuffer,&item);
  states return_value = Buffer_Empty(cbuffer);
  assert_int_equal(return_value, AVAILABLE);
}

/*function to test if buffer is full*/
void test_buffer_full_1(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 5;
  Buffer_Init(&cbuffer,&circ_buffer,length_buff);
  add_item(cbuffer,10);
  add_item(cbuffer,20);
  add_item(cbuffer,30);
  add_item(cbuffer,40);
  add_item(cbuffer,50);
  states return_value = Buffer_Full(cbuffer); 
  assert_int_equal(return_value, FULL);
}

/*test buffer full function when item available*/
void test_buffer_full_2(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 10;
  Buffer_Init(&cbuffer,&circ_buffer,length_buff);
  add_item(cbuffer,10);
  add_item(cbuffer,20);
  add_item(cbuffer,30);
  add_item(cbuffer,40);
  add_item(cbuffer,50);
  states return_value = Buffer_Full(cbuffer); 
  assert_int_equal(return_value, AVAILABLE);
}

/*function to test buffer dump[items]*/
void test_buffer_dump_items(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 10;
  Buffer_Init(&cbuffer,&circ_buffer,length_buff);
  add_item(cbuffer,10);
  add_item(cbuffer,20);
  add_item(cbuffer,30);
  add_item(cbuffer,40);
  add_item(cbuffer,50);
  states return_value = Buffer_Dump_items(cbuffer); 
  assert_int_equal(return_value, SUCCESS);
}

/*function to test buffer dump[length]*/
void test_buffer_dump_length(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 6;
  Buffer_Init(&cbuffer,&circ_buffer,length_buff);
  add_item(cbuffer,10);
  add_item(cbuffer,20);
  add_item(cbuffer,30);
  add_item(cbuffer,40);
  add_item(cbuffer,50);
  states return_value = Buffer_Dump_length(cbuffer); 
  assert_int_equal(return_value, SUCCESS);
}

/*function to test buffer size*/
void test_buffer_size(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 10;
  Buffer_Init(&cbuffer,&circ_buffer,length_buff);
  add_item(cbuffer,10);
  add_item(cbuffer,20);
  add_item(cbuffer,30);
  add_item(cbuffer,40);
  add_item(cbuffer,50);
  states return_value = Buffer_Size(cbuffer); 
  assert_int_equal(return_value, 5);
}



/*main function*/
int main(int argc, char **argv)
{
    const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_buffer_full_NULL),
    cmocka_unit_test(test_buffer_empty_NULL),
    cmocka_unit_test(test_buffer_add_NULL),
    cmocka_unit_test(test_buffer_free_NULL),
    cmocka_unit_test(test_buffer_dump_items_NULL),
    cmocka_unit_test(test_buffer_dump_length_NULL),
    cmocka_unit_test(test_buffer_size_NULL),
    cmocka_unit_test(test_buffer_init_length_ZERO),
    cmocka_unit_test(test_buffer_init),
    cmocka_unit_test(test_buffer_free),
    cmocka_unit_test(test_buffer_add_pass),
    cmocka_unit_test(test_buffer_add_fail),
    cmocka_unit_test(test_buffer_remove_pass),
    cmocka_unit_test(test_buffer_remove_fail), 
    cmocka_unit_test(test_buffer_full_1),
    cmocka_unit_test(test_buffer_full_2),
    cmocka_unit_test(test_buffer_empty_1),
    cmocka_unit_test(test_buffer_empty_2),
    cmocka_unit_test(test_buffer_size),
    cmocka_unit_test(test_buffer_dump_length),
    cmocka_unit_test(test_buffer_dump_items),

};

  return cmocka_run_group_tests(tests, NULL, NULL);
}
