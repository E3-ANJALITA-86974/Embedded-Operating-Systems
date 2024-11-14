#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct input {
    int min;
    int max;
};
struct output {
    int sum;
};

void* divide(void *param) {
    struct input *ip = (struct input *)param;
    struct output *op = (struct output *)malloc(sizeof(struct output));
    for(int i = ip->min;i <= ip->max;i++)
	{
      op->sum = op->sum+i;
      printf("%d  +  %d  = %d \n", op->sum , i,op->sum+i);
	}
    printf("thread : sum =%d\n", op->sum);
    return op;
}

int main() {
    pthread_t th;
    struct input in = { .min = 5, .max =10 };
    struct output *out;
    pthread_create(&th, NULL, divide, &in);
    pthread_join(th, (void**)&out);
   
        printf("main: sum=%d\n", out->sum);
    free(out);
    return 0;
}