#include <xinu.h>

syscall pipread(int32 pip, char *buf, uint32 len) {
 	intmask mask;
	struct pipe *pipeptr;

	mask = disable();

	if (isbadpipeid(pip) || isbadpid(getpid()) || (pipeptr = &pipelist[pip])->pipestate != PIPE_CONNECTED || (pipeptr = &pipelist[pip])->end1 != getpid()) {
		if (isbadpid(getpid()))
		{
			kprintf("PIPREAD: Owner had bad PID!\n\r");
		}
		
		restore(mask);
		return(SYSERR);
	}

	pipeptr = &pipelist[pip];
	int i = 0;  // keep track of length
	int writePos = pipeptr->writePos;
	int readPos = pipeptr->readPos;

	int orientation = writePos - readPos;
	int charInBuff;
	
	if (orientation > 0) 
	{
		charInBuff = writePos - readPos;
	}
	else if (orientation < 0)
	{
		charInBuff = PIPE_SIZE - readPos + writePos;
	}
	else 
	{
		charInBuff = 0;
	}

	if (charInBuff == 0) 
	{

		for (i = 0; i < len; i++)
		{
			wait(pipeptr->csem);
				if (pipeptr->pipestate != PIPE_CONNECTED) {
					kprintf("pipe gone\n\r");
					return SYSERR;
				}
				
        			buf[i] = pipeptr->buffer[readPos];
				readPos++; 
				
				if (pipeptr->readPos == PIPE_SIZE) pipeptr->readPos = 0;
				else pipeptr->readPos = readPos;
			signal(pipeptr->psem);
		}

		restore(mask);
		return(len);
	}
	else if (charInBuff <= len)
	{
		for (i = 0; i < charInBuff; i++)
		{
			wait(pipeptr->csem);
				if (pipeptr->pipestate != PIPE_CONNECTED) {
					kprintf("pipe gone\n\r");
					return SYSERR;
				}
				
				buf[i] = pipeptr->buffer[readPos];
				readPos++; 
				
				if (pipeptr->readPos == PIPE_SIZE) pipeptr->readPos = 0;
				else pipeptr->readPos = readPos;
			signal(pipeptr->psem);
		}
		
		restore(mask);
		return(charInBuff);
	}
	else 
	{
		for (i = 0; i < len; i++)
		{
			wait(pipeptr->csem);
				if (pipeptr->pipestate != PIPE_CONNECTED) {
					kprintf("pipe gone\n\r");
					return SYSERR;
				}
				
        			buf[i] = pipeptr->buffer[readPos];
				readPos++;
				
				if (pipeptr->readPos == PIPE_SIZE) pipeptr->readPos = 0;
				else pipeptr->readPos = readPos;
			signal(pipeptr->psem);
		}

		restore(mask);
		return(len);
	}
}
