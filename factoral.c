#include<stdio.h>
long long factorial(int n){
long long fact=1;
for (int i=1;i<=n;i++)
  fact*=i;
return fact;
}
int main(){
int n;
printf("enter a number")
scanf("%d",&n);
if(n<0)
  printf("factorial not possible");
else
  printf("factorial of %d is %lld\n",n,factorial(n));
return 0;
}
