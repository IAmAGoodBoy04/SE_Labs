#include<stdio.h>
#include<stdlib.h>
#include<wchar.h>
#include<locale.h>

int count=1;

int find(int x, int* column, int n){
    for(int i=0;i<n;i++){
        if(column[i]==x){
            return 1;
        }
    }
    return 0;
}

void printqueens(int* column,int n){
    wprintf(L"Solution %d:\n",count);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(j!=column[i]){
                wprintf(L"⬜ ");
            }
            else{
                wprintf(L"♕  ");
            }
        }
        wprintf(L"\n");
    }
    wprintf(L"\n");
}

void calculate(int n, int* column,int i,int j){
    column[i]=j;
    if(i>0){
        for(int x=i-1;x>=0;x--){
            if(column[x]==j-(i-x) || column[x]==j+(i-x)){
                column[i]=-1;
                return;
            }
        }
    }
    if(i==n-1){
        printqueens(column,n);
        count++;
        column[i]=-1;
    }
    for(int x=0;x<n;x++){
        if(find(x,column,n)==0){
            calculate(n,column,i+1,x);
        }
    }
    column[i]=-1;
}

int main(){
    setlocale(LC_CTYPE,"");
    int n;
    wprintf(L"Enter value of N : ");
    scanf("%d",&n);
    int column[n];
    for(int i=0;i<n;i++){
        column[i]=-1;
    }
    for(int i=0;i<n;i++){
        calculate(n,column,0,i);
    }

return 0;
}