#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>


/*License Declaration*/
MODULE_LICENSE("GPL");

/*Macro for timer expiration in milliseconds*/
#define EXPIRATION_ms 500

/*Defining instance of timer_list structure*/
struct timer_list vigi_timer;

/*callback function for timer*/
void vigi_timer_callback(unsigned long data)
{

   /*Restarting the timer*/
   int return_value; 
   return_value = mod_timer(&vigi_timer,jiffies + msecs_to_jiffies(EXPIRATION_ms));
   if(return_value)
    {
      printk("ERROR: TIMER MOD FUNCTION");
    }

   /*printing to the kernel buffer the number of timer the timer has fired*/
    static int count;
    count += 1;
    printk("%d count: timer fired",count);

}

/*init function for kernel module*/
int timer_init_module(void)
{
	int return_value;
  printk(KERN_INFO "CUSTOM TIMER MODULE INSERTED INTO KERNEL\n");
  

  /*initializing and set-up timer*/
  init_timer(&vigi_timer);
  setup_timer(&vigi_timer,vigi_timer_callback,0);
  
  /*modifying the timer and setting an expiration value*/ 
  printk("\nTimer to fire in 500ms\n");
  return_value = mod_timer(&vigi_timer,jiffies+msecs_to_jiffies(EXPIRATION_ms));
  if(return_value)
  {
    printk("ERROR: TIMER MOD FUNCTION");
  }

  return 0;
}

/*exit function for kernel module*/
void timer_cleanup_module(void)
{
  int return_value;

  /*Deleting the timer*/
  return_value = del_timer(&vigi_timer);
  if(return_value)
  {
    printk("TIMER: Still in use\n");
  }
  
  printk("TIMER: DELETING");

	printk(KERN_INFO "REMOVED CUSTOM TIMER MODULE\n");

  return;
}

module_init(timer_init_module);
module_exit(timer_cleanup_module);
