/*

File Name: dll.c
Author: Sandeep Raj Kumbargeri
Description: Linux Doubly Linked Lists Functions .c file
Written for ECEN 5013 - Homework 2 - in Spring 2018 at University of Colorado Boulder

*/


#include "dll.h"

node_t* insert_at_beginning(node_t *head_node, unsigned char data)
{
  item_t *entry = (item_t *) malloc(sizeof(item_t));

  //If theere are no nodes in the linked list
  if((head_node->prev == NULL) && (head_node->next == NULL))
  {
    printf("Linked list doesn't exist. Creating head node.\n");

    head_node = &(entry->link);
    entry->data = data;

    head_node->next = head_node;
    head_node->prev = head_node;

    return (head_node);
  }

  //If there is only one element in the linked list
  else if((head_node->prev == head_node) && (head_node->next == head_node))
  {
    head_node->prev = &(entry->link);
    head_node->next = NULL;

    entry->link.next = head_node;
    entry->link.prev = NULL;
    entry->data = data;

    return (head_node->prev);
  }

  //Adding the new node infront of the head node
  else if((head_node->prev == NULL) && (head_node->next != NULL))
  {
    head_node->prev = &(entry->link);
    entry->link.next = head_node;
    entry->link.prev = NULL;
    entry->data = data;

    return (head_node->prev);
  }

  //If the head node received is not the head node, then return NULL.
  else
  {
    printf("Error: Parameter 1 is not pointing to a head node.\n");
    free(entry);
    return NULL;
  }
}

node_t* insert_at_end(node_t *head_node, unsigned char data)
{
  item_t *entry = (item_t *) malloc(sizeof(item_t));

  //If theere are no nodes in the linked list
  if((head_node->prev == NULL) && (head_node->next == NULL))
  {
    printf("Linked list doesn't exist. Creating head node.\n");

    head_node = &(entry->link);
    entry->data = data;

    head_node->next = head_node;
    head_node->prev = head_node;

    return (head_node);
  }

  //If there is only one element in the linked list
  else if((head_node->prev == head_node) && (head_node->next == head_node))
  {
    head_node->next = &(entry->link);
    head_node->prev = NULL;

    entry->link.prev = head_node;
    entry->link.next = NULL;
    entry->data = data;

    return (head_node->prev);
  }

  //If the head node received is a valid head node
  else if((head_node->prev == NULL) && (head_node->next != NULL))
  {
    do {
      head_node = head_node->next;
    } while(head_node->next != NULL);

    head_node->next = &(entry->link);
    entry->link.prev = head_node;
    entry->link.next = NULL;
    entry->data = data;

    do {
      head_node = head_node->prev;
    } while(head_node->prev != NULL);

    return (head_node);
  }

  //If the head node received is not a head node at all
  else
  {
    printf("Error: Parameter 1 is not pointing to a head node.\n");
    free(entry);
    return NULL;
  }
}


node_t* insert_at_position(node_t *base_node, unsigned char data, int offset)
{
  item_t *entry = (item_t *) malloc(sizeof(item_t));
  node_t *prev_base_node;

  //If the offset is positive then traverse right through the links
  if(offset > 0)
  {
    do {
      base_node = base_node->next;
      offset--;
    } while((offset != 0) || base_node->next != NULL);

    if(offset == 0)
    {
      prev_base_node = base_node->prev;
      base_node->prev = &(entry->link);
      prev_base_node->next = &(entry->link);

      entry->link.prev = prev_base_node;
      entry->link.next = base_node;
      entry->data = data;

      do {
        base_node = base_node->prev;
      } while(base_node->prev != NULL);

      return base_node;
    }

    else if(base_node->next == NULL)
    {
      printf("Error: Offset out of bounds.\n");
      return NULL;
    }
  }

  //if the offset position is negative, then traverse left through the list
  else if(offset < 0)
  {
    offset = -offset;

    do {
      base_node = base_node->prev;
      offset--;
    } while((offset != 0) || base_node->prev != NULL);

    if(offset == 0)
    {
      prev_base_node = base_node->prev;
      base_node->prev = &(entry->link);
      prev_base_node->next = &(entry->link);

      entry->link.prev = prev_base_node;
      entry->link.next = base_node;
      entry->data = data;

      do {
        base_node = base_node->prev;
      } while(base_node->prev != NULL);

      return base_node;
    }

    else if(base_node->prev == NULL)
    {
      printf("Error: Offset out of bounds.\n");
      return NULL;
    }
  }
}

node_t* delete_from_beginning(node_t *head_node)
{
  item_t *entry = NULL;
  node_t *next_node = NULL;

  //If theere are no nodes in the linked list
  if((head_node->prev == NULL) && (head_node->next == NULL))
  {
    printf("Linked list doesn't exist. Cannot delete.\n");
    return NULL;
  }

  //If there is only one element in the linked list
  else if((head_node->prev == head_node) && (head_node->next == head_node))
  {
    entry = GET_LIST_CONTAINER(head_node, item_t, link);
    free(entry);
    return NULL;
  }

  //If the received head node is a valid head node, delete it.
  else if((head_node->prev == NULL) && (head_node->next != NULL))
  {
    head_node->prev = NULL;
    next_node = head_node->next;
    head_node->next = NULL;
    next_node->prev = NULL;

    entry = GET_LIST_CONTAINER(head_node, item_t, link);
    free(entry);

    return (next_node);
  }

  //If not, then return a null pointer
  else
  {
    printf("Error: Parameter 1 is not pointing to a head node.\n");
    return NULL;
  }
}

