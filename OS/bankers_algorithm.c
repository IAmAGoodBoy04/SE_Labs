#include<stdio.h>
#include<stdlib.h>

#define inf 0x7fffffff

int main(){
    printf("Enter number of processes : ");
    int n,c;
    scanf("%d",&n);
    printf("Enter number of resource types (no. of columns in the tables) : ");
    scanf("%d",&c);
    int total[c];
    int order[n];
    int available[c];
    printf("Enter total number of instances for each of the %d resources : \n",c);
    for(int i=0;i<c;i++){
        scanf("%d",&total[i]);
        available[i]=total[i];
    }
    int data[3][n][c];
    printf("Enter the number of allocated instances of each of the resources for :\n");
    for(int i=0;i<n;i++){
        printf("Process %d : ",i+1);
        for(int j=0;j<c;j++){
            scanf("%d",&data[0][i][j]);
            available[j]-=data[0][i][j];
        }
    }
    printf("Enter the max number of instances demanded by the different processes : \n");
    for(int i=0;i<n;i++){
        printf("Process %d : ",i+1);
        for(int j=0;j<c;j++){
            scanf("%d",&data[1][i][j]);
        }
    }
    printf("\nInitially, the availability status of the %d resources is as follows : \n",c);
    for(int i=0;i<c;i++){
        printf("%d   ",available[i]);
    }
    printf("\n");
    printf("\nThe need matrix is as follows : \n");
    for(int i=0;i<n;i++){
        for(int j=0;j<c;j++){
            data[2][i][j]=data[1][i][j]-data[0][i][j];
            printf("%d  ",data[2][i][j]);
        }
        printf("\n");
    }
    int found=0;
    for(int x=0;x<n;x++){
        printf("\n");
        for(int i=0;i<n;i++){
            found=1;
            for(int j=0;j<c;j++){
                found=found && (available[j]>=data[2][i][j]);
            }
            if(found){
                order[x]=i+1;
                found=i+1;
                break;
            }
        }
        if(found==0){
            printf("The processes are in a deadlock. \n");
            exit(0);
        }
        printf("Step %d : Allocate resources to process %d\n",x+1,found);
        for(int i=0;i<c;i++){
            available[i]+=data[0][found-1][i];
        }
        printf("The availability status of the %d resources after process %d has executed is as follows : \n",c,found);
        for(int i=0;i<c;i++){
            printf("%d   ",available[i]);
        }
        printf("\n");
        for(int i=0;i<c;i++){
            data[2][found-1][i]=inf;
        }
        printf("The need matrix after process %d has executed is as follows : \n",found);
        for(int i=0;i<n;i++){
            for(int j=0;j<c;j++){
                if(data[2][i][j]<inf)
                printf("%d  ",data[2][i][j]);
            }
            if(data[2][i][0]==inf){
                printf("executed");
            }
            printf("\n");
        }
    }
    printf("\nThe order of execution of the processes to avoid deadlock is as follows :\n");
    for(int i=0;i<n;i++){
        printf("%d -> ",order[i]);
    }
    printf("\b\b\b   \n");


return 0;
}