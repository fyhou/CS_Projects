#include <xinu.h>

syscall pipread(int32 pip, char *buf, uint32 len) {
  intmask mask;
	struct pipe *pipeptr;

	mask = disable();

	// add || (pipeptr = &pipelist[pip])->end1 != getpid() to condition when done
	if (isbadpipeid(pip) || (pipeptr = &pipelist[pip])->pipestate != PIPE_CONNECTED || (pipeptr = &pipelist[pip])->ownerPID != getpid()) {
		restore(mask);
		return(SYSERR);
	}

	pipeptr = &pipelist[pip];
	int i = 0;  // keep track of length
	int pos = pipeptr->pos;

	int charInBuff = pos;
	int last = 0;
	if (charInBuff == 0) 
	{
		for (i = 0; i < len; i++)
		{
			wait(pipeptr->csem);
        			buf[i] = pipeptr->buffer[i];
				pos--; 
				pipeptr->pos = pos;
				last = i;
			signal(pipeptr->psem);
		}

		buf[last] = '\0';
		restore(mask);
		return(len);
	}
	else if (charInBuff <= len)
	{
		for (i = 0; i < charInBuff; i++)
		{

			pipeptr->buffer[i] = buf[i];
			pos--; 
			pipeptr->pos = pos;
			last = i;
		}

		buf[last] = '\0';

		semtab[pipeptr->csem].scount = 0;
		semtab[pipeptr->psem].scount = PIPE_SIZE;

		restore(mask);
		return(charInBuff);
	}
	else 
	{
		for (i = 0; i < len; i++)
		{
			wait(pipeptr->csem);
        			buf[i] = pipeptr->buffer[i];
				pos--;
				pipeptr->pos = pos;
				last = i;
			signal(pipeptr->psem);
		}
		
		buf[last] = '\0';

		restore(mask);
		return(len);
	}
}
