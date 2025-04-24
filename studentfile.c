#include<stdio.h>
int main()
{  
char name[50] ;
int marks,i,n;
printf("enter num of student");
scanf("%d",&n);
FILE*fp
fp=fopen("student.txt","w");
if(fp==NULL)
{
printf("ERROR");
}
else
{
for (i=0;i<n;i++)
{
printf("%d",i+1);
printf("Name");
scanf("%s",name);
printf("marks");
scanf("%d",&marks);
fprintf(fp,"Name :%s marks %d",name,marks);
}
}
fclose(fp);
return 0;
