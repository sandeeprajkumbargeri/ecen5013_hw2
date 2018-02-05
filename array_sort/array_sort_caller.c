/*

Filename: array_sort_caller.c
Author: Sandeep Raj Kumbargeri
Description: Implements syscall for sorting an array.
Written for ECEN 5013 Homework 2 in Spring 2018 at University of Colorado Boulder

*/

//Headers
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

//MACROS
#define ARRAY_SIZE 16
#define MAX_RAND  128
#define MIN_RAND  0


int main(void)
{
  int32_t data_item[ARRAY_SIZE], swap_temp = 0;
  unsigned int i = 0, j = 0, min_index = 0;

  srand(0);//Seeding the random generator
  printf("\n\nBefore:\n");

  for(i = 0; i < ARRAY_SIZE; i++)
  {
    data_item[i] = (rand() % (MAX_RAND + 1 - MIN_RAND)) + MIN_RAND; //generating random numbers
    printf("%d\t", data_item[i]);
  }

  syscall(333, data_item, ARRAY_SIZE * sizeof(int32_t), data_item); //implementing a syscall for array sort

  printf("\n\nAfter:\n"); //printing sorted array.
  for(i = 0; i < ARRAY_SIZE; i++)
    printf("%d\t", data_item[i]);

    printf("\n\n");
}
