#include <linux/kernel.h> 
#include <linux/unistd.h>
#include <linux/sched.h>

void sys_my_get_proc_name_by_id(int pid, char *user_buf) { 		
	struct task_struct *t;
	t = find_task_by_vpid(pid);
    
	// inform user if PID is invalid
	if (t == NULL) {
		printk(KERN_ALERT "Invalid PID!\n");
		return;
	}

	char buf[17]; //size of exec name in Linux is 16. We add extra byte for NULL termination.
	get_task_comm(buf, t);
	buf[16] = '\0';

	copy_to_user(user_buf, buf, 17);
    
	return; 
}