node_t* delete_from_end(node_t *head_node)
{
  item_t *entry = NULL;
  node_t *prev_node = NULL;

  //If theere are no nodes in the linked list
  if((head_node->prev == NULL) && (head_node->next == NULL))
  {
    printf("Linked list doesn't exist. Cannot delete.\n");
    return NULL;
  }

  //If there is only one element in the linked list
  else if((head_node->prev == head_node) && (head_node->next == head_node))
  {
    entry = GET_LIST_CONTAINER(head_node, item_t, link);
    free(entry);
    return NULL;
  }


  //If the head node received is a valiod head node
  else if((head_node->prev == NULL) && (head_node->next != NULL))
  {
    do {
      head_node = head_node->next;
    } while(head_node->next != NULL);

    head_node->next = NULL;
    prev_node = head_node->prev;
    head_node->prev = NULL;
    prev_node->next = NULL;

    entry = GET_LIST_CONTAINER(head_node, item_t, link);
    free(entry);

    do {
      prev_node = prev_node->prev;
    } while(prev_node->prev != NULL);

    return (prev_node);
  }

  //If not, return null
  else
  {
    printf("Error: Parameter 1 is not pointing to a head node.\n");
    return NULL;
  }
}

node_t* delete_from_position(node_t *base_node, int offset)
{
  item_t *entry;
  node_t *prev_base_node;
  node_t *next_base_node;


  //If offset is potive traverse right
  if(offset > 0)
  {
    do {
      base_node = base_node->next;
      offset--;
    } while((offset != 0) || base_node->next != NULL);

    if(offset == 0)
    {
      prev_base_node = base_node->prev;
      next_base_node = base_node->next;

      prev_base_node->next = next_base_node;
      next_base_node->prev = prev_base_node;

      base_node->prev = NULL;
      base_node->next = NULL;

      entry = GET_LIST_CONTAINER(base_node, item_t, link);
      free(entry);

      base_node = prev_base_node;

      do {
        base_node = base_node->prev;
      } while(base_node->prev != NULL);

      return base_node;
    }

    else if(base_node->next == NULL)
    {
      printf("Error: Offset out of bounds.\n");
      return NULL;
    }
  }

  //If the offset is negative, then traverse left.
  else if(offset < 0)
  {
    offset = -offset;

    do {
      base_node = base_node->prev;
      offset--;
    } while((offset != 0) || base_node->prev != NULL);

    if(offset == 0)
    {
      prev_base_node = base_node->prev;
      next_base_node = base_node->next;

      prev_base_node->next = next_base_node;
      next_base_node->prev = prev_base_node;

      base_node->prev = NULL;
      base_node->next = NULL;

      entry = GET_LIST_CONTAINER(base_node, item_t, link);
      free(entry);

      base_node = prev_base_node;

      do {
        base_node = base_node->prev;
      } while(base_node->prev != NULL);

      return base_node;
    }

    else if(base_node->prev == NULL)
    {
      printf("Error: Offset out of bounds.\n");
      return NULL;
    }
  }
}

size_t size(node_t *base_node)
{
  size_t length = 0;

  //If theere are no nodes in the linked list
  if((base_node->prev == NULL) && (base_node->next == NULL))
    return 0;

    //If there is only one node in the linked list
  else if((base_node->prev == base_node) && (base_node->next == base_node))
    return 1;

  //If there are n nodes in the linked list, then go to the front and...
  do {
    base_node = base_node->prev;
  } while(base_node->prev != NULL);

  //count the number of nodes in the linked list
  do {
    base_node = base_node->next;
    length++;
  } while(base_node->next != NULL);

  return length;
}

node_t* destroy(node_t *base_node)
{
  item_t *entry = NULL;
  node_t *next_node = NULL;
  unsigned char last_node = 255;

  //If theere are no nodes in the linked list
  if((base_node->prev == NULL) && (base_node->next == NULL))
  {
    printf("Error: Linked list is empty.\n");
    return NULL;
  }

  //If there is only one element in the linked list
  else if((base_node->prev == base_node) && (base_node->next == base_node))
  {
    base_node->next = NULL;
    base_node->prev = NULL;

    entry = GET_LIST_CONTAINER(base_node, item_t, link);
    free(entry);

    return NULL;
  }

  do {
    base_node = base_node->prev;
  } while(base_node->prev != NULL);

  do{
    next_node = base_node->next;
    base_node->next = NULL;
    base_node->prev = NULL;

    entry = GET_LIST_CONTAINER(base_node, item_t, link);
    free(entry);

    base_node = next_node;

    if(last_node == 1)
      last_node = 0;

    if(base_node->next == NULL)
      last_node = 1;

  }while(last_node != 0);

  return NULL;
}

void main(void)
{

}
