#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv){
    int n=atoi(argv[1]);
    int page_bits=12;
    int pno=n>>page_bits;
    int offset=n-(pno<<page_bits);
    printf("Page number : %d\nOffset : %d\n",pno,offset);

return 0;
}