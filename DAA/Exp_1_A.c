#include<stdio.h>
#include<math.h>
#include<stdlib.h>

long double fastpow(long double a, int b){//faster pow function when index is integer
    long double ans=1,power=a;
    while(b>0){
        if(b%2==1){
            ans*=power;
        }
        power*=power;
        b/=2;
    }
    return ans;
}


// all functions have long double return type and all attributes have long double data type
// to allow for use of array of function pointers
long double x(long double x){
    return x;
}

long double x3(long double x){
    return x*x*x;
}

long double lgx(long double x){
    return log2(x);
}

long double lnx(long double x){
    return log(x);
}

long double lg_sq_x(long double x){
    return lgx(x)*lgx(x);
}

long double ln_lnx(long double x){
    return lnx(lnx(x));
}

long double x_lgx(long double x){
    return x*lgx(x);
}

long double x_pow_1bylgx(long double x){
    return pow(x,pow(lgx(x),-1));
}

long double two_x(long double x){
    return fastpow(2,(int)x);
}

long double e_x(long double x){
    return fastpow(exp(1),(int)x);//using inbuilt function for accurate value of e
}

long double factorial(long double x){
    if(x==0){
        return 1;
    }
    long double ans=1;
    for(int i=x;i>1;i--){
        ans*=i;
    }
    return ans;
}

int main(){
    FILE* file=fopen("Exp_1_A.csv","w");//using csv formatting so file is easily opeened in excel
    if(file==NULL){//checking if fopen worked
        printf("Failed to open file\n");
    }
    
    //i stored all values in an array first so that they can be printed side by side into the file
    long double **arr=malloc(11*sizeof(long double *));//initializing 11 1D arrays to store data for the 10 functions+factorial
    for(int i=0;i<10;i++){
        arr[i]=malloc(101*sizeof(long double));
    }
    arr[10]=malloc(21*sizeof(long double));//array of size 20 for factorial
    long double (*fnptr_arr[])(long double)={x,x3,lgx,lnx,lg_sq_x,ln_lnx,x_lgx,x_pow_1bylgx,two_x,e_x,factorial};
    //using an array of function pointers so all functions can be called in a loop
    for(int i=0;i<10;i++){
        for(int n=0;n<=100;n++){
            arr[i][n]=fnptr_arr[i](n);
        }
    }
    for(int n=0;n<=20;n++){
        arr[10][n]=fnptr_arr[10](n);
    }

    //in the csv file format, contents of each cell are seperated by commas, empty cells are represented by consecutive
    //commas, and newlines by newline characters
    fprintf(file,"x,x,x^3,lg(x),ln(x),lg^2(x),ln(ln(x)),xlg(x),x^(1/lg(x)),2^x,e^x,x!\n");
    for(int i=0;i<=20;i++){
        fprintf(file,"%d,",i);
        for(int j=0;j<11;j++){
            fprintf(file,"%.5Lf,",arr[j][i]);
        }
        fprintf(file,"\n");
    }
    for(int i=21;i<=100;i++){
        fprintf(file,"%d,",i);
        for(int j=0;j<10;j++){
            fprintf(file,"%.5Lf,",arr[j][i]);
        }
        fprintf(file,"\n");
    }
    
    fclose(file);
    for(int i=0;i<11;i++){
        free(arr[i]);
    }
    free(arr);
    return 0;
}

