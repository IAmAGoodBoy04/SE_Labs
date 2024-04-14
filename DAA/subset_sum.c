#include<stdio.h>
#include<stdlib.h>

int count=0;
void printans(int* state, int* arr, int n){
    printf("Solution %d : ",count);
    for(int i=0;i<n;i++){
        if(state[i]){
            printf("%d + ",arr[i]);
        }
    }
    printf("\b\b \n");
}

void calculate(int* arr,int n, int target,int* state, int i,int curr,int remains){
    if(curr==target){
        count++;
        printans(state,arr,n);
        state[i]=0;
        return;
    }
    if(i==n-1){
        if(curr+arr[i]!=target){
            state[i]=0;
            return;
        }
        else{
            state[i]=1;
            count++;
            printans(state,arr,n);
            state[i]=0;
            return;
        }
    }
    if(curr+arr[i]<=target){
        state[i]=1;
        calculate(arr,n,target,state,i+1,curr+arr[i],remains-arr[i]);
    }
    if(curr+remains>=target){
        state[i]=0;
        calculate(arr,n,target,state,i+1,curr,remains-arr[i]);
    }
    state[i]=0;
}

int main(){
    int n,remains=0;
    printf("Enter number of elements in array : ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter the elements of the array : \n");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    printf("Enter the target sum : ");
    int target;
    scanf("%d",&target);
    printf("\nThe subarrays which add up to the target sum are :\n");
    int state[n];
    for(int i=0;i<n;i++){
        remains+=arr[i];
        state[i]=0;
    }
    calculate(arr,n,target,state,0,0,remains);

return 0;
}