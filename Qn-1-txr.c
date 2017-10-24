#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>

int main(int argc,char **argv)
{
if(argc!=2)
{
printf("Usage:./txr1 number\n");
return;
}
int id,sid,*p;
struct sembuf v;
id=shmget(4,4,IPC_CREAT|0664);
sid=semget(4,2,IPC_CREAT|0664);

semctl(sid,1,SETVAL,1);

p=shmat(id,0,0);
*p=atoi(argv[1]);

printf("starting.....\n");
semctl(sid,1,SETVAL,0);
semctl(sid,0,SETVAL,1);

v.sem_num=0;
v.sem_op=0;
v.sem_flg=0;
semop(sid,&v,1);

printf("Reverse is : %d\n",*p);
return 0;
}
