#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

int main()
{
  int arr1[2];
  int arr2[2];
  int res , ret ,s ;
  int buff[3],buff1[1],buff2[2];

  ret = pipe(arr1);
  ret = pipe(arr2);
  if(ret < 0)
  {
    perror("pipe failed");
	_exit(0);
	}
  
  res = fork();
  if(res == 0)
  {
    buff[2] ;
	printf("enter two numbers");
	scanf("%d",&buff[0]);
	scanf("%d",&buff[1]);
	write(arr1[1] ,buff, sizeof(buff));
	printf("numbers entered is : %d %d\n",buff[0],buff[1]);
    
    read(arr2[0] , buff , sizeof(buff));
	printf("child received : addition of number is : %d\n",buff[1]);
	close(arr2[0]);
	close(arr1[1]);
	}
  else 
  {
	read(arr1[0] , buff , sizeof(buff));
	int addition = buff[0] + buff[1] ;
    buff2[1] = buff[0] + buff[1];
	write(arr2[1] , buff2 , sizeof(buff2));
	printf("parent sending : additon of two numbers is %d \n",buff2[1]);

	close(arr1[0]);
	close(arr2[1]);
	waitpid(res , &s,0);
	}
  return 0 ;
  }
    



  
