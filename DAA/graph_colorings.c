#include<stdio.h>
#include<stdlib.h>

int count=0;

void printcoloring(int* colors,int n){
    printf("Coloring %d :\n",count);
    for(int i=0;i<n;i++){
        printf("%c -> %d\t",('a'+i),colors[i]);
        if(i%2==1){
            printf("\n");
        }
    }
    printf("\n");
}

int find(int* arr, int n, int k){
    for(int i=0;i<n;i++){
        if(arr[i]==k){
            return 1;
        }
    }
    return 0;
}

int mex1(int* arr,int n){
    for(int i=1;i<=n;i++){
        if(find(arr,n,i)==0){
            return i;
        }
    }
}

int findchno(int** graph, int v){
    int colors[v];
    for(int i=0;i<v;i++){
        colors[i]=0;
    }
    colors[0]=1;
    int rowcolor[v];
    for(int i=1;i<v;i++){
        for(int j=0;j<v;j++){
            if(graph[i][j]==1){
                rowcolor[j]=colors[j];
            }
            else{
                rowcolor[j]=0;
            }
        }
        colors[i]=mex1(rowcolor,v);
    }
    int max=-1;
    for(int i=0;i<v;i++){
        if(colors[i]>max){
            max=colors[i];
        }
    }
    return max;
}

int chk_valid(int* row, int n, int* colors, int c){
    for(int i=0;i<n;i++){
        if(row[i]){
            if(colors[i]==c){
                return 0;
            }
        }
    }
    return 1;
}

void calculate(int** graph, int n, int* colors,int i, int cno){
    for(int j=0;j<cno;j++){
        if(chk_valid(graph[i],n,colors,j+1)){
            colors[i]=j+1;
            if(i+1<n)
                calculate(graph,n,colors,i+1,cno);
            else{
                count++;
                printcoloring(colors,n);
            }
        }
    }
    colors[i]=0;
}

int main(){
    int V,E;
    char v1,v2;
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);
    int **graph = (int **)malloc(V * sizeof(int *));
    for(int i=0;i<V;i++){
        graph[i] = (int *)calloc(V,sizeof(int));
    }

    printf("Enter the edges as vortex1 vortex2, where names of vertices start from 'a': \n");
    for(int i=0;i<E;i++){
        while((getchar()) != '\n');
        scanf("%c %c", &v1, &v2);
        int v1i=v1-'a';
        int v2i=v2-'a';
        graph[v1i][v2i] = 1;
        graph[v2i][v1i] = 1;
    }
    

    int chromatic=findchno(graph,V);
    printf("\nThe chromatic number of the graph is : %d\n",chromatic);
    printf("All the possible colorings of the graph using %d colors are :\n",chromatic);
    int col[V];
    for(int i=0;i<V;i++){
        col[i]=0;
    }
    calculate(graph,V,col,0,chromatic);
    

    for(int i=0;i<V;i++){
        free(graph[i]);
    }
    free(graph);
return 0;
}