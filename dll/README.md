# Unit Tests Functional Description

The cmocka unit tests were executed by using "sudo make test" command from the command line. 8 unit tests have been written to test the double linked list. Their functional description are as follows.

# void test_insert_at_beginning(void **state)
Creates one node and reads the value stored in it using the GET_LIST_CONTAINER macro and verifies it.

# void test_insert_at_end(void **state)
Creates a node after the first node after it and reads the item value in the first node to verify the value saved before.

# void test_insert_at_position(void **state)
Creates three nodes adding each node in the beginning, then inserts a node in the second position using the head node as the base node and using the offset +1.

# void test_delete_from_beginning(void **state)
Creates three nodes inserting from the beginning and then deletes the first node and reads the value in the first node which happens to be the value of the previous second node.

# void test_delete_from_end(void **state)
Creates four nodes adding each node from the beginning and deletes a node in the end, which reduces the size of the linked list by one. This is read using the size command to verify it.

# void test_delete_from_position(void **state)
Creates four nodes adding each node from the beginning and deletes the second node from the head node. Then the value at the second node is read which happens to be the value at the previous third node.

# void test_size(void **state)
Creates four nodes adding each node from the beginning and deletes a node. Then size of the list is found and verified.

# void test_destroy(void **state)
Creates four nodes and deletes one node and then destroys them all. Then the size of it is verified.
