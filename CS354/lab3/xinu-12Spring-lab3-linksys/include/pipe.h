#define NPIPE 10
#define PIPE_SIZE 256

#define PIPE_FREE 1
#define PIPE_USED 2
#define PIPE_CONNECTED 3

struct pipe {
	uint16	pipestate;       /* state of the pipe */
	sid32   psem;            /* sender semaphore */
	sid32   csem;            /* receiver semaphore */
	int32   pip;       	     /* pipe ID */
	pid32   ownerPID;        /* owner PID */
	pid32   end1;            /* one end of the pipe */
    pid32   end2;            /* other end of the pipe */
	char buffer[PIPE_SIZE];  /* buffer */
	int     pos;             /* current position in buffer */
}; 

extern struct pipe pipelist[];   /* list of free pipes */
extern int32 pipenextid;         /* next pipe ID to try when looking for a new one */

#define isbadpipeid(pipeid) ((pipeid)<0 || (pipeid)>=NPIPE)  
