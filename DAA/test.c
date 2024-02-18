#include<stdio.h>
#include<stdlib.h>
#define inf 0x7fffffff
void swap(int* a, int* b){
    int temp=*b;
    *b=*a;
    *a=temp;
}

void merge(int* arr,int start, int mid, int end){
    int L[mid-start+2],R[end-mid+1];
    L[mid-start+1]=R[end-mid]=inf;
    for(int i=start;i<=mid;i++){
        L[i-start]=arr[i];
    }
    for(int i=mid+1;i<=end;i++){
        R[i-mid-1]=arr[i];
    }
    int i=0,l=0,r=0;
    for(int i=start;i<=end;i++){
        if(L[l]<R[r]){
            arr[i]=L[l];
            l++;
        }
        else{
            arr[i]=R[r];
            r++;
        }
    }
}

void mergesort(int* arr, int start, int end){
    if(start==end){
        return;
    }
    if(end-start<16){
        end++;
        int key,j;
        for(int i=start+1;i<end;i++){
            key=arr[i];
            j=i;
            while(j>0 && arr[j-1]>key){
                arr[j]=arr[j-1];
                j--;
            }
            arr[j]=key;
        }
        return;
    }
    int mid=(end+start)/2;
    mergesort(arr,start,mid);
    mergesort(arr,mid+1,end);
    merge(arr,start,mid,end);
}


void quicksort(int* arr, int start, int end){
    if(end-start<=17){
        int key,j;
        for(int i=start+1;i<end;i++){
            key=arr[i];
            j=i;
            while(arr[j-1]>key && j>0){
                arr[j]=arr[j-1];
                j--;
            }
            arr[j]=key;
        }
        return;
    }
    int mid=(start+end)/2,pivot,other;
    if(arr[start]>arr[mid]){
        pivot=start;
        other=mid;
    }else{
        pivot=mid;
        other=start;
    }
    pivot=arr[pivot]<arr[end-1]?pivot:arr[end-1]>arr[other]?end-1:other;
    int lower=end-1,higher=start;
    while(1){
        while(arr[higher]<=arr[pivot]){
            higher++;
        }
        while(lower>0 && arr[lower]>=arr[pivot]){
            lower--;
        }
        if(lower<=higher){
            if(pivot>higher){
                swap(&arr[pivot],&arr[higher]);
                pivot=higher;
            }
            else if(pivot<lower){
                swap(&arr[pivot],&arr[lower]);
                pivot=lower;
            }
            break;
        }
        swap(&arr[lower],&arr[higher]);
        lower--;
        higher++;
    }
    
    quicksort(arr,start,pivot);
    quicksort(arr,pivot+1,end);
}

int main(){
    int n;
    scanf("%d",&n);
    int arr[n+1];
    int temp[n];
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
        temp[i]=arr[i];
    }
    arr[n]=inf;
    quicksort(arr,0,n);
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    mergesort(temp,0,n-1);

    printf("\n");
    for(int  i=0;i<n;i++){
        if(arr[i]!=temp[i]){
            printf("Not equal!!!!\n\n");
            break;
        }
        if(i==n-1){
            printf("Equal!!!\n\n");
        }
    }

return 0;
}