Joseph Martella
CS 354 Lab 4
April 1, 2012

To keep record of blocked senders on receivers, I added one additional field to proccess.h
apart from sndmsg and sndflag that were outlined in the lab spec. The additional field I 
added was 'qid16 senderqueue' which holds the queue identifier for that process which 
points to a queue that holds the sender processes that are waiting on it. Each senderqueue
(one for each process) is initialized in initialize.c when we initialize the proctab entries.

Additionally, I wrote a loop that dequeues all left over sender processes that are waiting
on the receiver and wakes them up if the receiver is killed so the system doesn't hang in 
kill.c. Also, when a blocked sender is killed, it remains in the senderqueue of a receiver
with its message still in tact so the receiver can still receive the message. This was done
because the lab spec says "that messages should not be lost".

