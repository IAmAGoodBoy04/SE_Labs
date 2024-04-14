#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/shm.h>	/* Include this to use shared memory */

int main()
{
	int shmid, status;
	int *a,*b;
	int i;

	shmid = shmget(IPC_PRIVATE, 1*sizeof(int), 0777|IPC_CREAT);
	
	if (fork() == 0) 
	{
		/* Child Process */
		b = (int *) shmat(shmid, 0, 0);

		for( i=0; i< 10; i++) 
		{
			sleep(rand()%3);
			printf("Child reads: %d\n",b[0]);
			fflush(stdout);
		}
		shmdt(b);
	}
	else {

		/* Parent Process */

		a = (int *) shmat(shmid, 0, 0);

		a[0] = 0; 
		for( i=0; i< 10; i++) 
		{
			sleep(rand()%3);
			a[0] = i;
			printf("Parent writes: %d\n",a[0]);
			fflush(stdout);
		}
		wait(&status);
		shmdt(a);
		shmctl(shmid, IPC_RMID, 0);
	}
}
