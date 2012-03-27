/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/************************************************************************/
/*									                                    */
/* main - main program for testing Xinu			                 		*/
/*									                                    */
/************************************************************************/

int main(int argc, char **argv)
{
	kprintf("Welcome to the main function!");

	void sendMessage(pid32 recPID);
	void receiveMessage(void);

	pid32 receiver = create(receiveMessage, 1000, 20, "receiver", 0); // reader
	pid32 sender = create(sendMessage, 1000, 20, "sender", 1, receiver);  // writer

	ready(sender, 1);
	ready(receiver, 1);

	return OK;
}

void sendMessage(pid32 recPID) {
	sendb(currpid, 'a');
}

void receiveMessage(void) {
	umsg32 msg = receiveb();
	kprintf("msg = %s\n\r", msg);
}
