#include<stdio.h>
#include<stdlib.h>

#define inf 0x7fffffff

int extractmin(int** distances,int n,int* visited){
    int min=inf,minindex=0;
    for(int i=0;i<n;i++){
        if(distances[0][i]<min && visited[i]==0){
            min=distances[0][i];
            minindex=i;
        }
    }
    visited[minindex]=1;
    return minindex;
}

void relax(int** graph,int u, int v, int** distances){
    if(graph[u][v]<distances[0][v]){
        distances[0][v]=graph[u][v]+distances[0][u];
        distances[1][v]=u;
    }
}

void printpath(int ** distances, int source){
    if(source==-1){
        return;
    }
    printpath(distances,distances[1][source]);
    printf("%c -> ",(source+'a'));
    return;
}

int** dijkstra(int **graph, int source,int n){
    int** distances=malloc(2*sizeof(int*));
    for(int i=0;i<2;i++){
        distances[i]=malloc(n*sizeof(int));
    }
    int visited[n];
    for(int i=0;i<n;i++){
        distances[0][i]=inf;
        visited[i]=0;
    }
    distances[0][source]=0;
    distances[1][source]=-1;
    int u;
    for(int i=0;i<n;i++){
        u=extractmin(distances,n,visited);
        for(int j=0;j<n;j++){
            if(visited[j]==0 && graph[u][j]!=0){
                relax(graph,u,j,distances);
            }
        }
    }

    return distances;
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
        printf("Enter weight of edge %c -> %c: ", v1, v2);
        while((getchar()) != '\n');
        scanf("%d", &w);
        graph[v1i][v2i] = w;
        while((getchar()) != '\n');
    }
    printf("\nEnter source vortex: ");
    scanf("%c",&v1);
    int** distances=dijkstra(graph,v1-'a',nV);
    printf("\nThe shortest paths to the other vertices from the source as per Dijkstra's algorithm is:\n");
    for(int i=0;i<nV;i++){
        if(i!=v1-'a'){
            printpath(distances,distances[1][i]);
            printf("%c\tcost: %d\n",(i+'a'),distances[0][i]);
        }
        else{
            printf("%c\tcost: 0\n",i+'a');
        }
    }

    for(int i=0;i<nV;i++){
        free(graph[i]);
    }
    free(graph);
    free(distances);

return 0;
}