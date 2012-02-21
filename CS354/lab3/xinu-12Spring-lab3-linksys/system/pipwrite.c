#include <xinu.h>

syscall pipwrite(int32 pip, char *buf, uint32 len) {
	intmask mask;
	struct pipe *pipeptr;

	mask = disable();

	// add || (pipeptr = &pipelist[pip])->end2 != getpid() to condition when done
	if (isbadpipeid(pip) || (pipeptr = &pipelist[pip])->pipestate != PIPE_CONNECTED || (pipeptr = &pipelist[pip])->ownerPID != getpid()) {
		restore(mask);
		return(SYSERR);
	}

	pipeptr = &pipelist[pip];
	int i = 0;  // keep track of length
	int pos = pipeptr->pos;

	int available = PIPE_SIZE - pos + 1;
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

		kprintf("PIPWRITE: buffer = %s\n\r", pipeptr->buffer);
		kprintf("PIPWRITE: pos    = %d\n\r", pipeptr->pos);

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

		semtab[pipeptr->psem].count = 0;

		kprintf("PIPWRITE: buffer = %s\n\r", pipeptr->buffer);
		kprintf("PIPWRITE: pos    = %d\n\r", pipeptr->pos);

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

		kprintf("PIPWRITE: buffer = %s\n\r", pipeptr->buffer);
		kprintf("PIPWRITE: pos    = %d\n\r", pipeptr->pos);

		restore(mask);
		return(len);
	}
}
