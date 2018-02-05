/*

Filename: sys_array_sort.c
Author: Sandeep Raj Kumbargeri
Description: Implements selection sort algorithm in the kernel space using a syscall
Written for ECEN 5013 Homework 2 in Spring 2018 at University of Colorado Boulder

*/

//Headers
#include <linux/kernel.h>
#include <linux/syscall.h>


// Main system call function
SYSCALL_DEFINE3(array_sort, int32_t __user *, src_buffer, size_t __user, buffer_size, int32_t __user *, dst_buffer)
{
  unsigned int elements = 0, i = 0, j = 0, min_index;
  int32_t swap_temp = 0;
  int32_t *data_item = NULL;

  if(buffer_size != 0)
    printk(KERN_INFO "SYS_CALL : ARRAY_SORT_DESCENDING :: Entered. Buffer size: %lu bytes.\n", buffer_size);
  else
    {
      printk(KERN_ERROR "SYS_CALL : ARRAY_SORT_DESCENDING :: ERROR. Buffer size: %lu bytes. EXITING.\n", buffer_size);
      return -EFAULT;
    }

  data_item = (int32_t *) kmalloc(buffer_size, GFP_KERNEL); //dynamically allocating memory for storing sorting data
  if(data_item == NULL)
  {
    printk(KERN_ERROR "SYS_CALL : ARRAY_SORT_DESCENDING :: Error creating buffer.\n");
    kfree(data_item);
    return -EFAULT;
  }

  if(copy_from_user(data_item, src_buffer, buffer_size)) //copying data from user space to kernel space
  {
    printk(KERN_ERROR "SYS_CALL : ARRAY_SORT_DESCENDING :: Error copying user buffer data to kernel buffer.\n");
    kfree(data_item);
    return -EFAULT;
  }

  elements = buffer_size / sizeof(int32_t); //calculating the number of elements

  printk(KERN_INFO "SYS_CALL : ARRAY_SORT_DESCENDING :: Starting sort.\n");

  // Performing selection sort
  for (i = 0; i < elements - 1; i++)
  {
    min_index = i;

    for (j = i+1; j < elements; j++)
    {
      if (data_item[j] > data_item[min_index])
        min_index = j;
    }

    swap_temp = data_item[min_index];
    data_item[min_index] = data_item[i];
    data_item[i] = swap_temp;
  }

  printk(KERN_INFO "SYS_CALL : ARRAY_SORT_DESCENDING :: Sort complete.\n");

  if(copy_to_user(dst_buffer, data_item, buffer_size))  //Copying back sorted array to user space from kernel space
  {
    printk(KERN_ERROR "SYS_CALL : ARRAY_SORT_DESCENDING :: Error copying kernel buffer data to user buffer.\n");
    kfree(data_item);
    return -EFAULT;
  }

  kfree(data_item); //freeing the dynamically allocated memory in the kernel spcace
  return 0;
}
