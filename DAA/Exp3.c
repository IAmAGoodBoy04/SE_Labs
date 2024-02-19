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


ll** addmatrix(ll** a,int ax,int ay,ll** b,int bx,int by,int size, int multiplier){
    ll** ret=malloc(size*sizeof(ll*));
    for(int i=0;i<size;i++){
        ret[i]=malloc(size*sizeof(ll));
    }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            ret[i][j]=a[ay+i][ax+j]+multiplier*b[by+i][bx+j];
        }
    }
    return ret;
}

ll** mmultstrassen(ll** a,int ax, int ay, ll**b,int bx, int by, int size){
    if(size==1){
        ll** ret=malloc(size*sizeof(ll*));
        for(int i=0;i<size;i++){
            ret[i]=malloc(size*sizeof(ll));
        }
        ret[0][0]=a[ay][ax]*b[by][bx];
        return ret;
    }
    if(size==2){
        ll** ret=malloc(size*sizeof(ll*));
        for(int i=0;i<size;i++){
            ret[i]=malloc(size*sizeof(ll));
        }
        ll p,q,r,s,t,u,v;
        p=(a[ay][ax]+a[ay+1][ax+1])*(b[by][bx]+b[by+1][bx+1]);
        q=(a[ay+1][ax]+a[ay+1][ax+1])*b[by][bx];
        r=a[ay][ax]*(b[by][bx+1]-b[by+1][bx+1]);
        s=a[ay+1][ax+1]*(b[by+1][bx]-b[by][bx]);
        t=(a[ay][ax]+a[ay][ax+1])*b[by+1][bx+1];
        u=(a[ay+1][ax]-a[ay][ax])*(b[by][bx]+b[by][bx+1]);
        v=(a[ay][ax+1]-a[ay+1][ax+1])*(b[by+1][bx]+b[by+1][bx+1]);
        ret[0][0]=p+s-t+v;
        ret[0][1]=r+t;
        ret[1][0]=q+s;
        ret[1][1]=p-q+r+u;
        return ret;
    }
    ll** ret=malloc(size*sizeof(ll*));
    for(int i=0;i<size;i++){
        ret[i]=malloc(size*sizeof(ll));
    }
    int mid=size/2;
    ll **c,**d,**e,**f,**g,**h,**im,**j,**k,**l;
    c=addmatrix(a,ax,ay,a,ax+mid,ay+mid,size/2,1);
    d=addmatrix(b,bx,by,b,bx+mid,by+mid,size/2,1);
    ll** p=mmultstrassen(c,0,0,d,0,0,size/2);
    e=addmatrix(a,ax,ay+mid,a,ax+mid,ay+mid,size/2,1);
    ll** q=mmultstrassen(e,0,0,b,bx,by,size/2);
    f=addmatrix(b,bx+mid,by,b,bx+mid,by+mid,size/2,-1);
    ll** r=mmultstrassen(a,ax,ay,f,0,0,size/2);
    g=addmatrix(b,bx,by+mid,b,bx,by,size/2,-1);
    ll** s=mmultstrassen(a,ax+mid,ay+mid,g,0,0,size/2);
    h=addmatrix(a,ax,ay,a,ax+mid,ay,size/2,1);
    ll** t=mmultstrassen(h,0,0,b,bx+mid,by+mid,size/2);
    im=addmatrix(a,ax,ay+mid,a,ax,ay,size/2,-1);
    j=addmatrix(b,bx,by,b,bx+mid,by,size/2,1);
    ll** u=mmultstrassen(im,0,0,j,0,0,size/2);
    k=addmatrix(a,ax+mid,ay,a,ax+mid,ay+mid,size/2,-1);
    l=addmatrix(b,bx,by+mid,b,bx+mid,by+mid,size/2,1);
    ll** v=mmultstrassen(k,0,0,l,0,0,size/2);
    ll** c11,**c12,**c21,**c22;
    c11=addmatrix(p,0,0,s,0,0,size/2,1);
    c11=addmatrix(c11,0,0,t,0,0,size/2,-1);
    c11=addmatrix(c11,0,0,v,0,0,size/2,1);
    c12=addmatrix(r,0,0,t,0,0,size/2,1);
    c21=addmatrix(q,0,0,s,0,0,size/2,1);
    c22=addmatrix(p,0,0,r,0,0,size/2,1);
    c22=addmatrix(c22,0,0,q,0,0,size/2,-1);
    c22=addmatrix(c22,0,0,u,0,0,size/2,1);
    for(int i=0;i<mid;i++){
        for(int j=0;j<mid;j++){
            ret[i][j]=c11[i][j];
        }
    }
    for(int i=mid;i<size;i++){
        for(int j=0;j<mid;j++){
            ret[i][j]=c21[i-mid][j];
        }
    }
    for(int i=0;i<mid;i++){
        for(int j=mid;j<size;j++){
            ret[i][j]=c12[i][j-mid];
        }
    }
    for(int i=mid;i<size;i++){
        for(int j=mid;j<size;j++){
            ret[i][j]=c22[i-mid][j-mid];
        }
    }
    for(int i=0;i<size/2;i++){
        free(c[i]);
        free(d[i]);
        free(e[i]);
        free(f[i]);
        free(g[i]);
        free(h[i]);
        free(im[i]);
        free(j[i]);
        free(k[i]);
        free(l[i]);
        free(p[i]);
        free(q[i]);
        free(r[i]);
        free(s[i]);
        free(t[i]);
        free(u[i]);
        free(v[i]);
        free(c11[i]);
        free(c12[i]);
        free(c21[i]);
        free(c22[i]);
    }
    free(c);
    free(d);
    free(e);
    free(f);
    free(g);
    free(h);
    free(im);
    free(j);
    free(k);
    free(l);
    free(p);
    free(q);
    free(r);
    free(s);
    free(t);
    free(u);
    free(v);
    free(c11);
    free(c12);
    free(c21);
    free(c22);
    return ret;
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
    ll** temp;
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
    temp=mmultstrassen(arr1,0,0,arr2,0,0,size);
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
    file=fopen("Exp_3_timings.csv","w");
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
