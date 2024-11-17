#include<stdio.h>
#include<unistd.h>

int main()
{
	int arr[2];
	char buff[1] = "A" ;
	int res,count=0 ;
	res = pipe(arr);
	if(res < 0)
	{
		perror("pipe failed");
		_exit(0);
	}
	while(1){
		write( arr[1] , buff , sizeof(buff));
		count++ ;
		printf("count : %d\n",count);
	}
	close(arr[1]);
	return 0 ;
}

