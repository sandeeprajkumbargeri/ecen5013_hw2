#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define ARRAY_SIZE 16
#define MAX_RAND  128
#define MIN_RAND  0


int main(void)
{
  int32_t data_item[ARRAY_SIZE], swap_temp = 0;
  unsigned int i = 0, j = 0, min_index = 0;

  srand(0);
  printf("\n\nBefore:\n");

  for(i = 0; i < ARRAY_SIZE; i++)
  {
    data_item[i] = (rand() % (MAX_RAND + 1 - MIN_RAND)) + MIN_RAND;
    printf("%d\t", data_item[i]);
  }

  for (i = 0; i < ARRAY_SIZE - 1; i++)
  {
    min_index = i;

    for (j = i+1; j < ARRAY_SIZE; j++)
    {
      if (data_item[j] > data_item[min_index])
        min_index = j;
    }

    swap_temp = data_item[min_index];
    data_item[min_index] = data_item[i];
    data_item[i] = swap_temp;
  }

  printf("\n\nAfter:\n");
  for(i = 0; i < ARRAY_SIZE; i++)
    printf("%d\t", data_item[i]);

  printf("\n");
}
