#include<linux/sched.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/sched/signal.h>
#include<linux/list.h>

MODULE_LICENSE("GPL");

int module_start(void)
{
  /*create a pointer instance for task struct*/
  struct task_struct *task_current;

  /*create a pointer instance of list_head*/
  struct list_head* current_ptr;

  int no_children;
  
  printk(KERN_INFO "\nMODULE:INIT FUNCTION\n");

  /* traverse backwards till init task is reached*/
  for_each_process(task_current)
  {
  
    /*reset the number of childern value to zero*/
    no_children = 0;
    
    /*calculate number of children*/
    list_for_each(current_ptr, &(task_current->children))
    {
      no_children++;
    }

    /*print all values*/
    printk(KERN_INFO "PROCESS NAME: %s PID = %d STATE = %ld NUMBER OF CHILDREN = %d\n",task_current->comm,task_current->pid,task_current->state,no_children);
  }

  return 0;

}

void module_cleanup(void)
{
  printk(KERN_INFO "MODULE: REMOVE");
}

module_init(module_start);
module_exit(module_cleanup);


MODULE_LICENSE("GPL");




