/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/************************************************************************/
/*									*/
/* main - main program for testing Xinu					*/
/*									*/
/************************************************************************/

int main(int argc, char **argv)
{
	void sendMessage(pid32 recPID);
	void receiveMessage(void);

	kprintf("Welcome to the main function!\n\r");

	pid32 receiver = create(receiveMessage, 1000, 20, "receiver", 0); 
	pid32 sender = create(sendMessage, 1000, 20, "sender", 1, receiver); 

	ready(sender, 1);
	ready(receiver, 1);

	return OK;
}

void sendMessage(pid32 recPID) {
	umsg32 msg = 'a';
	kprintf("sender sent %s\n\r", msg);
	sendb(currpid, msg);
}

void receiveMessage(void) {
	umsg32 msg = receiveb();
	kprintf("msg = %c\n\r", msg);
}
