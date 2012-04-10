
/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

char input[600] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\0";
int rw;

void pdelete(pipid32 pipe, pid32 pid){
  if(pipdelete(pipe) != SYSERR)
    kprintf("ERROR TEST CASE 6\n\r");    
}

void test1(void){
  
  pipid32 pipe[10];
  int i = 0;
  char ch;
  int rval;
  
   kprintf("TEST 1 BEGIN\n\r");
  
  for(i = 0; i < 11; i++){
    pipe[i] = pipcreate();
    if(pipe[i] == SYSERR)
      if(i < 10)
	kprintf("ERROR TEST CASE 1\n\r");
  }  
  
  if(pipconnect(pipe[1],-100,100)!=SYSERR)
    kprintf("ERROR TEST CASE 2\n\r");
  
  if(pipdisconnect(pipe[1])!=SYSERR)
    kprintf("ERROR TEST CASE 3\n\r");
  
  if(pipread(pipe[1],&ch,1)!=SYSERR)
    kprintf("ERROR TEST CASE 4\n\r");
  
  if(pipwrite(pipe[1],&ch,1)!=SYSERR)
    kprintf("ERROR TEST CASE 5\n\r");
  
  resume(create(pdelete,1024,20,"del",2,pipe[1],getpid()));
  
  sleep(2);
  
  for(i = 0; i < 11; i++){
    rval = pipdelete(pipe[i]);
    if(rval == SYSERR)
      if(i < 10)
	kprintf("ERROR TEST CASE 7\n\r");      
  }
  
  for(i = 0; i < 10; i++){
    pipe[i] = pipcreate();
    if(pipe[i] == SYSERR){
      kprintf("ERROR TEST CASE 8\n\r");
      break;
    }
  }
  
  for(i = 0; i < 10; i++)
    pipdelete(pipe[i]);
  
  
  kprintf("TEST 1 COMPLETE\n\r");
  
}


void read1(void){
}

void write1(void){
}

void readey(pipid32 pipe){  
  if(pipread(pipe,NULL,1)!=SYSERR)
    kprintf("ERROR TEST CASE 20\n\r");
}

void writey(pipid32 pipe){  
  if(pipwrite(pipe,NULL,1)!=SYSERR)
    kprintf("ERROR TEST CASE 19\n\r");
}

void pdisconnect(pipid32 pipe, pid32 pid){
  if(pipdisconnect(pipe) != SYSERR)
    kprintf("ERROR TEST CASE 14\n\r");
}


void test2(void){
  pipid32 pipe;
  pid32 r,w,r1,w1;  
  char ch;
  
  kprintf("TEST 2 BEGIN\n\r");
  
  r = create(read1,1024,20,"read",0);
  w = create(write1,1024,20,"write",0);
  
  kprintf("Hehe 1\n\r");
  
  r1 = create(read1,1024,20,"read",0);
  w1 = create(write1,1024,20,"write",0);
  
  kprintf("Hehe 2\n\r");
  
  if((pipe = pipcreate()) == SYSERR)
    kprintf("Test2 pipcreate failure\n\r");
  
  kprintf("Hehe 3\n\r");
  
  if(pipdelete(pipe) == SYSERR)
    kprintf("Test2 pipdelete failure\n\r");
  
  kprintf("Hehe 4\n\r");
  
  if(pipconnect(pipe,r,w)!=SYSERR)
    kprintf("ERROR TEST CASE 12\n\r");
  
  kprintf("Hehe 5\n\r");
  
  if(pipwrite(pipe,&ch,1)!=SYSERR)
    kprintf("ERROR TEST CASE 21\n\r");
  
  kprintf("Hehe 6\n\r");
  
  if(pipread(pipe,&ch,1)!=SYSERR)
    kprintf("ERROR TEST CASE 22\n\r");
  
  kprintf("Hehe 7\n\r");
  
  if(pipdisconnect(pipe)!=SYSERR)
    kprintf("ERROR TEST CASE 13\n\r");  
  kprintf("Hehe 8\n\r");
  
  if((pipe = pipcreate()) == SYSERR)
    kprintf("Test2 pipcreate failure\n\r");  
  
  kprintf("Hehe 9\n\r");
  
  if(pipconnect(100,r,w)!=SYSERR)
    kprintf("ERROR TEST CASE 11\n\r");
  
  kprintf("Hehe 10\n\r");
  
  resume(r);
  resume(w);
  
  kprintf("Hehe 11\n\r");
  
  r = create(readey,1024,20,"ready",1,pipe);
  w = create(writey,1024,20,"writey",1,pipe);
  
  if(pipconnect(pipe,r,w)==SYSERR)
    kprintf("ERROR TEST CASE 9\n\r");
  
  kprintf("Hehe 12\n\r");
  
  //resume(r);
  //resume(w);
  
  kprintf("Hehe 13\n\r");
  
  if(pipconnect(pipe,r1,w1)!=SYSERR)
    kprintf("ERROR TEST CASE 10\n\r");
  
  kprintf("Hehe 14\n\r");
  
  if(pipwrite(pipe,&ch,1)!=SYSERR)
    kprintf("ERROR TEST CASE 17\n\r");
  
  kprintf("Hehe 15\n\r");
  
  if(pipread(pipe,&ch,1)!=SYSERR)
    kprintf("ERROR TEST CASE 18\n\r");
    
  kprintf("Hehe 16\n\r");
  // disconnect
  
  resume(create(pdisconnect,1024,20,"del",2,pipe,getpid()));  
  
  sleep(1);
  
  if(pipdisconnect(pipe)==SYSERR)
    kprintf("ERROR TEST CASE 15\n\r");
  
  kprintf("Hehe 17\n\r");
  
  if(pipdisconnect(pipe)!=SYSERR)
    kprintf("ERROR TEST CASE 16\n\r"); 
  
  kprintf("Hehe 18\n\r");
  
  if(pipdelete(pipe)==SYSERR)
    kprintf("ERROR TEST CASE 19\n\r"); 
  
  resume(r1);
  resume(w1);
  
  kprintf("Hehe 19\n\r");
  
  kprintf("TEST 2 COMPLETE\n\r");
  
  
  
}

