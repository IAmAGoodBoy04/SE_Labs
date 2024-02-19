#include<stdio.h>
#include<stdlib.h>
typedef struct minmax{
    int min;
    int max;
}minmax;


minmax minmaxnormal(int* arr, int size){
    minmax retval;
    retval.max=INT_MIN;
    retval.min=INT_MAX;
    for(int i=0;i<size;i++){
        if(arr[i]>retval.max){
            retval.max=arr[i];
        }
        if(arr[i]<retval.min){
            retval.min=arr[i];
        }
    }
    return retval;
}

minmax minmaxdc(int *arr,int start, int end){
    minmax retval;
    if(start==end){
        retval.min=retval.max=arr[start];
        return retval;
    }
    if(end-start==1){
        retval.min=arr[start]<arr[end]?arr[start]:arr[end];
        retval.max=arr[start]>arr[end]?arr[start]:arr[end];
        return retval;
    }
    minmax left,right;
    int mid=(start+end)/2;
    left=minmaxdc(arr,start,mid);
    right=minmaxdc(arr,mid+1,end);
    retval.min=left.min<right.min?left.min:right.min;
    retval.max=left.max>right.max?left.max:right.max;
    return retval;
}

int main(){
    int arr[300];
    int temp[300];
    for(int i=0;i<300;i++){
        scanf("%d",&arr[i]);
        temp[i]=arr[i];
    }
    minmax a,b;
    a=minmaxnormal(arr,300);
    b=minmaxdc(temp,0,299);
    if(a.max==b.max && a.min==b.min){
        printf("%d, %d, %d, %d",a.max,a.min,b.max,b.min);
        printf("EQUAL\n");
    }
    else
    printf("EQUAL\n");


return 0;
}