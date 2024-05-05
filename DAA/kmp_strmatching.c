#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(){
    char str[1024];
    char pattern[256];
    printf("Enter a string : ");
    fgets(str,1023,stdin);
    printf("Enter the pattern : ");
    fgets(pattern,255,stdin);
    str[strlen(str)-1]=pattern[strlen(pattern)-1]='\0';
    int np=strlen(pattern),n=strlen(str);
    int table[np];
    memset(table,0,np*sizeof(int));
    int j=0;
    for(int i=1;i<np;i++){
        if(pattern[i]==pattern[j]){
            table[i]=j+1;
            j++;
        }
        else{
            j=0;
            if(pattern[i]==pattern[j]){
                table[i]=j+1;
                j++;
            }
        }
    }
    int found[n];
    int count=0;
    j=0;
    for(int i=0;i<n;i++){
        found[i]=0;
        if(str[i]==pattern[j]){
            j++;
            if(j==np){
                count++;
                j=0;
                for(int x=i;x>i-np;x--){
                    found[x]=1;
                }
            }
        }
        else{
            if(j>0){
                j=table[j-1];
                i--;
            }
        }
    }
    printf("\n%d pattern matches were found\n",count);
    if(count>0){
        printf("The pattern matches are as follows : ");
        for(int i=0;i<n;i++){
            if(found[i]==0)
            printf("%c",str[i]);
            else{
                printf("%c",toupper(str[i]));
            }
        }
        printf("\n");
    }

return 0;
}