#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main(){
    srand(time(NULL));
    int n=16;
    int arr[n];
    for(int i=0;i<n;i++){
        arr[i]=rand();
    }
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }

return 0;
}
// 14793 24918 25813 32408 19578 14719 13791 24611 1565 23827 6132 6323 28733 21113 20141 6413 
