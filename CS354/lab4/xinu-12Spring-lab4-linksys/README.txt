Joseph Martella
CS 354 Lab 4
April 1, 2012

Sorry for the lengthy README. I worked on this lab and don't think I missed anything.
I completed 100% of the lab and did the additional 20% that was implemented the mid-ground
between blocking and asynchronous message passing system. This was a GREAT lab.

/***********************************
 *								   *
 *       Basic lab infomation      *   
 *								   *
 ***********************************/

To keep record of blocked senders on receivers, I added one additional field to proccess.h
apart from sndmsg and sndflag that were outlined in the lab spec. The additional field I 
added was 'qid16 senderqueue' which holds the queue identifier for that process which 
points to a queue that holds the sender processes that are waiting on it. Each senderqueue
(one for each process) is initialized in initialize.c when we initialize the proctab entries.

Additionally, I wrote a loop that dequeues all left over sender processes that are waiting
on the receiver and wakes them up if the receiver is killed so the system doesn't hang in 
kill.c. Also, when a blocked sender is killed, it remains in the senderqueue of a receiver,
but its sndflag field is set to FALSE, so the receiver knows to ignore it and get another 
blocked sender from the queue. If no other blocked senders exist, it behaves like receive().


/***********************************
 *								   *
 *     Extra credit infomation     *   
 *								   *
 ***********************************/

The way I implemented the message queue for each recipient was adding a umsg32 array to 
process.h called msgqueue that holds a maximum of MSGQ_SIZE messages (default is 3). I also
created a C file called messagequeue.c that holds 2 utility methods I made to enqueue and 
dequeue messages from these message queues. Using all of these things, I implemeted sendq()
to enqueue its messag in the recipient message queue if the the recipient has fewer than 
MSGQ_SIZE messages, otherwise it gets put into the senderqueue like in sendb(). In receiveq(),
each time it receives a message, it checks to see if the senderqueue has any blocked senders
an if so, enqueues their message and wakes it up.
