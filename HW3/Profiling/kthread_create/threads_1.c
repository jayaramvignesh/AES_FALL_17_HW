/********************************************
*   Authors: vignesh jayaram
*   date edited: 5th Oct 2017
*
*   file: threads_1.c
*
*   description: source file for kthread_Create
*      
*      - kernel_thread_function
*      - kernel_thread_init
*      - kernel_thread_cleanup
*   
*	
********************************************************/


#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/kthread.h>
#include <linux/time.h>
#include <linux/sched.h>
#include <linux/timex.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VIGNESH JAYARAM");

cycles_t time;
static struct task_struct *thread1;

/*functon for kthread*/
int kernel_thread_function(void *data )
{
  cycles_t end;
  cycles_t diff;

  printk(KERN_INFO "\nTHREAD 1 FUNCTION\n");
  
  /*get the end time*/
  end = get_cycles();
  printk(KERN_INFO "\nEnd time is  %llu\n",end);
  
  /*calculate time taken for kthread create + function execution*/
  diff = end - time;
  printk(KERN_INFO "\nTime taken is %llu\n",diff);
  return 0;
}

/*module init function*/
int kernel_thread_init(void)
{

  printk(KERN_INFO "\nINIT FUNCTION\n");

  /*get the starting time*/
  time = get_cycles();
  printk(KERN_INFO "\ntime %llu\n",time);

  /*create kthread_create*/
  thread1 = kthread_create(kernel_thread_function,"HI","thread1");
  if((thread1))
  {
    printk(KERN_INFO "\nINSIDE IF\n");
    wake_up_process(thread1);
  }
  else
  {
    printk(KERN_INFO "ERRROR");
    return ;
  }

  return 0;
}

/*clean up function*/
void kernel_thread_cleanup(void)
{
  printk(KERN_INFO "\nCLEAN UP\n");
}

module_init(kernel_thread_init);
module_exit(kernel_thread_cleanup);

MODULE_LICENSE("GPL");
