#include <xinu.h>

syscall pipread(int32 pip, char *buf, uint32 len) {
  intmask mask;
	struct pipe *pipeptr;
	kprintf("err1\n\r");
	mask = disable();

	if (isbadpipeid(pip) || (pipeptr = &pipelist[pip])->pipestate != PIPE_CONNECTED || (pipeptr = &pipelist[pip])->end1 != getpid()) {
		restore(mask);
		return(SYSERR);
	}
	kprintf("err2\n\r");
	pipeptr = &pipelist[pip];
	int i = 0;  // keep track of length
	int pos = pipeptr->pos;
	kprintf("err3\n\r");
	int charInBuff = pos;
	if (charInBuff == 0) 
	{
		kprintf("err4\n\r");
		for (i = 0; i < len; i++)
		{
			wait(pipeptr->csem);
        			buf[i] = pipeptr->buffer[i];
				pos--; 
				pipeptr->pos = pos;
			signal(pipeptr->psem);
		}

		restore(mask);
		return(len);
	}
	else if (charInBuff <= len)
	{
		kprintf("err5\n\r");
		for (i = 0; i < charInBuff; i++)
		{
			//kprintf("PIPREAD (A): char = %c\n\r", pipeptr->buffer[i]);
			buf[i] = pipeptr->buffer[i];
			pos--; 
			pipeptr->pos = pos;
		}
		kprintf("err6\n\r");
		semtab[pipeptr->csem].scount = 0;
		semtab[pipeptr->psem].scount = PIPE_SIZE;
		kprintf("err7\n\r");
		restore(mask);
		return(charInBuff);
	}
	else 
	{
		kprintf("err8\n\r");
		for (i = 0; i < len; i++)
		{
			wait(pipeptr->csem);
				kprintf("PIPREAD (B): char = %c\n\r", pipeptr->buffer[i]);
        			buf[i] = pipeptr->buffer[i];
				pos--;
				pipeptr->pos = pos;
			signal(pipeptr->psem);
		}

		restore(mask);
		return(len);
	}
}