void aread(pipid32 pipe,int num,int incr){
  int cnt = 0;  
  int rval;
  char buf[600];
  
  for(;cnt < num;){
    if(cnt+incr > num)
      incr = num - cnt;
    rval = pipread(pipe,buf,incr);
    if(rval < 0){
      kprintf("ERROR WHILE READING in AREAD\n\r");
      return;
    }
    else{
      buf[rval] = '\0';
      kprintf("Read is %s\n\r",buf);
    }
    cnt+=rval;
  }
}

void awrite(pipid32 pipe,int num,int incr){
  int cnt = 0;
  int rval;
  
  for(;cnt < num;){
    if(cnt+incr > num)
      incr = num - cnt;
    rval = pipwrite(pipe,&(input[cnt]),incr);
    if(rval < 0){
      kprintf("ERROR WHILE WRITING in AWRITE\n\r");
      return;
    }else
      kprintf("AWRITE - wrote %d bytes\n\r",rval);
    cnt+=rval;
  }
}

void test3(void){
  
  pid32 r, w;
  pipid32 pipe;
  
  kprintf("TEST 3 BEGIN\n\r");
  
  if((pipe = pipcreate()) == SYSERR)
    kprintf("Test3 pipcreate failure\n\r");  
  
  r = create(aread,2048,20,"aread",3,pipe,50,5);
  w = create(awrite,2048,20,"awrite",3,pipe,50,5);
  if(rw ==1){  
    if(pipconnect(pipe,r,w)==SYSERR)
      kprintf("Test3 pipconnect failure\n\r");
  }
  else if(rw == 0){
    if(pipconnect(pipe,w,r)==SYSERR)
      kprintf("Test3 pipconnect failure\n\r");
  }
  
  resume(r);
  resume(w);
  
  sleep(3);
  
  kprintf("You should see 5 times 1 to 0. If nothing -12, if something -8\n\r");
  
  if(pipdisconnect(pipe)==SYSERR)
    kprintf("ERROR TEST CASE 23 !!! -2\n\r"); 
  
  if(pipdelete(pipe)==SYSERR)
    kprintf("ERROR TEST CASE 24 !!! -2\n\r");  
  
  kprintf("TEST 3 COMPLETE\n\r");
  
}

void test4(void){
  
  pid32 r, w;
  pipid32 pipe;
  
  kprintf("TEST 4 BEGIN\n\r");
  
  if((pipe = pipcreate()) == SYSERR)
    kprintf("Test3 pipcreate failure\n\r");  
  
  r = create(aread,4096,20,"aread",3,pipe,400,100);
  w = create(awrite,4096,20,"awrite",3,pipe,400,300);
  
  
  if(rw ==1){  
    if(pipconnect(pipe,r,w)==SYSERR)
      kprintf("Test4 pipconnect failure\n\r");
  }
  else if(rw == 0){
    if(pipconnect(pipe,w,r)==SYSERR)
      kprintf("Test4 pipconnect failure\n\r");
  }
  
  
  resume(r);
  resume(w);
  
  sleep(3);
  
  kprintf("You should see 40 times 1 to 0. If nothing -18, if something -14\n\r");
  
  if(pipdisconnect(pipe)==SYSERR)
    kprintf("ERROR TEST CASE 25 !!! -2\n\r"); 
  
  if(pipdelete(pipe)==SYSERR)
    kprintf("ERROR TEST CASE 26 !!! -2\n\r");
  
  kprintf("TEST 4 COMPLETE\n\r");
}


