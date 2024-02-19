#include<stdio.h>
#include<stdlib.h>
#define inf 0x7fffffff
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
    ll** ans2;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            mat1[i][j]=arr[i*4+j];
            mat2[i][j]=mat1[i][j];
        }
    }
    ans=mmult(mat1,mat2,4);
    ans2=mmultstrassen(mat1,0,0,mat2,0,0,4);
    printmat(ans,4);
    printmat(ans2,4);
    

return 0;
}