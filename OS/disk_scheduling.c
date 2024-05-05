#include<stdio.h>
#include<stdlib.h>

int loc;

int abs(int a){
    if(a<0){
        return -1*a;
    }
    return a;
}

void swap(int *a, int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void reverse(int* arr, int n){
    for(int i=0;i<n/2;i++){
        swap(&arr[i],&arr[n-i-1]);
    }
}

int cmp_ascending(const void* x, const void* y){
    int* a=(int*) x;
    int* b=(int*) y;
    if(*a<*b){
        return -1;
    }
    return 1;
}

int headmovement(int *arr, int n){
    int ans=abs(arr[0]-loc);
    for(int i=1;i<n;i++){
        ans+=abs(arr[i]-arr[i-1]);
    }
    return ans;
}

void printdetails(int *arr, int n){
    printf("The order in which the disk requests are serviced are : \n");
    for(int i=0;i<n;i++){
        printf("%d ,",arr[i]);
    }
    printf("\b\b  \n");
}

int main(){
    printf("Enter number of cylinders on disk : ");
    int n,cy;
    scanf("%d",&cy);
    printf("Enter initial location of disk arm : ");
    scanf("%d",&loc);
    printf("Enter number of disk access requests : ");
    scanf("%d",&n);
    int* arr;
    int* copy;
    arr=malloc(n*sizeof(int));
    copy=malloc(n*sizeof(int));
    printf("Enter sequence of cylinder numbers of disk access requests : \n");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
        copy[i]=arr[i];
    }
    printf("Using FCFS :\n");
    printdetails(arr,n);
    printf("Total head movement : %d\n\n",headmovement(arr,n));
    printf("Using SCAN :\n");
    qsort(copy,n,sizeof(int),cmp_ascending);
    int start=0;
    int last=copy[n-1];
    for(int i=0;i<n;i++){
        if(copy[i]>=loc){
            start=i;
            break;
        }
    }
    reverse(copy,n);
    reverse(copy,n-start);
    printdetails(copy,n);
    int movement;
    if(copy[n-1]>loc){
        movement=copy[n-1]-loc;
    }
    else{
        movement=cy-1-loc+cy-1-copy[n-1];
    }

    printf("Total head movement : %d\n\n",movement);
    printf("Using C-SCAN :\n");
    qsort(copy,n,sizeof(int),cmp_ascending);
    reverse(copy,n);
    reverse(copy,n-start);
    reverse(&copy[n-start],start);
    printdetails(copy,n);
    if(copy[n-1]>loc){
        movement=copy[n-1]-loc;
    }
    else{
        movement=cy-1-loc+cy-1+copy[n-1];
    }
    printf("Total head movement : %d\n\n",movement);
    free(copy);
    free(arr);
return 0;
}