void test5(void){
  
  pid32 r, w;
  pipid32 pipe;
  
  kprintf("TEST 5 BEGIN\n\r");
  
  if((pipe = pipcreate()) == SYSERR)
    kprintf("Test5 pipcreate failure\n\r");  
  
  r = create(aread,4096,20,"aread",3,pipe,500,500);
  w = create(writey,4096,20,"writey",3,pipe,100,100);
    
  if(rw ==1){
    if(pipconnect(pipe,r,w)==SYSERR)
      kprintf("Test5 pipconnect failure\n\r");
  }
  else if(rw == 0){
    if(pipconnect(pipe,w,r)==SYSERR)
      kprintf("Test5 pipconnect failure\n\r");
  }
  
  resume(r);
  sleep(2);
  
  kprintf("Test 5 Disconnect and Delete pipe\n\r");
  
  if(pipdisconnect(pipe)==SYSERR)
    kprintf("ERROR TEST CASE 27 !!! -1\n\r"); 
  
  if(pipdelete(pipe)==SYSERR)
    kprintf("ERROR TEST CASE 28 !!! -1\n\r");
  
  sleep(3);
  if(!isbadpid(r))
    kprintf("ERROR TEST CASE 32 !!! -8");
  
  resume(w);
  
  kprintf("TEST 5 COMPLETE\n\r");
}


void test6(void){
  
  pid32 r, w;
  pipid32 pipe;
  
  kprintf("TEST 6 BEGIN\n\r");
  
  if((pipe = pipcreate()) == SYSERR)
    kprintf("Test3 pipcreate failure\n\r");
  
  r = create(readey,4096,20,"readey",3,pipe,500,500);
  w = create(awrite,4096,20,"awrite",3,pipe,400,400);
    
  if(rw ==1){  
    if(pipconnect(pipe,r,w)==SYSERR)
      kprintf("Test6 pipconnect failure\n\r");
  }
  else if(rw == 0){
    if(pipconnect(pipe,w,r)==SYSERR)
      kprintf("Test6 pipconnect failure\n\r");
  }
  
  resume(w);
  sleep(2);  
  
  kprintf("Test 6 Disconnect and Delete pipe\n\r");
  
  if(pipdisconnect(pipe)==SYSERR)
    kprintf("ERROR TEST CASE 29 !!! -1\n\r"); 
  
  if(pipdelete(pipe)==SYSERR)
    kprintf("ERROR TEST CASE 30 !!! -1\n\r");  
    
  sleep(3);
  if(!isbadpid(w))
    kprintf("ERROR TEST CASE 31 !!! -8");
  
  resume(r);
  
  kprintf("TEST 6 COMPLETE\n\r");
}


void test7(void){
  
  pid32 r, w;
  pipid32 pipe;
  
  kprintf("TEST 7 BEGIN - EXTRA CREDIT\n\r");
  
  if((pipe = pipcreate()) == SYSERR)
    kprintf("Test3 pipcreate failure\n\r");  
  
  r = create(aread,4096,20,"aread",3,pipe,500,5);
  w = create(awrite,4096,20,"awrite",3,pipe,500,5);
    
  if(rw ==1){  
    if(pipconnect(pipe,r,w)==SYSERR)
      kprintf("Test7 pipconnect failure\n\r");
  }
  else if(rw == 0){
    if(pipconnect(pipe,w,r)==SYSERR)
      kprintf("Test7 pipconnect failure\n\r");
  }
  
  resume(r);
  resume(w);
  
  kill(getpid());
  
}


void tread(void){ 
}

void twrite(pipid32 pipe){ 
  if(pipwrite(pipe,&(input[0]),1) != SYSERR)
     rw = 1;
  else
    rw = 0;
}

int main(int argc, char **argv)
{  
    pid32 r,w;
    pipid32 pipe;    
  
    rw = 2;
    if((pipe = pipcreate()) == SYSERR)
      kprintf("Main pipcreate failure\n\r");  
  
    r = create(tread,2048,20,"tread",0);
    w = create(twrite,2048,20,"twrite",1,pipe);
    
    if(pipconnect(pipe,r,w)==SYSERR)
      kprintf("Main pipconnect failure\n\r"); 
    
    resume(w);    
    sleep(2);    
    resume(r);
    if(pipdisconnect(pipe)==SYSERR)
      kprintf("Main pipdisconnect failure\n\r");
    if(pipdelete(pipe)==SYSERR)
      kprintf("Main delete failure\n\r");    
       
    kprintf("Begin TA MAIN\n\r");
    
    test1();
    test2();    
    test3();
    test4();
    
    test5();    
    test6();
    
    test7();
    
	
    kprintf("End TA MAIN\n\r");
    return OK;
	
}
