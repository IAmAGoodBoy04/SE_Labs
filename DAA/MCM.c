#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

char* parenthesize(int i, int j, int** arr){
    if(i==j){
        char* s=malloc(2*sizeof(char));
        s[0]='A'+i;
        s[1]='\0';
        return s;
    }
    char *l,*r;
    l=parenthesize(i,arr[i][j],arr);
    r=parenthesize(arr[i][j]+1,j,arr);
    char* s=malloc(256*sizeof(char));
    s[0]='(';
    s[1]='\0';
    strcat(s,l);
    strcat(s," x ");
    strcat(s,r);
    strcat(s,")");
    free(l);
    free(r);
    return s;
}


signed main(){
    srand(time(NULL));
    int n,temp;
    printf("Enter number of Martices: ");
    scanf("%d",&n);
    char a='A';
    int p[n+1];
    // printf("Enter dimensions of matrix %c: ",a++);
    // scanf("%dx%d",&p[0],&p[1]);
    for(int i=0;i<=n;i++){
        p[i]=rand()%46;
        if(p[i]<2){
            p[i]=2;
        }
    }
    printf("The array P is (random values): ");
    for(int i=0;i<=n;i++){
        printf("%d ",p[i]);
    }
    printf("\n");
    // temp=p[1];
    // for(int i=1;i<n;i++){
    //     printf("Enter dimensions of matrix %c: ",a++);
    //     scanf("%dx%d",&temp,&p[i+1]);
    //     if(temp!=p[i]){
    //         printf("Invalid dimensions\n");
    //         return 0;
    //     }
    // }
    int m[n][n];
    int** s=malloc(n*sizeof(int*));
    for(int i=0;i<n;i++){
        s[i]=malloc(n*sizeof(int));
        m[i][i]=0;
        s[i][i]=0;
    }
    int j;
    for(int l=2;l<=n;l++){
        for(int i=0;i<=n-l;i++){
            j=l+i-1;
            m[i][j]=INT_MAX;
            for(int k=i;k<j;k++){
                temp=m[i][k]+m[k+1][j]+p[i]*p[k+1]*p[j+1];
                if(temp<m[i][j]){
                    m[i][j]=temp;
                    s[i][j]=k;
                }
            }
        }
    }
    printf("The matrix of costs is: \n");
    for(int i=0;i<n;i++){
        for(int x=0;x<i;x++){printf("\t");}
        for(int j=i;j<n;j++){
            printf("%d\t",m[i][j]);
        }
        printf("\n");
    }
    printf("The matrix s is: \n");
    for(int i=1;i<n;i++){
        for(int x=1;x<i;x++){printf("\t");}
        for(int j=i;j<n;j++){
            printf("%d\t",s[i][j]+1);
        }
        printf("\n");
    }

    printf("The parenthesized expression is:\n");
    char* exp=parenthesize(0,n-1,s);
    printf("%s\n",exp);
    printf("The number of scalar multiplications with optimal parenthesization are: %d\n",m[0][n-1]);
    int naive=0;
    for(int i=1;i<n;i++){
        temp=p[0]*p[i]*p[i+1];
        naive+=temp;
    }
    printf("The number of scalar multiplications with naive parenthesization are: %d\n",naive);
    for(int i=0;i<n;i++){
        free(s[i]);
    }
    free(s);
    free(exp);

return 0;
}