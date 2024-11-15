#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void* sorting(void* param)
{
int pos,temp,sel_pos;
int* arr1 = (int*) param;
for(sel_pos=0;sel_pos<4;sel_pos++)
{
for(pos=sel_pos+1;pos<5;pos++)
{
if(arr1[sel_pos] > arr1[pos])
{
temp = arr1[sel_pos];
arr1[sel_pos]=arr1[pos];
arr1[pos]=temp;
}
}
}
printf("Thread : \n");
for(int i=0;i<5;i++)
{
printf("%d  ",arr1[i]);
}
printf("\n");
return NULL;
}
int main()
{
pthread_t th;
int arr[5] = {5,6,4,2,3};
pthread_create(&th,NULL,sorting,arr);
pthread_join(th,NULL);
printf("main : \n");
for(int i=0;i<5;i++)
{
printf(" %d  ",arr[i]);
}
return 0;
}
