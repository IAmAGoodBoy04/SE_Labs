#include<stdio.h>
#include<stdlib.h>

int main(){
    int n;
    printf("Enter number of stations: ");
    scanf("%d", &n);
    int a[n],b[n],ta[n-1],tb[n-1],e1,e2,x1,x2,path[2][n];
    printf("Enter entry times for lines 1 and 2: ");
    scanf("%d%d", &e1, &e2);
    printf("Enter exit times for lines 1 and 2: ");
    scanf("%d%d", &x1, &x2);
    printf("Enter processing times for stations in line 1:\n");
    for(int i=0;i<n;i++){
        scanf("%d", &a[i]);
    }
    printf("Enter processing times for stations in line 2:\n");
    for(int i=0;i<n;i++){
        scanf("%d", &b[i]);
    }
    printf("Enter transfer times from line 1 to line 2:\n");
    for(int i=0;i<n-1;i++){
        scanf("%d", &ta[i]);
    }
    printf("Enter transfer times from line 2 to line 1:\n");
    for(int i=0;i<n-1;i++){
        scanf("%d", &tb[i]);
    }
    a[0]+=e1;
    b[0]+=e2;
    path[0][0]=1;
    path[1][0]=2;
    for(int i=1;i<n;i++){
        if(a[i]+a[i-1]<a[i]+b[i-1]+tb[i-1]){
            a[i]+=a[i-1];
            path[0][i]=1;
        }
        else{
            a[i]+=b[i-1]+tb[i-1];
            path[0][i]=2;
        }
        if(b[i]+b[i-1]<b[i]+a[i-1]+ta[i-1]){
            b[i]+=b[i-1];
            path[1][i]=2;
        }
        else{
            b[i]+=a[i-1]+ta[i-1];
            path[1][i]=1;
        }
    }
    a[n-1]+=x1;
    b[n-1]+=x2;
    int follow=a[n-1]<b[n-1]?1:2;
    int f[n];
    f[n-1]=follow;
    for(int i=n-2;i>=0;i--){
        f[i]=path[f[i+1]-1][i+1];
    }

    printf("The matrix of minimum costs for each of the stations is (exit cost has been added to the last station):\n");
    for (int i = 0; i < n; i++){
        printf("%4d ",a[i]);
    }printf("\n");
    for (int i = 0; i < n; i++){
        printf("%4d ",b[i]);
    }printf("\n");
    printf("Matrix showing path followed for each station: (each number represents the line used to arrive to that station)\n");
    for(int i=0;i<2;i++){
        for(int j=0;j<n;j++){
            printf("%d  ",path[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("The path followed was: (entry and exit times have been added to the first and last elements)\n");
    printf("Line 1 -> ");
    for(int i=0;i<n;i++){
        if(f[i]==1){
            printf("%d\t",a[i]);
        }
        else{
            printf("\t");
        }
    }
    printf("\n");
    printf("Line 2 -> ");
    for(int i=0;i<n;i++){
        if(f[i]==2){
            printf("%d\t",b[i]);
        }
        else{
            printf("\t");
        }
    }
    printf("\n");
    printf("\nThe minimum time to get through all the stations is: %d",follow==1?a[n-1]:b[n-1]);

return 0;
}