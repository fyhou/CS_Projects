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
	/*umsg32 retval;

	resume(create(shell, 4096, 1, "shell", 1, CONSOLE));

	retval = recvclr();
	while (TRUE) {
		retval = receive();
		kprintf("\n\n\rMain process recreating shell\n\n\r");
		resume(create(shell, 4096, 1, "shell", 1, CONSOLE));
	}*/

	void sendMessage(pid32 recPID, char msg);
	void receiveMessage(void);

	pid32 receiver = create(receiveMessage, 1000, 20, "receiver", 0); 
	pid32 sender = create(sendMessage, 1000, 20, "sender", 2, receiver, 'X'); 
	pid32 sender2 = create(sendMessage, 1000, 20, "sender2", 2, receiver, 'Y'); 
	
	resume(sender);
	resume(sender2);
	resume(receiver);

	return OK;
}

void sendMessage(pid32 recPID, char msg) {
	sendb(recPID, msg);
}

void receiveMessage(void) {
	char msg = receiveb();
	kprintf("Receiver received = %c.\n\r", msg);

	char msg2 = receiveb();
	kprintf("Receiver received = %c.\n\r", msg2);
}
