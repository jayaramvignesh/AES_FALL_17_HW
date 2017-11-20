/******* Referred from DEREK MOLLY LINK*****************/

#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/device.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
#include <linux/string.h>
#include <linux/timer.h>
#include <linux/gpio.h>

#define DEVICE_NAME "vigi_char_device"
#define CLASS_NAME "vigi"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VIGNESH JAYARAM");
MODULE_DESCRIPTION("Simple Character Driver for BBG");
MODULE_VERSION("1");

static uint8_t gpio_led_num = 53;
static bool led_value = false;

static uint16_t led_on_time = 500;
static uint16_t led_off_time = 500;
static uint16_t led_period = 1;

/*packet to receive structure*/
typedef struct led_packet{
  uint8_t led_state;
  uint8_t period;
  uint8_t dutycycle;
}packet;

/*create a global instance of the packet received*/
packet received;

/*Defining instance of timer_list structure*/
struct timer_list vigi_timer;

/*defining a count for the number of times timer expires*/
static int count = 1;

/*flag so that timer gets added only once*/
uint8_t flag = 1;

/*callback function for timer*/
void vigi_timer_callback(unsigned long data)
{
	count = count + 1;
  if(received.led_state == 2)
  {
    led_value = false;
    count = 1;
    flag = 1;
  }
  else if(received.led_state == 1)
  {
    if(count%2 == 0)
	  {
	    /*Modifying the timer*/
	    int return_value; 
      return_value = mod_timer(&vigi_timer,jiffies + msecs_to_jiffies(led_on_time));
      if(return_value)
	    {
		    printk(KERN_ALERT "ERROR: TIMER MOD FUNCTION");
      }

      led_value = true;
	  }
	  else
	  {
      /*Modifying the timer*/
      int return_value; 
      return_value = mod_timer(&vigi_timer,jiffies + msecs_to_jiffies(led_off_time));
      if(return_value)
      {
        printk(KERN_ALERT "ERROR: TIMER MOD FUNCTION");
      }

      led_value = false;
	  }
  }
	
	  gpio_set_value(gpio_led_num,led_value);
  printk("%d count: timer fired",count);

}

/*stoes the device number*/
static int major_number;

/*variable to store size of string*/
static uint32_t size_of_message = 0;

/*variable to count number of times device has been opened*/
static uint32_t no_open = 0;

/*device driver class struct pointer*/
static struct class* vigicharClass = NULL;

/*device dtriver device struct pointer*/
static struct device* vigicharDevice = NULL;

/*function prototype for open*/
static int dev_open(struct inode *inodep, struct file *filep);

/*function prototype for release*/
static int dev_release(struct inode *inodep, struct file *filep);

/*function prototype for read*/
static ssize_t dev_read(struct file *filep,char *buffer,size_t length, loff_t* offset);

/*function prototype for write*/
static ssize_t dev_write(struct file *filep, const char *buffer, size_t length, loff_t* offset);

/*fops structure for linking the prototypes with the callback functions*/
static struct file_operations fops = 
{
  .open = dev_open,
  .read = dev_read,
  .write = dev_write,
  .release = dev_release,
};


/*module init function*/
static int __init vigi_char_init(void)
{
  printk(KERN_INFO "\nVIGI CHAR DRIVER: INIT MODULE FUNCTION\n");

  /*Allocate Major Number*/
  major_number = register_chrdev(0,DEVICE_NAME, &fops);

  /*check for success*/
  if(major_number < 0)
  {
    printk(KERN_ALERT "\nCHAR DRIVER ERROR: FAILED TO REGISTER MAJOR NUMBER\n");
    return major_number;
  }

  printk(KERN_INFO "\nCHAR DRIVER REGISTERED SUCCESSFULLY WITH MAJOR NUMBER %d\n",major_number);

  /*Register the device class*/
  vigicharClass = class_create(THIS_MODULE,CLASS_NAME);

  if(IS_ERR(vigicharClass))
  {
    unregister_chrdev(major_number,DEVICE_NAME);
    printk(KERN_ALERT "\nCHAR DRIVER ERROR: FAILED TO REGISTER DEVICE CLASS\n");
    return PTR_ERR(vigicharClass);
  }

  printk(KERN_INFO "\nDEVICE CLASS REGISTERED SUCCESSFULLLY\n");
  
  /*Register DEvice Driver*/
  vigicharDevice = device_create(vigicharClass, NULL , MKDEV(major_number, 0), NULL, DEVICE_NAME);

  if(IS_ERR(vigicharDevice))
  {
    class_destroy(vigicharClass);
    unregister_chrdev(major_number,DEVICE_NAME);
    printk(KERN_ALERT "\nCHAR DRIVER ERROR: FAILED TO CREATE DEVICE\n");
    return PTR_ERR(vigicharDevice);
  }

  printk(KERN_INFO "\nDEVICE CLASS CREATED SUCCESSFULLY \n");
  
  /*initializing and set-up timer*/
  init_timer(&vigi_timer);
  setup_timer(&vigi_timer,vigi_timer_callback,0);
  
  printk(KERN_INFO "\nTIMER SUCCESSFULLLY CREATED\n");
  
  /*check if gpio is valid*/
  if(!gpio_is_valid(gpio_led_num))
  {
    printk(KERN_ALERT "INVALID GPIO FOR LED\n");
    return -ENODEV;
  }

  /*initially led will be off*/
  led_value = false;
  gpio_request(gpio_led_num,"sysfs");
 
  gpio_direction_output(gpio_led_num,led_value);
 
  gpio_export(gpio_led_num, false);


  printk(KERN_ALERT "LED INITIALIZED SUCCESSFULLLY\n");

  return 0;
}

