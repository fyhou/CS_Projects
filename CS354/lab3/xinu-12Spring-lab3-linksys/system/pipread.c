#include <xinu.h>

syscall pipread(int32 pip, char *buf, uint32 len) {
 	intmask mask;
	struct pipe *pipeptr;

	mask = disable();

	if (isbadpipeid(pip) || (pipeptr = &pipelist[pip])->pipestate != PIPE_CONNECTED || (pipeptr = &pipelist[pip])->end1 != getpid()) {
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
		charInBuff = readPos;
	}
	if else (orientaiton < 0)
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
        			buf[i] = pipeptr->buffer[i];
				readPos++; 
				pipeptr->readPos = readPos;
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
				//kprintf("PIPREAD (A): char = %c\n\r", pipeptr->buffer[i]);
				buf[i] = pipeptr->buffer[i];
				readPos++; 
				pipeptr->readPos = readPos;
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
				//kprintf("PIPREAD (B): char = %c\n\r", pipeptr->buffer[i]);
        			buf[i] = pipeptr->buffer[i];
				readPos++;
				pipeptr->readPos = readPos;
			signal(pipeptr->psem);
		}

		restore(mask);
		return(len);
	}
}
