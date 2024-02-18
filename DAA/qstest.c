#include<stdio.h>
#include<stdlib.h>
void swap(int* a, int* b){
    int temp=*b;
    *b=*a;
    *a=temp;
}
void quicksort(int* arr, int start, int end){
    if(end-start<2){
        return;
    }
    int pivot=start;
    int lower=end-1,higher=start+1;
    while(1){
        while(arr[higher]<=arr[pivot]){
            higher++;
        }
        while(lower>start && arr[lower]>=arr[pivot]){
            lower--;
        }
        if(lower<higher){
            swap(&arr[pivot],&arr[lower]);
            pivot=lower;
            break;
        }
        swap(&arr[lower],&arr[higher]);
        lower--;
        higher++;
    }
    quicksort(arr,start,pivot);
    quicksort(arr,pivot+1,end);
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
int main(){
    int arr[301];
    int temp[300];
    arr[300]=0x7fffffff;
    for(int i=0;i<300;i++){
        scanf("%d",&arr[i]);
        temp[i]=arr[i];
    }
    quicksort(arr,0,300);
    qsort(temp,300,sizeof(int),cmpfunc);
    for(int i=0;i<300;i++){
        if(arr[i]!=temp[i]){
            printf("NOT EQUAL!! %d\n",i);
        }
    }
    printf("EQUAL\n");


return 0;
}