#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>
#include<unistd.h>

#define right n-1
#define left n%5

int t;
time_t start,now;
int state[5];

sem_t chopstick_semaphores[5];

void take_chopstick(int n, int random){
    if(state[left]==0){
        state[left]=1;
        sem_wait(&chopstick_semaphores[left]);
        sem_wait(&chopstick_semaphores[right]);
        state[right]=1;
    }
    else if(state[right]==0){
        state[right]=1;
        sem_wait(&chopstick_semaphores[right]);
        sem_wait(&chopstick_semaphores[left]);
        state[left]=1;
    }
    else{
        while(state[left]==1 && state[right]==1);
        if(state[left]==0){
        state[left]=1;
        sem_wait(&chopstick_semaphores[left]);
        sem_wait(&chopstick_semaphores[right]);
        state[right]=1;
        }
        else if(state[right]==0){
            state[right]=1;
            sem_wait(&chopstick_semaphores[right]);
            sem_wait(&chopstick_semaphores[left]);
            state[left]=1;
        }
    }
    now=time(NULL);
    long long here=(now-start);
    printf("time: %lld | Philosopher %d has started eating for %d seconds\n",here,n,random);
}

void put_chopstick(int n){
    state[left]=state[right]=0;
    sem_post(&chopstick_semaphores[left]);
    sem_post(&chopstick_semaphores[right]);
    now=time(NULL);
    long long here=(now-start);
    printf("time: %lld | Philosopher %d has finished eating\n",here,n);
}

void* simulate(void* arg){
    while(1){
        int n=*((int*)arg);
        int random;
        random=rand()%t+1;
        now=time(NULL);
        long long here=(now-start);
        printf("time: %lld | Philosopher %d will think for %d seconds\n",here,n,random);
        sleep(random);
        now=time(NULL);
        here=(now-start);
        printf("time: %lld | Philosopher %d has become hungry, will attempt to eat\n",here,n);
        random=rand()%t+1;
        take_chopstick(n,random);
        sleep(random);
        put_chopstick(n);
    }
    return NULL;
}

int main(){
    printf("Enter maximum time a philosopher can think/eat: ");
    scanf("%d",&t);
    srand(time(NULL));
    pthread_t philosophers[5];
    int number[5];
    for(int i=0;i<5;i++){
        sem_init(&chopstick_semaphores[i],0,1);
        number[i]=i+1;
        state[i]=0;
    }
    start= time(NULL);
    for(int i=0;i<5;i++){
        pthread_create(&philosophers[i],NULL,simulate,&number[i]);
    }

    for(int i=0;i<5;i++){
        pthread_join(philosophers[i],NULL);
    }

    for(int i=0;i<5;i++){
        sem_destroy(&chopstick_semaphores[i]);
    }
return 0;
}