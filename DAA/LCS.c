#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,m;
    printf("Enter lengths of the two sequences: ");
    scanf("%d%d",&n,&m);
    char a[n+1],b[m+1];
    a[n]=b[n]='\0';
    printf("Enter the two sequences: \n");
    while((getchar())!='\n');
    fgets(a,n+1,stdin);
    while((getchar())!='\n');
    fgets(b,m+1,stdin);
    int arr[m+1][n+1];
    for(int i=0;i<=n;i++){
        arr[0][i]=0;
    }
    for(int i=0;i<=m;i++){
        arr[i][0]=0;
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(a[j-1]==b[i-1]){
                arr[i][j]=arr[i-1][j-1]+1;
            }
            else{
                arr[i][j]=__max(arr[i-1][j],arr[i][j-1]);
            }
        }
    }
    printf("Matrix of solutions: \n");
    printf("%c\t%3d ",'-',0);
    for(int i=0;i<n;i++){
        printf("%3c ",a[i]);
    }
    printf("\n\n");
    for(int i=0;i<=m;i++){
        if(i==0){
            printf("%d \t",0);
        }
        else
        printf("%c\t",b[i-1]);
        for(int j=0;j<=n;j++){
            printf("%3d ",arr[i][j]);
        }
        printf("\n");
    }
    printf("The length of the longest common subsequence is : %d\n",arr[m][n]);
    printf("One of the valid longest subsequences is:\n");
    char s[arr[m][n]+1];
    s[arr[m][n]]='\0';
    int i=m,j=n;
    while(arr[i][j]>0){
        if(arr[i-1][j]==arr[i][j]){
            i--;
        }
        else{
            s[arr[i][j]-1]=b[i-1];
            i--;
            j--;
        }
    }
    if(arr[m][n]!=0)
    printf("%s\n",s);
    else
    printf("No common subsequence\n");

return 0;
}