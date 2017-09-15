#include "double_ll.h"
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

void test_dll_length_NULL(void **state)
{
  struct node* head= NULL;
  states return_value = dll_length(head);
  assert_int_equal(return_value, NULL_PTR);
}

void test_dll_print_NULL(void **state)
{
  struct node* head= NULL;
  states return_value = print_list(head);
  assert_int_equal(return_value, NULL_PTR);
}

void test_dll_destroy_NULL(void **state)
{
  struct node* head= NULL;
  states return_value = destroy_list(&head);
  assert_int_equal(return_value, NULL_PTR);
}

void test_dll_remove_NULL(void **state)
{
  struct node* head= NULL;
  uint32_t data;
  states return_value = position_delete(&head,2,&data);
  assert_int_equal(return_value, NULL_PTR);
}

void test_dll_insert_empty_list(void **state)
{
  struct node* head= NULL;
  states return_value = position_insert(&head,2,1000);
  assert_int_equal(return_value, SUCCESS);
}

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
