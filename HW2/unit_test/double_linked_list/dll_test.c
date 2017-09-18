#include "double_ll.h"
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

/*function to test NULL pointer in length function*/
void test_dll_length_NULL(void **state)
{
  struct node* head= NULL;
  states return_value = dll_length(head);
  assert_int_equal(return_value, NULL_PTR);
}

/*function to test NULL pointer in print function*/
void test_dll_print_NULL(void **state)
{
  struct node* head= NULL;
  states return_value = print_list(head);
  assert_int_equal(return_value, NULL_PTR);
}

/*function to test NULL pointer in destroy function*/
void test_dll_destroy_NULL(void **state)
{
  struct node* head= NULL;
  states return_value = destroy_list(&head);
  assert_int_equal(return_value, NULL_PTR);
}

/*function to test NULL pointer in remove function*/
void test_dll_remove_NULL(void **state)
{
  struct node* head= NULL;
  uint32_t data;
  states return_value = position_delete(&head,2,&data);
  assert_int_equal(return_value, NULL_PTR);
}

/*function to test insert function for empty list*/
void test_dll_insert_empty_list(void **state)
{
  struct node* head= NULL;
  states return_value = position_insert(&head,2,1000);
  assert_int_equal(return_value, SUCCESS);
}

/*function to test insert function for adding item to middle of list*/
void test_dll_insert_middle(void **state)
{
  struct node* head= NULL;
  position_insert(&head,1,5);
  position_insert(&head,1,10);
  position_insert(&head,2,20);
  position_insert(&head,3,30);
  position_insert(&head,4,40);
  position_insert(&head,5,50);
  states return_value = position_insert(&head,2,1000);
  assert_int_equal(return_value, SUCCESS);
}

/*function to test insert function for adding item at head*/
void test_dll_insert_head(void **state)
{
  struct node* head= NULL;
  position_insert(&head,1,5);
  position_insert(&head,1,10);
  position_insert(&head,2,20);
  position_insert(&head,3,30);
  position_insert(&head,4,40);
  position_insert(&head,5,50);
  states return_value = position_insert(&head,0,1000);
  assert_int_equal(return_value, SUCCESS);
}

/*function to test insert function for adding item at end*/
void test_dll_insert_end(void **state)
{
  struct node* head= NULL;
  position_insert(&head,1,5);
  position_insert(&head,1,10);
  position_insert(&head,2,20);
  position_insert(&head,3,30);
  position_insert(&head,4,40);
  position_insert(&head,5,50);
  states return_value = position_insert(&head,6,1000);
  assert_int_equal(return_value, SUCCESS);
}

/*function to test insert function [fail]*/
void test_dll_insert_fail(void **state)
{
  struct node* head= NULL;
  position_insert(&head,1,5);
  position_insert(&head,1,10);
  position_insert(&head,2,20);
  position_insert(&head,3,30);
  position_insert(&head,4,40);
  position_insert(&head,5,50);
  states return_value = position_insert(&head,7,1000);
  assert_int_equal(return_value, FAIL);
}

/*function to test remove function [fail]*/
void test_dll_remove_fail(void **state)
{
  struct node* head= NULL;
  position_insert(&head,1,5);
  position_insert(&head,1,10);
  position_insert(&head,2,20);
  position_insert(&head,3,30);
  position_insert(&head,4,40);
  position_insert(&head,5,50);
  uint32_t data;
  states return_value = position_delete(&head,7,&data);
  assert_int_equal(return_value, FAIL);
}

/*function to test remove function [data at head]*/
void test_dll_remove_head(void **state)
{
  struct node* head= NULL;
  position_insert(&head,1,5);
  position_insert(&head,1,10);
  position_insert(&head,2,20);
  position_insert(&head,3,30);
  position_insert(&head,4,40);
  position_insert(&head,5,50);
  uint32_t data;
  states return_value = position_delete(&head,0,&data);
  assert_int_equal(return_value, SUCCESS);
}

/*function to test remove function [data at middle]*/
void test_dll_remove_middle(void **state)
{
  struct node* head= NULL;
  position_insert(&head,1,5);
  position_insert(&head,1,10);
  position_insert(&head,2,20);
  position_insert(&head,3,30);
  position_insert(&head,4,40);
  position_insert(&head,5,50);
  uint32_t data;
  states return_value = position_delete(&head,2,&data);
  assert_int_equal(return_value, SUCCESS);
}

/*function to test remove function [data at end]*/
void test_dll_remove_end(void **state)
{
  struct node* head= NULL;
  position_insert(&head,1,5);
  position_insert(&head,1,10);
  position_insert(&head,2,20);
  position_insert(&head,3,30);
  position_insert(&head,4,40);
  position_insert(&head,5,50);
  uint32_t data;
  states return_value = position_delete(&head,5,&data);
  assert_int_equal(return_value, SUCCESS);
}

/*to test destroy function*/
void test_dll_destroy(void **state)
{
  struct node* head= NULL;
  position_insert(&head,1,5);
  position_insert(&head,1,10);
  position_insert(&head,2,20);
  position_insert(&head,3,30);
  position_insert(&head,4,40);
  position_insert(&head,5,50);
  states return_value = destroy_list(&head);
  assert_int_equal(return_value, SUCCESS);
}

/*to test length function*/
void test_dll_length(void **state)
{
  struct node* head= NULL;
  position_insert(&head,1,5);
  position_insert(&head,1,10);
  position_insert(&head,2,20);
  position_insert(&head,3,30);
  position_insert(&head,4,40);
  position_insert(&head,5,50);
  states return_value = dll_length(head);
  assert_int_equal(return_value, 6);
}

/*to test print list function*/
void test_dll_print(void **state)
{
  struct node* head= NULL;
  position_insert(&head,1,5);
  position_insert(&head,1,10);
  position_insert(&head,2,20);
  position_insert(&head,3,30);
  position_insert(&head,4,40);
  position_insert(&head,5,50);
  states return_value = print_list(head);
  assert_int_equal(return_value, SUCCESS);
}

/*main function*/
int main(int argc, char **argv)
{
    const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_dll_length_NULL),
    cmocka_unit_test(test_dll_remove_NULL),
    cmocka_unit_test(test_dll_destroy_NULL),
    cmocka_unit_test(test_dll_print_NULL),
    cmocka_unit_test(test_dll_insert_empty_list),
    cmocka_unit_test(test_dll_insert_head),
    cmocka_unit_test(test_dll_insert_end),
    cmocka_unit_test(test_dll_insert_middle),
    cmocka_unit_test(test_dll_insert_fail),
    cmocka_unit_test(test_dll_remove_head),
    cmocka_unit_test(test_dll_remove_end),
    cmocka_unit_test(test_dll_remove_middle),
    cmocka_unit_test(test_dll_remove_fail),
    cmocka_unit_test(test_dll_length),
    cmocka_unit_test(test_dll_destroy),
    cmocka_unit_test(test_dll_print),    
};

  return cmocka_run_group_tests(tests, NULL, NULL);
}
