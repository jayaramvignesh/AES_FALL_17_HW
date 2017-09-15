#include "circbuff.h"
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

void test_buffer_full_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  states return_value = Buffer_Empty(cbuffer);
  assert_int_equal(return_value, NULL_PTR);
}

void test_buffer_empty_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  states return_value = Buffer_Full(cbuffer);
  assert_int_equal(return_value, NULL_PTR);
}

void test_buffer_add_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  states return_value = add_item(cbuffer,4);
  assert_int_equal(return_value, NULL_PTR);
}

void test_buffer_remove_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t item;
  states return_value = remove_item(cbuffer,&item);
  assert_int_equal(return_value, NULL_PTR);
}

void test_buffer_free_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t* circ_buffer = NULL;
  states return_value = Buffer_Free(cbuffer,circ_buffer);
  assert_int_equal(return_value, NULL_PTR);
}

void test_buffer_dump_length_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  states return_value = Buffer_Dump_length(cbuffer);
  assert_int_equal(return_value, NULL_PTR);
}

void test_buffer_dump_items_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  states return_value = Buffer_Dump_items(cbuffer);
  assert_int_equal(return_value, NULL_PTR);
}

void test_buffer_size_NULL(void **state)
{
  cirbuff_t *cbuffer = NULL;
  states return_value = Buffer_Size(cbuffer);
  assert_int_equal(return_value, NULL_PTR);
}

void test_buffer_init_length_ZERO(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 0;
  states return_value = Buffer_Init(&cbuffer,&circ_buffer,length_buff);
  assert_int_equal(return_value, LENGTH_ZERO);
}

void test_buffer_init(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 4;
  states return_value = Buffer_Init(&cbuffer,&circ_buffer,length_buff);
  assert_int_equal(return_value, SUCCESS);
}

void test_buffer_free(void **state)
{
  cirbuff_t *cbuffer = NULL;
  uint32_t *circ_buffer = NULL;
  uint32_t length_buff = 4;
  Buffer_Init(&cbuffer,&circ_buffer,length_buff);
  states return_value = Buffer_Free(cbuffer,circ_buffer);
  assert_int_equal(return_value, SUCCESS);
}

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
