/*

File Name: dll.h
Author: Sandeep Raj Kumbargeri
Description: Linux Doubly Linked Lists Functions .h file
Written for ECEN 5013 - Homework 2 - in Spring 2018 at University of Colorado Boulder

*/


#ifndef _DLL_H
#define _DLL_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#define GET_LIST_CONTAINER(addr, type, member) ({\
	const typeof( ( (type * )0)->member) *__ptr = (addr);\
	(type *) (( (char *) __ptr ) - offsetof(type, member)); }\
)

typedef struct node{
  struct node *next;
  struct node *prev;
} node_t;

typedef struct item{
  unsigned char data;
  struct node link;
} item_t;

node_t* destroy(node_t *);
node_t* insert_at_beginning(node_t *, unsigned char);
node_t* insert_at_end(node_t *, unsigned char);
node_t* insert_at_position(node_t *, unsigned char, int);
node_t* delete_from_beginning(node_t *);
node_t* delete_from_end(node_t *);
node_t* delete_from_position(node_t *, int);
size_t size(node_t *);


#endif
