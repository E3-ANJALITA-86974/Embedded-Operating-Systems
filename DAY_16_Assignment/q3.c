#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t m;
pthread_cond_t c;
int sun_flag = 0;

void*sunbeam(void *param)
{
   
   char *str = "SUNBEAM\n";
   while(1){
   pthread_mutex_lock(&m);
   while(sun_flag==1)
   {

    pthread_cond_wait(&c,&m);
   }
    for(int i=0; str[i]!='\0'; i++) {
        write(1, &str[i], 1);
      sleep(1);
    }
    sun_flag=1;
    pthread_cond_signal(&c); // wakeup infotech thread
    pthread_mutex_unlock(&m);
	}
    return NULL;
}
void* infotech(void *param) {
   char *str = "INFOTECH\n";
   while(1){
   pthread_mutex_lock(&m);
   while(sun_flag == 0)
   {
   pthread_cond_wait(&c, &m); // block infotech flag
    }
	for(int i=0; str[i]!='\0'; i++) {
        write(1, &str[i], 1);
       sleep(1);
    }
	sun_flag=0;
	pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
	}
    return NULL;
}

int main() {
    pthread_t st, it;
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&c, NULL);
    pthread_create(&it, NULL, infotech, NULL);
    pthread_create(&st, NULL, sunbeam, NULL);
    printf("press enter to exit...\n");
    getchar();
   pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);
    return 0;
}
