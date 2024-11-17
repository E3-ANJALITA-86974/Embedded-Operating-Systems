#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#define SIZE 10
void*thread_fun(void*para)
{ 
  int*arr=(int*)para;
   int its,pos;
       
    for(its = 0;its < SIZE-1; its++)

    {
      
        for(pos=0;pos < SIZE-1-its;pos++)
        {
            
            if(arr[pos] > arr[pos+1])
            
			{
			 int temp=arr[pos];
			 arr[pos]=arr[pos+1];
			 arr[pos+1]=temp;
		

            }
        }
    }
return arr;
}

int main()
{
 
 pthread_t th;
 int ret;
 int arr[10]={45,22,66,88,44,33,21,11,99,66};
 
 
 ret=pthread_create(&th,NULL,thread_fun,arr);
 pthread_join(th,NULL);
 
 for(int i=0;i<=SIZE; i++){
 printf("sorted array:%d\n",arr[i]);
}
return 0;
}


