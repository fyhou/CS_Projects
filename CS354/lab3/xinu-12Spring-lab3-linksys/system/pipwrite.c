#include <xinu.h>

syscall pipwrite(int32 pip, char *buf, uint32 len) {
	intmask mask;
	struct pipe *pipeptr;

	mask = disable();

	if (isbadpipeid(pip) || (pipeptr = &pipelist[pip])->pipestate != PIPE_CONNECTED || (pipeptr = &pipelist[pip])->end2 != getpid()) {
		
		if (isbadpipeid(pip)) 
		{
			kprintf("err1\r\n");
		}
		if ((pipeptr = &pipelist[pip])->pipestate != PIPE_CONNECTED)
		{
			kprintf("err2\r\n");
		}
		if ((pipeptr = &pipelist[pip])->ownerPID != getpid()) {
			kprintf("err3\r\n");
		}
		if ((pipeptr = &pipelist[pip])->end2 != getpid()) {
			kprintf("err4\r\n");
		}
		
		restore(mask);
		return(SYSERR);
	}

	pipeptr = &pipelist[pip];
	int i = 0;  // keep track of length
	int pos = pipeptr->pos;

	int available = PIPE_SIZE - pos;
	if (available <= 0) 
	{
		for (i = 0; i < len; i++)
		{
			wait(pipeptr->psem);
				pipeptr->buffer[pos] = buf[i];
				pos++; 
				pipeptr->pos = pos;
			signal(pipeptr->csem);
		}

		restore(mask);
		return(len);
	}
	else if (available <= len)
	{
		for (i = 0; i < available; i++)
		{

			pipeptr->buffer[pos] = buf[i];
			pos++; 
			pipeptr->pos = pos;
		}

		semtab[pipeptr->psem].scount = 0;
		semtab[pipeptr->csem].scount = PIPE_SIZE;

		restore(mask);
		return(available);
	}
	else 
	{
		for (i = 0; i < len; i++)
		{
			wait(pipeptr->psem);
				pipeptr->buffer[pos] = buf[i];
				pos++; 
				pipeptr->pos = pos;
			signal(pipeptr->csem);
		}

		restore(mask);
		return(len);
	}
}
