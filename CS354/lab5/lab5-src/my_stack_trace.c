#include <linux/kernel.h> 
#include <linux/unistd.h>
#include <linux/sched.h>

void sys_my_stack_trace(int pid, char *user_buf) { 		
	dump_stack();
	return; 
}
