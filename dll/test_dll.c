/*

File Name: test_dll.c
Author: Sandeep Raj Kumbargeri
Description: Linux Doubly Linked Lists Functions .h file
Written for ECEN 5013 - Homework 2 - in Spring 2018 at University of Colorado Boulder

*/

//Headers
#include <math.h>
#include <stdlib.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "dll.h"

//Function to test the functionality of the function "insert_at_beginning".
//Creates one node and reads the value stored in it and verifies it.
void test_insert_at_beginning(void **state)
{
  node_t *head_node = NULL;
  item_t *entry = NULL;
  unsigned char data = 20;

  head_node = insert_at_beginning(head_node, data);
  entry = GET_LIST_CONTAINER(head_node, item_t, link);
  assert_int_equal(data, entry->data);
}

//Function to test the functionality of the function "insert_at_end".
//Creates a node after the first node and reads the first node to verify the value stored
void test_insert_at_end(void **state)
{
  node_t *head_node = NULL;
  item_t *entry = NULL;
  unsigned char data = 30;

  head_node = insert_at_end(head_node, data);
  entry = GET_LIST_CONTAINER(head_node, item_t, link);
  assert_int_equal(data, entry->data);
}

//Function to test the functionality of the function "insert_at_position".
//Creats a node after the first node and reads its data to verify
void test_insert_at_position(void **state)
{
  node_t *head_node = NULL;
  node_t *base_node = NULL;
  item_t *entry = NULL;
  unsigned char data = 30;

  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_position(head_node, data, 1);
  head_node = head_node->next;
  entry = GET_LIST_CONTAINER(head_node, item_t, link);

  assert_int_equal(data, entry->data);
}

//Function to test the functionality of the function "delete_from__beginning".
//Creates several nodes and deletes the first node and reads the data at the first node which reads
//the value of the node initially created at posittion 2 to verify
void test_delete_from_beginning(void **state)
{
  node_t *head_node = NULL;
  node_t *base_node = NULL;
  item_t *entry = NULL;
  unsigned char data = 0x30;

  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = delete_from_beginning(head_node);
  entry = GET_LIST_CONTAINER(head_node, item_t, link);

  assert_int_equal(0x32, entry->data);
}

//Function to test the functionality of the function "delete_from_end".
//Creates several nodes and verifirs the size of it after deleting the node from the end.
void test_delete_from_end(void **state)
{
  node_t *head_node = NULL;
  node_t *base_node = NULL;
  item_t *entry = NULL;
  unsigned char data = 0x30;

  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = delete_from_end(head_node);

  assert_int_equal(3, size(head_node));
}

//Function to test the functionality of the function "delete_from_position".
//Creates several nodes, deletes the second node and reads the data at node 2, which reads the
//data fromm initially created node 3 to verify
void test_delete_from_position(void **state)
{
  node_t *head_node = NULL;
  node_t *base_node = NULL;
  item_t *entry = NULL;
  unsigned char data = 0x30;

  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = delete_from_position(head_node, 1);
  head_node = head_node->next;
  entry = GET_LIST_CONTAINER(head_node, item_t, link);

  assert_int_equal(0x31, entry->data);
}

//Function to test the functionality of the function "size".
//Creates several nodes and deletes a node somewhere in the middle. Then checks for the size to verify
void test_size(void **state)
{
  node_t *head_node = NULL;
  node_t *base_node = NULL;
  item_t *entry = NULL;
  unsigned char data = 0x30;
  size_t nodes;

  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = delete_from_position(head_node, 1);
  nodes = size(head_node);

  assert_int_equal(3, nodes);
}


//Function to test the functionality of the function "destroy".
//Creates several nodes and then destroys them all and then checks for the size, the size returns 0.
void test_destroy(void **state)
{
  node_t *head_node = NULL;
  node_t *base_node = NULL;
  item_t *entry = NULL;
  unsigned char data = 0x30;
  size_t nodes;

  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = insert_at_beginning(head_node, data);
  data++;
  head_node = delete_from_position(head_node, 1);
  head_node = destroy(head_node);

  nodes = size(head_node);

  assert_int_equal(0, nodes);
}

//mMain function in which all the unit_tests are executed.
int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_insert_at_beginning),
    cmocka_unit_test(test_insert_at_end),
    cmocka_unit_test(test_insert_at_position),
    cmocka_unit_test(test_delete_from_beginning),
    cmocka_unit_test(test_delete_from_end),
    cmocka_unit_test(test_delete_from_position),
    cmocka_unit_test(test_size),
    cmocka_unit_test(test_destroy),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
