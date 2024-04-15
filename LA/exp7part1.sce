clc;
clear all;
A=[2 -1 1;1 2 -1;1 -1 2];
[c,d]=spec(A);
printf("The Eigen-values of matrlx A are:\n");
disp(spec(A)) ;
printf("\nThe corresponding Eigen-vectors of matrix A is:\n");
disp(c);
