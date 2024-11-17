#include<stdio.h>
#include<unistd.h>
#include <fcntl.h>

int main()
{
	int ret,arr[2],cnt=0,fd;
	ret = pipe(arr);
	if(ret < 0)
	{
		perror("pipe failed :");
	}
	char buff[] = "A";
//	close(arr[0]);
	while(1)
	{
		cnt++;
		write(arr[1],buff, 1);
		printf("count buffer %d\n",cnt);
	}
	close(arr[1]);
	return 0;
}
