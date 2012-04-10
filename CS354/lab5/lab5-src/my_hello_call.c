#include <linux/kernel.h> 
#include <linux/unistd.h>

void sys_my_hello_call() { 
        printk(KERN_ALERT "Hello world !!!\n");	//KERN_ALERT is loglevel, making sure that this msg appears on console
        return; 
}
