#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 100000
FILE* file;

void runinsertionsort(int *arr, int len){
    int temp[len];
    for(int i=0;i<len;i++){
        temp[i]=arr[i];
    }
    clock_t time=clock();
    int key,j;
    for(int i=1;i<len;i++){
        key=temp[i];
        j=i;
        while(temp[j-1]>key && j>0){
            temp[j]=temp[j-1];
            j--;
        }
        temp[j]=key;
    }
    time=clock()-time;
    double tme=(double)time/CLOCKS_PER_SEC;
    fprintf(file,"%lf,",tme);
}

void runselectionsort(int *arr, int len){
    int temp[len];
    for(int i=0;i<len;i++){
        temp[i]=arr[i];
    }
    clock_t time=clock();
    int max,ind,tem;
    for(int i=len-1;i>=0;i--){
        max=INT_MIN;
        for(int j=0;j<=i;j++){
            if(temp[j]>max){
                max=temp[j];
                ind=j;
            }
        }
        tem=temp[i];
        temp[i]=temp[ind];
        temp[ind]=tem;
    }
    time=clock()-time;
    double tme=(double)time/CLOCKS_PER_SEC;
    fprintf(file,"%lf\n",tme);
}

int main(){
    if(fopen("input.txt","r")==NULL){
        srand(time(NULL));
        file=fopen("input.txt","w");
        for(int i=0;i<SIZE;i++){
            fprintf(file,"%d ",rand());
        }
        fclose(file);
    }
    file=fopen("input.txt","r");
    int arr[SIZE];
    for(int i=0;i<SIZE;i++){
        fscanf(file,"%d ",&arr[i]);
    }
    fclose(file);
    file=fopen("Exp_1_B_timings.csv","w");
    fprintf(file,"insertion sort,selection sort\n");
    for(int i=1000;i<=SIZE;i+=1000){
        runinsertionsort(arr,i);
        runselectionsort(arr,i);
    }
    fclose(file);

    return 0;
}