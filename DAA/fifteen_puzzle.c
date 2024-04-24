#include<stdio.h>
#include<stdlib.h>

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

#define inf 0x7fffffff

int count=0;

void swap(int* a, int* b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

void prarr(int **arr){
    if(count>0)
    printf("Step %d :\n",count);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(arr[i][j]!=16){
                printf("%-4d",arr[i][j]);
            }
            else{
                printf("*   ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int score(int** arr){
    int sc=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(arr[i][j]!=(4*i+j+1) && arr[i][j]!=16){
                sc++;
            }
        }
    }
    return sc;
}

void calculate(int** arr, int coordi,int coordj, int direction){
    if(score(arr)==0){
        printf("Solved!\n");
        return;
    }
    int scores[4];
    if(direction!=DOWN){
        if(coordi>0){
            swap(&arr[coordi][coordj],&arr[coordi-1][coordj]);
            scores[UP]=score(arr);
            swap(&arr[coordi][coordj],&arr[coordi-1][coordj]);
        }
        else{
            scores[UP]=inf;
        }
    }
    else{
        scores[UP]=inf;
    }
    if(direction!=UP){
        if(coordi<3){
            swap(&arr[coordi][coordj],&arr[coordi+1][coordj]);
            scores[DOWN]=score(arr);
            swap(&arr[coordi][coordj],&arr[coordi+1][coordj]);
        }
        else{
            scores[DOWN]=inf;
        }
    }
    else{
        scores[DOWN]=inf;
    }
    if(direction!=LEFT){
        if(coordj<3){
            swap(&arr[coordi][coordj],&arr[coordi][coordj+1]);
            scores[RIGHT]=score(arr);
            swap(&arr[coordi][coordj],&arr[coordi][coordj+1]);
        }
        else{
            scores[RIGHT]=inf;
        }
    }
    else{
        scores[RIGHT]=inf;
    }
    if(direction!=RIGHT){
        if(coordj>0){
            swap(&arr[coordi][coordj],&arr[coordi][coordj-1]);
            scores[LEFT]=score(arr);
            swap(&arr[coordi][coordj],&arr[coordi][coordj-1]);
        }
        else{
            scores[LEFT]=inf;
        }
    }
    else{
        scores[LEFT]=inf;
    }
    int minindex=-1,min=inf;
    for(int i=0;i<4;i++){
        if(scores[i]<=min){
            minindex=i;
            min=scores[i];
        }
    }
    if(minindex==UP){
        swap(&arr[coordi][coordj],&arr[coordi-1][coordj]);
        count++;
        prarr(arr);
        calculate(arr,coordi-1,coordj,UP);
    }
    else if(minindex==DOWN){
        swap(&arr[coordi][coordj],&arr[coordi+1][coordj]);
        count++;
        prarr(arr);
        calculate(arr,coordi+1,coordj,DOWN);
    }
    else if(minindex==RIGHT){
        swap(&arr[coordi][coordj],&arr[coordi][coordj+1]);
        count++;
        prarr(arr);
        calculate(arr,coordi,coordj+1,RIGHT);
    }
    else if(minindex==LEFT){
        swap(&arr[coordi][coordj],&arr[coordi][coordj-1]);
        count++;
        prarr(arr);
        calculate(arr,coordi,coordj-1,LEFT);
    }
return;
}


int main(){
    int **arr;
    arr=malloc(4*sizeof(int*));
    for(int i=0;i<4;i++){
        arr[i]=malloc(4*sizeof(int));
    }
    int arr2[16];
    int sigma=0,x=0;
    int coordi,coordj;
    printf("Enter the initial state (16 for blank tile):\n");
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            scanf("%d",&arr[i][j]);
            arr2[4*i+j]=arr[i][j];
            if(arr[i][j]==16){
                coordi=i;
                coordj=j;
                x=(i+j)%2==1;
            }
        }
    }
    sigma+=x;
    for(int i=0;i<16;i++){
        for(int j=i+1;j<16;j++){
            if(arr2[j]<arr2[i]){
                sigma++;
            }
        }
    }
    if(sigma%2==1){
        printf("The goal state is unreachable.\n");
        return 0;
    }
    printf("\nThe steps for solving this puzzle are: \n");
    printf("Initial state : \n");
    prarr(arr);
    if(score(arr)==0){
        printf("Already solved.\n");
        return 0;
    }
    calculate(arr,coordi,coordj,-1);

    for(int i=0;i<4;i++){
        free(arr[i]);
    }
    free(arr);

return 0;
}