#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>

int main()
{
int id,sid,*p,n,s=0;
struct sembuf v;
id=shmget(4,4,IPC_CREAT|0664);
sid=semget(4,2,IPC_CREAT|0664);

printf("starting....\n");
v.sem_num=1;
v.sem_op=0;
v.sem_flg=0;
semop(sid,&v,1);

p=shmat(id,0,0);
n=*p;
printf("Received.....\n");
while(n)
{
s=s*10+n%10;
n/=10;
}
*p=s;
printf("retransmitted\n");
semctl(sid,0,SETVAL,0);
semctl(sid,1,SETVAL,1);

printf("Done\n");
return 0;
}
