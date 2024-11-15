#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

struct array
{ int *arr;
int size; };

void* bubble_sort(void* param)
{
struct array *arr = (struct arr*)param;

int its,pos;

    for(its = 0;its < SIZE-1; its++)
 {
        
        for(pos=0;pos < SIZE-1-its;pos++)
        {
           
            if(arr[pos] > arr[pos+1])
            {
                
                temp = arr[pos];
				arr[pos]=arr[pos+1];
				arr[pos+1]=temp;
}
}
}
for(int i=0;i<=3;i++)
{
printf("%
d ",arr[i]);
return NULL;
}

int main()
{
struct array Arr = arr->:
pthread_t th;
pcreate(&th,NULL,bubble_sort,&Arr);

return 0;
}
