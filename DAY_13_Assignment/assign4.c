#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main()
{
	int arr[2],s1,s2;
	int ret = pipe(arr);

	if(ret < 0)
	{
		perror("pipe() failed :");
		_exit(1);
	}

	int pid1 = fork();

	if(pid1 < 0)
	{
		perror("FORK() failed :");
		_exit(1);
	}

	if(pid1 == 0)
	{
		//writer process.../
		close(arr[0]);
		dup2(arr[1], 1);
		close(arr[1]);

		int err1 = execlp("who","who",NULL);
		if(err1<0)
		{
			perror("Execpl() failed : ");
			_exit(1);
		}
	}

	int pid2 = fork();
	if(pid2 < 0)
	{
		perror("fork() failed :");
		_exit(1);
	}

	if(pid2 == 0)
	{
		//reader process...../
		close(arr[1]);
		dup2(arr[0], 0);
		close(arr[0]);

		int err2 = execlp("wc","wc",NULL);
		if(err2 < 0)
		{
			perror("Execpl() failed");
			_exit(1);
		}
	}
	
	close(arr[1]);
	close(arr[0]);
	
	waitpid(pid1, &s1, 0);
	waitpid(pid2, &s2, 0);

	return 0;
}

