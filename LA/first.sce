clc
A=[1 1 1;1 2 4;1 4 10];
printf("Original matrix is:");
disp(A);
n=3;
for i=1:n
    if A(i,i)~=0
        A(i,:)=A(i,:)/A(i,i);
    end
    disp(A);
    for j=i+1:n
        A(j,:)=A(j,:)-A(j,i)*A(i,:)
    end
    if A(1,2)== A(2,2)
    A(1,:)=A(1,:)-A(2,:)
    else
    end
    disp(A)
end