/*module clean up function*/
static void __exit vigi_char_clean(void)
{

  int return_value;
  
  gpio_set_value(gpio_led_num , 0);

  gpio_unexport(gpio_led_num);
 
  gpio_free(gpio_led_num);

  /*Deleting the timer*/
  return_value = del_timer(&vigi_timer);
  if(return_value)
  {
    printk("TIMER: Still in use\n");
  }
 

  /*remove the device*/
  device_destroy(vigicharClass , MKDEV(major_number,0));

  /*unregister the device*/
  class_unregister(vigicharClass);
    
  /*Remove the device class*/
  class_destroy(vigicharClass);

  /*unregister the major number*/
  unregister_chrdev(major_number,DEVICE_NAME);

  printk(KERN_INFO "\nVIGI CHAR DRIVER: BYE BYE !!!\n");
}

/************************************************ 
 * Device Open Function
 * increment the counter whenever open is called
 * filep = pointer to file object
 * inodep = pointer to inode object
 ************************************************/

static int dev_open(struct inode *inodep, struct file* filep)
{
  no_open++;
  printk(KERN_INFO "\nVIGII CHAR DEVICE has been opened %d times\n",no_open);
  return 0;
}


/************************************************ 
 * Device Read Function
 * filep = pointer to file object
 * length = length of buffer to read
 * buffer = array where contents to read are stored
 * offset = offset if required
 ************************************************/

static ssize_t dev_read(struct file *filep,char *buffer,size_t length, loff_t* offset)
{
  int error_count = 0;

  /*copy to user is used to send data from kernel side to user space*/
  error_count = copy_to_user(buffer,&received,sizeof(received));

  if(error_count == 0)
  {
    printk(KERN_INFO "VIGI CHAR DEVICE: %d characters read\n",size_of_message);
    size_of_message = 0;
    return 0;
  }
  else
  {
    printk(KERN_ALERT "\nERROR: VIGI CHAR DEVICE FAILED TO READ\n");
    return -EFAULT;
  }
}

/************************************************ 
 * Device Write Function
 * filep = pointer to file object
 * length = length of buffer to read
 * buffer = array where contents to write are stored
 * offset = offset if required
 ************************************************/

static ssize_t dev_write(struct file *filep,const char *buffer,size_t length, loff_t* offset)
{
  int error_count = copy_from_user(&received,buffer,length);

  if(error_count == 0)
  {
    printk(KERN_INFO "VIGI CHAR DEVICE: %ld characters written\n",length);
    size_of_message = 0;
  }
  else
  {
    printk(KERN_ALERT "\nERROR: VIGI CHAR DEVICE FAILED TO WRITE\n");
    return -EFAULT;
  }

 
  led_period = received.period * 1000;
  led_on_time = (received.dutycycle * led_period)/100;
  led_off_time = led_period - led_on_time;

  printk(KERN_ALERT "State= %d\n",received.led_state);
  printk(KERN_ALERT "period %d milliseconds\n",led_period);
  printk(KERN_ALERT "in the given period, led will be on for %d milliseconds",led_on_time);

  if(received.led_state == 1 && flag == 1)
  {
    vigi_timer.expires=jiffies+msecs_to_jiffies(led_on_time);
    vigi_timer.data=0;
    vigi_timer.function= vigi_timer_callback;
    add_timer(&vigi_timer);
    flag = 0;
  }

  return length;
}

/************************************************ 
 * Device Release Function
 * filep = pointer to file object
 * inodep = pointer to inode object
 ************************************************/

static int dev_release(struct inode *inodep, struct file *filep)
{
  printk(KERN_INFO "VIGI CHAR DEVICE SUCCESSFULLY CLOSED\n");
  return 0;
}


module_init(vigi_char_init);
module_exit(vigi_char_clean);
