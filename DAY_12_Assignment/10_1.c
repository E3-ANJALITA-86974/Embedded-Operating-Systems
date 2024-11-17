#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define  MSG_KEY  0x2415

typedef struct msg {
    long id ;
	int data[2];
	}msg_t ;

int main()
{ 
   printf("program starts\n");
   msg_t m1 ;
   int msg_id,s;
   msg_id = msgget(MSG_KEY , IPC_CREAT |0644);
   if(msg_id < 0 )
   {
     perror("msgget failed\n");
	 _exit(0);
	 }
	else 
	{
	  printf("msg queue created \n ");
	  }
   int ret,res,num1, num2,pr ;
   res = fork();
   if( res == 0)
   { 
      m1.id = 100 ;
	  printf("enter num1  : ");
	  scanf("%d",&m1.data[0]);
	  printf("enter num2 : ");
	  scanf("%d",&m1.data[1]);
      ret = msgsnd(msg_id , &m1 , sizeof(msg_t) - sizeof(long) , 0);
	  if(ret < 0 )
	  {
	    perror("msg send failed ");
		_exit(0);
		}
	  else 
	    {
		  printf("msg send succesfull\n");
		  }

       msg_t m4 ;
	   res = msgrcv(msg_id , &m4 , sizeof(msg_t) - sizeof(long) ,m1.id , 0);
	   if(res < 0)
	   {
	     perror("msg rcv failed");
		 _exit(0);
		} 
	else 
     	{
		  printf("msg received of addition which is %d\n",m4.data[0]);
		  }

	   sleep(1);
	   _exit(0);
	   }
     
	 msg_t m2 ;
	 ret = msgrcv( msg_id , &m2 , sizeof(msg_t) - sizeof(long) ,m1.id , 0);
	 if(ret < 0)
	 {
	   perror("msg not received");
	   _exit(0);
	   }
	  else 
	  {
	    printf("msg received succesfully \n");
		}
     
	  msg_t m3 ;
	  m3.id = 100 ;
	  m3.data[0] = m2.data[0] + m2.data[1];
	  m3.data[1] = 0 ;
	  pr = msgsnd(msg_id , &m3 ,sizeof(msg_t) - sizeof(long) , 0);
	  if(pr < 0 )
	  {
	    perror("msg send to cld failed ");
		_exit(0);
		}
	  else 
	  {
	    printf("msg sending to child\n ");
		printf("addtion of two numbers is : %d\n",m3.data[0]);
		}
    
	waitpid(res , &s , 0);
	printf("parent process end:\n");
	return 0;
	}
	 
	 
   



