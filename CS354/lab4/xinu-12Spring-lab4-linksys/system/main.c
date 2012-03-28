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
	void receiveMessage(int number);

	pid32 receiver = create(receiveMessage, 1000, 20, "receiver", 1, 1); 
	pid32 sender   = create(sendMessage, 1000, 20, "sender", 2, receiver, 'X'); 

	resume(sender);
	resume(receiver);

	return OK;
}

void sendMessage(pid32 recPID, char msg) {
	sendb(recPID, msg);
}

void receiveMessage(int number) {
	char msg = ' ';
	int  i = 0;

	for (i = 0; i < number; i++) {
		msg = receiveb();
		kprintf("Message received from sender: \"%c\".\n\r", msg);	
	}
}
