clc;
A=[1 2 6;3 4 1;6 -1 -1];
B=[22;26;19];
disp(A);
disp(B);
C=[A B];
n=3;
for i=1:n
    if C(i,i)~=0
        C(i,:)=C(i,:)/C(i,i);
    end
    disp(C);
    for j=i+1:n
        C(j,:)=C(j,:)-C(j,i)*C(i,:); 
    end
    disp(C);
end

for i=n:-1:2
    for j=1:i-1
        C(j,:)=C(j,:)-C(i,:)*C(j,i); 
    end
end
disp(C);
