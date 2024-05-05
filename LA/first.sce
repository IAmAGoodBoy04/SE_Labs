clc;
A= [2 3 4 -2;2 3 -3 -1;7 9 -4 7;102 -1 70 301];
B= [11;1;21;72];
printf("The matrix A is:");
disp(A);
printf("The matrix B is:");
disp(B);
C=[A B];
printf("The matrix C is:");
disp(C);
n=4;
for i=1:n
    if C(i,i)==0
        C(i,:)=C(i,:)+C(i+1,:);
    end
    if C(i,i)~=0
        C(i,:)=C(i,:)/C(i,i);
    end
    disp(C);
    for j=i+1:n
        C(j,:)=C(j,:)-C(i,:)*C(j,i);
    end
    disp(C);
end
for i=n:-1:2
    for j=1:i-1
        C(j,:)=C(j,:)-C(i,:)*C(j,i);
    end
    disp(C);
end
printf("x=%g\n",C(1,5));
printf("y=%g\n",C(2,5));
printf("z=%g\n",C(3,5));
printf("w=%g\n",C(4,5));
