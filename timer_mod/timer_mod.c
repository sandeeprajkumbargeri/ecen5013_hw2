/*

Filename: timer_mod.c
Author: Sandeep Raj Kumbargeri
Description: Implements a kernel module which logs certain data for every 500ms by default which is User
            configurable.
Written for ECEN 5013 Homework 2 in Spring 2018 at University of Colorado Boulder

*/

//Headers
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/timer.h>

//Kernel module specifics
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sandeep Raj Kumbargeri");
MODULE_DESCRIPTION("This is a kernel module that fires a time interrupt for every 500ms");
MODULE_VERSION("1.0");

//Initializing static data
static char *name = "Sandeep Raj";
static unsigned long time_ms = 500;

//Initializing external parameters for the module
module_param(name, charp, S_IRUSR | S_IWUSR);
module_param(time_ms, ulong, S_IRUSR | S_IWUSR);

static struct timer_list timer;

//Declaration of Kernel Init and Exit functions
static int __init init_timer_module(void);
static void __exit exit_timer_module(void);
void timer_callback_handler(unsigned long);

//Function definitions
static int __init init_timer_module(void)
{
  printk(KERN_INFO "TIMER_MODULE :: Starting..");
  init_timer(&timer);
  setup_timer(&timer, timer_callback_handler, 0);
  mod_timer(&timer, jiffies + msecs_to_jiffies(time_ms));

  return 0;
}

//Kernel timer interrupt handler
void timer_callback_handler(unsigned long data)
{
  static unsigned long handler_count = 0;
  handler_count++;

  printk(KERN_INFO "TIMER_MODULE :: User: %s | Timeout: %lums | Handler Count: %lu.", name, time_ms, handler_count);
  mod_timer(&timer, jiffies + msecs_to_jiffies(time_ms));
}


static void __exit exit_timer_module(void)
{
  del_timer(&timer);
  printk(KERN_INFO "TIMER_MODULE :: Exited.");
}

//Letting the kernel module know baout the init and the exit functions
module_init(init_timer_module);
module_exit(exit_timer_module);
