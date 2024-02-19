#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#define inf 0x7fffffff
#define ll long long

#define SIZE 100000
FILE* file;

typedef struct minmax{
    int min;
    int max;
}minmax;



minmax minmaxnormal(int* arr, int size){
    minmax retval;
    retval.max=INT_MIN;
    retval.min=inf;
    for(int i=0;i<size;i++){
        if(arr[i]>retval.max){
            retval.max=arr[i];
        }
        if(arr[i]<retval.min){
            retval.min=arr[i];
        }
    }
    return retval;
}

minmax minmaxdc(int *arr,int start, int end){
    minmax retval;
    if(start==end){
        retval.min=retval.max=arr[start];
        return retval;
    }
    if(end-start==1){
        retval.min=arr[start]<arr[end]?arr[start]:arr[end];
        retval.max=arr[start]>arr[end]?arr[start]:arr[end];
        return retval;
    }
    minmax left,right;
    int mid=(start+end)/2;
    left=minmaxdc(arr,start,mid);
    right=minmaxdc(arr,mid+1,end);
    retval.min=left.min<right.min?left.min:right.min;
    retval.max=left.max>right.max?left.max:right.max;
    return retval;
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



void sum(ll** A, ll** B, ll** C, ll tam) {
    ll i, j;

    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract(ll** A, ll** B, ll** C, ll tam) {
    ll i, j;

    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen(ll** A, ll** B, ll** C, ll tam) {
    if (tam == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    ll newTam = tam/2;
    ll** A11 = (ll**)malloc(newTam * sizeof(ll*));
    ll** A12 = (ll**)malloc(newTam * sizeof(ll*));
    ll** A21 = (ll**)malloc(newTam * sizeof(ll*));
    ll** A22 = (ll**)malloc(newTam * sizeof(ll*));

    ll** B11 = (ll**)malloc(newTam * sizeof(ll*));
    ll** B12 = (ll**)malloc(newTam * sizeof(ll*));
    ll** B21 = (ll**)malloc(newTam * sizeof(ll*));
    ll** B22 = (ll**)malloc(newTam * sizeof(ll*));

    ll** C11 = (ll**)malloc(newTam * sizeof(ll*));
    ll** C12 = (ll**)malloc(newTam * sizeof(ll*));
    ll** C21 = (ll**)malloc(newTam * sizeof(ll*));
    ll** C22 = (ll**)malloc(newTam * sizeof(ll*));

    ll** P1 = (ll**)malloc(newTam * sizeof(ll*));
    ll** P2 = (ll**)malloc(newTam * sizeof(ll*));
    ll** P3 = (ll**)malloc(newTam * sizeof(ll*));
    ll** P4 = (ll**)malloc(newTam * sizeof(ll*));
    ll** P5 = (ll**)malloc(newTam * sizeof(ll*));
    ll** P6 = (ll**)malloc(newTam * sizeof(ll*));
    ll** P7 = (ll**)malloc(newTam * sizeof(ll*));

    ll** AResult = (ll**)malloc(newTam * sizeof(ll*));
    ll** BResult = (ll**)malloc(newTam * sizeof(ll*));

    ll i, j;

    for (i = 0; i < newTam; i++) {
        A11[i] = (ll*)malloc(newTam * sizeof(ll));
        A12[i] = (ll*)malloc(newTam * sizeof(ll));
        A21[i] = (ll*)malloc(newTam * sizeof(ll));
        A22[i] = (ll*)malloc(newTam * sizeof(ll));

        B11[i] = (ll*)malloc(newTam * sizeof(ll));
        B12[i] = (ll*)malloc(newTam * sizeof(ll));
        B21[i] = (ll*)malloc(newTam * sizeof(ll));
        B22[i] = (ll*)malloc(newTam * sizeof(ll));

        C11[i] = (ll*)malloc(newTam * sizeof(ll));
        C12[i] = (ll*)malloc(newTam * sizeof(ll));
        C21[i] = (ll*)malloc(newTam * sizeof(ll));
        C22[i] = (ll*)malloc(newTam * sizeof(ll));

        P1[i] = (ll*)malloc(newTam * sizeof(ll));
        P2[i] = (ll*)malloc(newTam * sizeof(ll));
        P3[i] = (ll*)malloc(newTam * sizeof(ll));
        P4[i] = (ll*)malloc(newTam * sizeof(ll));
        P5[i] = (ll*)malloc(newTam * sizeof(ll));
        P6[i] = (ll*)malloc(newTam * sizeof(ll));
        P7[i] = (ll*)malloc(newTam * sizeof(ll));

        AResult[i] = (ll*)malloc(newTam * sizeof(ll));
        BResult[i] = (ll*)malloc(newTam * sizeof(ll));
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




void runminmaxnormal(int *arr, int len){
    minmax pair;
    clock_t time=clock();
    pair=minmaxnormal(arr,len);
    time=clock()-time;
    double tme=(double)time/CLOCKS_PER_SEC;
    fprintf(file,"%lf,",tme);
}

void runminmaxdc(int *arr, int len){
    minmax pair;
    clock_t time=clock();
    pair=minmaxdc(arr,0,len-1);
    time=clock()-time;
    double tme=(double)time/CLOCKS_PER_SEC;
    fprintf(file,"%lf,",tme);
}

void runmmult(int* arr, int len){
    ll **temp;
    int size=len;
    ll** arr1=malloc(size*sizeof(ll*));
    for(int i=0;i<size;i++){
        arr1[i]=calloc(size, sizeof(ll));
    }
    ll** arr2=malloc(size*sizeof(ll*));
    for(int i=0;i<size;i++){
        arr2[i]=calloc(size, sizeof(ll));
    }
    int ind=0,offset=len*len;
    for(int i=0;i<len;i++){
        for(int j=0;j<len;j++){
            arr1[i][j]=arr[ind];
            arr2[i][j]=arr[ind+offset];
            ind++;
        }
    }
    clock_t time=clock();
    temp=mmult(arr1,arr2,len);
    time=clock()-time;
    double tme=(double)time/CLOCKS_PER_SEC;
    fprintf(file,"%lf,",tme);
    for(int i=0;i<len;i++){
        free(temp[i]);
    }
    free(temp);
}

void runmmultstrassen(int* arr, int len){
    int size=1;
    while(size<len){
        size*=2;
    }
    ll** temp=malloc(size*sizeof(ll*));
    for(int i=0;i<size;i++){
        temp[i]=calloc(size, sizeof(ll));
    }
    ll** arr1=malloc(size*sizeof(ll*));
    for(int i=0;i<size;i++){
        arr1[i]=calloc(size, sizeof(ll));
    }
    ll** arr2=malloc(size*sizeof(ll*));
    for(int i=0;i<size;i++){
        arr2[i]=calloc(size, sizeof(ll));
    }
    int ind=0,offset=len*len;
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(i<len && j<len){
                arr1[i][j]=arr[ind];
                arr2[i][j]=arr[ind+offset];
                ind++;
            }
            else{
                arr1[i][j]=0;
                arr2[i][j]=0;
            }
        }
    }
    clock_t time=clock();
    strassen(arr1,arr2,temp,size);
    time=clock()-time;
    double tme=(double)time/CLOCKS_PER_SEC;
    fprintf(file,"%lf,",tme);
    for(int i=0;i<size;i++){
        free(temp[i]);
    }
    free(temp);
}


int main(){
    srand(time(NULL));
    file=fopen("input.txt","w");
    for(int i=0;i<SIZE;i++){
        fprintf(file,"%d ",rand());
    }
    fclose(file);
    file=fopen("input.txt","r");
    int arr[SIZE];
    for(int i=0;i<SIZE;i++){
        fscanf(file,"%d ",&arr[i]);
        arr[i]%=0xfffff;//to ensure that result of matrix multiplication firs in long long
    }
    fclose(file);
    int best_case[SIZE];
    int worst_case[SIZE];
    for(int i=0;i<SIZE;i++){
        best_case[i]=i+1;
        worst_case[SIZE-i-1]=i+1;
    }
    file=fopen("Exp_3_timings_optimised.csv","w");
    fprintf(file,"min-max(normal) best case,min-max(normal) average case, min-max(normal) worst case,min-max(D&C) best case,min-max(D&C) average case,min-max(D&C) worst case,matrix-mult(normal) best case, matrix-mult(normal) average case, matrix-mult(normal) worst case,matrix-mult(strassen) best case,matrix-mult(strassen) average case,matrix-mult(strassen) worst case\n");
    for(int i=1;i<=128;i++){
        runminmaxnormal(best_case,i*100);
        runminmaxnormal(arr,i*100);
        runminmaxnormal(worst_case,i*100);
        runminmaxdc(best_case,i*100);
        runminmaxdc(arr,i*100);
        runminmaxdc(worst_case,i*100);
        runmmult(best_case,i);
        runmmult(arr,i);
        runmmult(worst_case,i);
        runmmultstrassen(best_case,i);
        runmmultstrassen(arr,i);
        runmmultstrassen(worst_case,i);
        fprintf(file,"\n");
    }
    for(int i=129;i<=1000;i++){
        runminmaxnormal(best_case,i*100);
        runminmaxnormal(arr,i*100);
        runminmaxnormal(worst_case,i*100);
        runminmaxdc(best_case,i*100);
        runminmaxdc(arr,i*100);
        runminmaxdc(worst_case,i*100);
        fprintf(file,"\n");
    }
    fclose(file);

    return 0;
}
