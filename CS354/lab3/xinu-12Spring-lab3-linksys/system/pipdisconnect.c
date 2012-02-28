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

	restore(mask);
	return(OK);
}
