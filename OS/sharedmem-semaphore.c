#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/shm.h>	/* Include this to use shared memory */
#include<sys/sem.h>	/* Include this to use semaphores */

//int semop ( int semid, struct sembuf *sops, unsigned nsops)
#define P(s) semop(s, &pop, 1)  /* pop P(s) operation */
#define V(s) semop(s, &vop, 1)  /* vop V(s) operation */
int main()
{
	int shmid, status;
	int *a,*b;
	int i;

	int semid1, semid2 ;
	struct sembuf pop, vop ;
	semid1 = semget(IPC_PRIVATE, 1, 0777|IPC_CREAT);
	semid2 = semget(IPC_PRIVATE, 1, 0777|IPC_CREAT);

	semctl(semid1, 0, SETVAL, 0);
	semctl(semid2, 0, SETVAL, 1);

	pop.sem_num = vop.sem_num = 0;
	pop.sem_flg = vop.sem_flg = 0;
	pop.sem_op = -1 ; vop.sem_op = 1 ;

	shmid = shmget(IPC_PRIVATE, 1*sizeof(int), 0777|IPC_CREAT);
	
	if (fork() == 0) 
	{
		/* Child Process */
		b = (int *) shmat(shmid, 0, 0);

		for( i=0; i< 10; i++) 
		{
			P(semid1);
			sleep(rand()%3);
			printf("Child reads: %d\n",b[0]);
			fflush(stdout);
			V(semid2);
		}
		shmdt(b);
	}
	else {

		/* Parent Process */

		a = (int *) shmat(shmid, 0, 0);

		a[0] = 0; 
		for( i=0; i< 10; i++) 
		{
			P(semid2);
			sleep(rand()%3);
			a[0] = i;
			printf("Parent writes: %d\n",a[0]);
			fflush(stdout);
			V(semid1);
		}
		wait(&status);
		shmdt(a);
		shmctl(shmid, IPC_RMID, 0);

		semctl(semid1, 0, IPC_RMID, 0);
		semctl(semid2, 0, IPC_RMID, 0);
	}
}
