#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

typedef struct arguments{
    int size;
    int* arr;
}arguments;

int cmpfunc (const void * a, const void * b) {//qsort comparator
   return ( *(int*)a - *(int*)b ); 
}

void* avg(void* argptr){
    arguments* args=(arguments*) argptr;
    float average=0;
    for(int i=0;i<args->size;i++){
        average+=args->arr[i];
    }
    average/=args->size;
    printf("The average of the %d values is %f\n",args->size,average);
    return NULL;
}
void* maxm(void* argptr){
    arguments* args=(arguments*) argptr;
    int max=args->arr[0];
    for(int i=0;i<args->size;i++){
        if(args->arr[i]>max){
            max=args->arr[i];
        }
    }
    printf("The maximum of the %d values is %d\n",args->size,max);
    return NULL;
}

void* median(void* argptr){
    arguments* args=(arguments*) argptr;
    qsort(args->arr,args->size,sizeof(int),cmpfunc);
    float med;
    if(args->size%2==1){
        med=args->arr[args->size/2];
    }
    else{
        med=(args->arr[args->size/2]+args->arr[args->size/2+1])/2.0;
    }
    printf("The median of the %d values is %.2f\n",args->size,med);
    return NULL;
}

int main(int argc, char* argv[]){
    argc--;
    arguments a,b,c;
    a.size=b.size=c.size=argc;
    a.arr=malloc(argc*sizeof(int));
    b.arr=malloc(argc*sizeof(int));
    c.arr=malloc(argc*sizeof(int));
    for(int i=0;i<argc;i++){
        a.arr[i]=b.arr[i]=c.arr[i]=atoi(argv[i+1]);
    }
    pthread_t t1,t2,t3;
    pthread_create(&t2,NULL,maxm,(void*)&c);
    pthread_create(&t1,NULL,median,(void*)&a);
    pthread_create(&t3,NULL,avg,(void*)&b);

    pthread_join(t1, NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);

return 0;
}