#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main(){
    srand(time(NULL));
    int arr[300];
    for(int i=0;i<300;i++){
        arr[i]=rand();
    }
    for(int i=0;i<300;i++){
        printf("%d ",arr[i]);
    }

return 0;
}