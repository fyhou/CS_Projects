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

	pid32 receiver  = create(receiveMessage, 1000, 20, "receiver", 1, 3); 
	pid32 sender1   = create(sendMessage, 1000, 20, "sender 1", 2, receiver, 'J'); 
	pid32 sender2   = create(sendMessage, 1000, 20, "sender 2", 2, receiver, 'O'); 
	pid32 sender3   = create(sendMessage, 1000, 20, "sender 3", 2, receiver, 'E'); 
	
	pid32 sender4   = create(sendMessage, 1000, 20, "sender 4", 2, receiver, 'M'); 
	pid32 sender5   = create(sendMessage, 1000, 20, "sender 5", 2, receiver, 'E'); 
	pid32 sender6   = create(sendMessage, 1000, 20, "sender 6", 2, receiver, 'G'); 

	resume(sender1);
	resume(sender2);
	resume(sender3);
	resume(sender4);
	resume(sender5);
	resume(sender6);

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
		kprintf("Message received from sender %d: \"%c\".\n\r", i+1, msg);	
	}
}
