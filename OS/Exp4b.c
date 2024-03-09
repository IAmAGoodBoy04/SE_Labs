#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>


pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

typedef struct t_args{
    int* arr;
    int size;
}t_args;

void* add_element(void* ptr){
    pthread_mutex_lock(&mutex);
    int val=rand();
    t_args* p=(t_args*)ptr;
    p->arr=realloc(p->arr,(p->size+1)*sizeof(int));
    p->arr[p->size]=val;
    p->size++;
    printf("Added %d to array\n",val);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* delete_two(void* ptr){
    srand(time(0));
    pthread_mutex_lock(&mutex);
    t_args* p=(t_args*)ptr;
    if(p->size<2){
        printf("Array too small!\n");
        return NULL;
    }
    printf("removed %d and %d from array\n",p->arr[p->size-1],p->arr[p->size-2]);
    p->arr=realloc(p->arr,(p->size-2)*sizeof(int));
    p->size-=2;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(){

    t_args ar;
    pthread_t t1,t2,t3,t4,t5;
    ar.arr=malloc(2*sizeof(int));
    ar.size=2;
    for(int i=0;i<ar.size;i++){//initialising first element to 5.
        ar.arr[i]=rand();
    }
    printf("initial array:\n");
    for(int i=0;i<ar.size;i++){
        printf("%d ",ar.arr[i]);
    }
    printf("\n");
    pthread_create(&t1,NULL,add_element,(void*)&ar);
    pthread_create(&t2,NULL,add_element,(void*)&ar);
    pthread_create(&t3,NULL,add_element,(void*)&ar);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_create(&t4,NULL,delete_two,(void*)&ar);
    pthread_create(&t5,NULL,delete_two,(void*)&ar);
    pthread_join(t4,NULL);
    pthread_join(t5,NULL);
    printf("final array:\n");
    for(int i=0;i<ar.size;i++){
        printf("%d ",ar.arr[i]);
    }
    printf("\n");

return 0;
}