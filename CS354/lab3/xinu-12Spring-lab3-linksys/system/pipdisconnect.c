#include <xinu.h>

syscall pipdisconnect(int32 pip) {
	intmask mask;
	struct pipe *pipeptr;

	mask = disable();

	if (isbadpipeid(pip) || (pipeptr = &pipelist[pip])->pipestate != PIPE_CONNECTED || (pipeptr = &pipelist[pip])->ownerPID != getpid()) {
		restore(mask);
		return(SYSERR);
	}

	// not sure if this is all that needs to be done for this method
	pipeptr = &pipelist[pip];
	pipeptr->pipestate = PIPE_USED;
	pipeptr->end1 = NULL;
	pipeptr->end2 = NULL;
	semreset(pipeptr->psem, PIPE_SIZE);
	semreset(pipeptr->csem, 0);
	pipeptr->readPos = 0;
	pipeptr->writePos = 0;

	restore(mask);
	return(OK);
}
