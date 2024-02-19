#include<stdio.h>
#include<stdlib.h>
#define inf 0x7fffffff
#define int long long
#define ll long long

void printmat(ll ** arr, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%lld ",arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

ll** mmult(ll** a, ll** b, int size){
    ll** c=malloc(size*sizeof(ll*));
    for(int i=0;i<size;i++){
        c[i]=malloc(size*sizeof(ll));
    }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            c[i][j]=0;
            for(int k=0;k<size;k++){
                c[i][j]+=a[i][k]*b[k][j];
            }
        }
    }
    return c;
}


void sum(int** A, int** B, int** C, int tam) {
    int i, j;

    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract(int** A, int** B, int** C, int tam) {
    int i, j;

    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen(int** A, int** B, int** C, int tam) {
    if (tam == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newTam = tam/2;
    int** A11 = (int**)malloc(newTam * sizeof(int*));
    int** A12 = (int**)malloc(newTam * sizeof(int*));
    int** A21 = (int**)malloc(newTam * sizeof(int*));
    int** A22 = (int**)malloc(newTam * sizeof(int*));

    int** B11 = (int**)malloc(newTam * sizeof(int*));
    int** B12 = (int**)malloc(newTam * sizeof(int*));
    int** B21 = (int**)malloc(newTam * sizeof(int*));
    int** B22 = (int**)malloc(newTam * sizeof(int*));

    int** C11 = (int**)malloc(newTam * sizeof(int*));
    int** C12 = (int**)malloc(newTam * sizeof(int*));
    int** C21 = (int**)malloc(newTam * sizeof(int*));
    int** C22 = (int**)malloc(newTam * sizeof(int*));

    int** P1 = (int**)malloc(newTam * sizeof(int*));
    int** P2 = (int**)malloc(newTam * sizeof(int*));
    int** P3 = (int**)malloc(newTam * sizeof(int*));
    int** P4 = (int**)malloc(newTam * sizeof(int*));
    int** P5 = (int**)malloc(newTam * sizeof(int*));
    int** P6 = (int**)malloc(newTam * sizeof(int*));
    int** P7 = (int**)malloc(newTam * sizeof(int*));

    int** AResult = (int**)malloc(newTam * sizeof(int*));
    int** BResult = (int**)malloc(newTam * sizeof(int*));

    int i, j;

    for (i = 0; i < newTam; i++) {
        A11[i] = (int*)malloc(newTam * sizeof(int));
        A12[i] = (int*)malloc(newTam * sizeof(int));
        A21[i] = (int*)malloc(newTam * sizeof(int));
        A22[i] = (int*)malloc(newTam * sizeof(int));

        B11[i] = (int*)malloc(newTam * sizeof(int));
        B12[i] = (int*)malloc(newTam * sizeof(int));
        B21[i] = (int*)malloc(newTam * sizeof(int));
        B22[i] = (int*)malloc(newTam * sizeof(int));

        C11[i] = (int*)malloc(newTam * sizeof(int));
        C12[i] = (int*)malloc(newTam * sizeof(int));
        C21[i] = (int*)malloc(newTam * sizeof(int));
        C22[i] = (int*)malloc(newTam * sizeof(int));

        P1[i] = (int*)malloc(newTam * sizeof(int));
        P2[i] = (int*)malloc(newTam * sizeof(int));
        P3[i] = (int*)malloc(newTam * sizeof(int));
        P4[i] = (int*)malloc(newTam * sizeof(int));
        P5[i] = (int*)malloc(newTam * sizeof(int));
        P6[i] = (int*)malloc(newTam * sizeof(int));
        P7[i] = (int*)malloc(newTam * sizeof(int));

        AResult[i] = (int*)malloc(newTam * sizeof(int));
        BResult[i] = (int*)malloc(newTam * sizeof(int));
    }

    for (i = 0; i < newTam; i++) {
        for (j = 0 ; j < newTam; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newTam];
            A21[i][j] = A[i + newTam][j];
            A22[i][j] = A[i + newTam][j + newTam];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newTam];
            B21[i][j] = B[i + newTam][j];
            B22[i][j] = B[i + newTam][j + newTam];
        }
    }

    sum(A11, A22, AResult, newTam);
    sum(B11, B22, BResult, newTam);
    strassen(AResult, BResult, P1, newTam);

    sum(A21, A22, AResult, newTam);
    strassen(AResult, B11, P2, newTam);

    subtract(B12, B22, BResult, newTam);
    strassen(A11, BResult, P3, newTam);

    subtract(B21, B11, BResult, newTam);
    strassen(A22, BResult, P4, newTam);

    sum(A11, A12, AResult, newTam);
    strassen(AResult, B22, P5, newTam);

    subtract(A21, A11, AResult, newTam);
    sum(B11, B12, BResult, newTam);
    strassen(AResult, BResult, P6, newTam);

    subtract(A12, A22, AResult, newTam);
    sum(B21, B22, BResult, newTam);
    strassen(AResult, BResult, P7, newTam);

    sum(P3, P5, C12, newTam);
    sum(P2, P4, C21, newTam);

    sum(P1, P4, AResult, newTam);
    sum(AResult, P7, BResult, newTam);
    subtract(BResult, P5, C11, newTam);

    sum(P1, P3, AResult, newTam);
    sum(AResult, P6, BResult, newTam);
    subtract(BResult, P2, C22, newTam);

    for (i = 0; i < newTam ; i++) {
        for (j = 0 ; j < newTam ; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newTam] = C12[i][j];
            C[i + newTam][j] = C21[i][j];
            C[i + newTam][j + newTam] = C22[i][j];
        }
    }

    for (i = 0; i < newTam; i++) {
        free(A11[i]); free(A12[i]); free(A21[i]); free(A22[i]);
        free(B11[i]); free(B12[i]); free(B21[i]); free(B22[i]);
        free(C11[i]); free(C12[i]); free(C21[i]); free(C22[i]);
        free(P1[i]); free(P2[i]); free(P3[i]); free(P4[i]);
        free(P5[i]); free(P6[i]); free(P7[i]);
        free(AResult[i]); free(BResult[i]);
    }

    free(A11); free(A12); free(A21); free(A22);
    free(B11); free(B12); free(B21); free(B22);
    free(C11); free(C12); free(C21); free(C22);
    free(P1); free(P2); free(P3); free(P4);
    free(P5); free(P6); free(P7);
    free(AResult); free(BResult);
}


int main(){
    int n=16;
    int arr[16];
    int temp[16];
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
        temp[i]=arr[i];
    }
    int size=4;
    ll** mat1=malloc(size*sizeof(ll*));
    for(int i=0;i<size;i++){
        mat1[i]=calloc(size, sizeof(ll));
    }
    ll** mat2=malloc(size*sizeof(ll*));
    for(int i=0;i<size;i++){
        mat2[i]=calloc(size, sizeof(ll));
    }
    ll** ans;
    ll** ans2=malloc(size*sizeof(ll*));
    for(int i=0;i<size;i++){
        ans2[i]=calloc(size, sizeof(ll));
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            mat1[i][j]=arr[i*4+j];
            mat2[i][j]=mat1[i][j];
        }
    }
    ans=mmult(mat1,mat2,4);
    strassen(mat1,mat2,ans2,4);
    printmat(ans,4);
    printmat(ans2,4);
    

return 0;
}