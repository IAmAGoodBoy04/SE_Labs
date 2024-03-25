#include<stdio.h>
#include<stdlib.h>

#define inf 0x7fffffff
int extractmin(int* key,int n){
    int min=inf,minindex=0;
    for(int i=0;i<n;i++){
        if(key[i]<min){
            min=key[i];
            minindex=i;
        }
    }
    key[minindex]=inf;
    return minindex;
}

int* mst_prim(int** graph, char root,int n){
    int *parents=malloc(n*sizeof(int));
    int key[n];
    int visited[n];
    for(int i=0;i<n;i++){
        visited[i]=0;
        parents[i]=-1;
        key[i]=inf;
    }
    key[root-'a']=0;
    int u;
    for(int i=0;i<n;i++){
        u=extractmin(key,n);
        visited[u]=1;
        for(int j=0;j<n;j++){
            if(visited[j]==0 && graph[u][j]!=0){
                if(graph[u][j]<key[j]){
                    key[j]=graph[u][j];
                    parents[j]=u;
                }
            }
        }
    }

    return parents;
}

int main(){
    int nV,nE,w;
    char v1,v2;
    printf("Enter number of vertices: ");
    scanf("%d", &nV);
    printf("Enter number of edges: ");
    scanf("%d", &nE);
    int **graph = (int **)malloc(nV * sizeof(int *));
    for(int i=0;i<nV;i++){
        graph[i] = (int *)calloc(nV,sizeof(int));
    }

    while((getchar()) != '\n');
    printf("Enter the edges as vortex1 vortex2, where names of vertices start from 'a': \n");
    for(int i=0;i<nE;i++){
        scanf("%c %c", &v1, &v2);
        int v1i=v1-'a';
        int v2i=v2-'a';
        printf("Enter weight of edge %c <-> %c: ", v1, v2);
        while((getchar()) != '\n');
        scanf("%d", &w);
        graph[v1i][v2i] = w;
        graph[v2i][v1i] = w;
        while((getchar()) != '\n');
    }
    printf("\nEnter root vortex: ");
    scanf("%c",&v1);
    printf("\nThe edges in the Minimum spanning tree as found by Prim's algorithm are:\n");
    int *parents=mst_prim(graph,v1,nV);
    for(int i=1;i<nV;i++){
        printf("%c<->%c  ",('a'+i),('a'+parents[i]));
    }
    int cost=0;
    for(int i=1;i<nV;i++){
        cost+=graph[i][parents[i]];
    }
    printf("\n\nThe cost of the minimum spanning tree is: %d\n",cost);

    for(int i=0;i<nV;i++){
        free(graph[i]);
    }
    free(graph);
    free(parents);
return 0;
}