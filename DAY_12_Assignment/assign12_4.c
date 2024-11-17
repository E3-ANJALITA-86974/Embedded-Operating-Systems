#include<stdio.h>
#include<unistd.h>

int arr[2] ;
pipe(arr);
int cld1,cld2,s1,s2,err1,err2 ;
    cld1 = fork();
    if(cld1 == 0)
	{
	  close(arr[0]);
	  dup(arr[0]);
	  close(arr[1]);
	  err1 = execlp("who","who",NULL);
	  if(err1 < 0 ) 
	  {
	    perror("exec failed");
		_exit(0);
	  }
	  }
	  
	 cld2 = fork();
	 if(cld2 == 0)
	 {
	   close(arr[1]);
	   dup2(arr[0] ,0);
	   close(arr[1]);
	   err2 = execlp("wc","wc",NULL);
	   if(err2 < 0 )
	   {
	     perror("exec2 failed");
		 _exit(0);
	   }
	   }

    close(arr[0]);
	close(arr[1]);
	waitpid(cld1 , &s , 0);
	waitpid(cld2 , &s , 0);
 
return 0;
}
