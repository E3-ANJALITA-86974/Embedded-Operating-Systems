#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define SIZE 10


struct array {
    int *arr;
    int size;
};


void* thread(void* para) {
    struct array *str_arr = (struct array*) para;  
    int *arr = str_arr->arr;
    int size = str_arr->size;
    int its, pos;

   
    for (its = 0; its < size - 1; its++) {
        for (pos = 0; pos < size - 1 - its; pos++) {
            if (arr[pos] > arr[pos + 1]) {
               
                int temp = arr[pos];
                arr[pos] = arr[pos + 1];
                arr[pos + 1] = temp;
            }
        }
    }

    return NULL;
}

int main() {
    pthread_t th;
    int ret;

    int arr[SIZE] = {99, 33, 44, 55, 77, 22, 66, 88, 11, 21};
    struct array arr_struct;
    arr_struct.arr = arr;
    arr_struct.size = SIZE;
    ret = pthread_create(&th, NULL, thread, (void*)&arr_struct);
    if (ret != 0) 
    {
        printf("Error creating thread\n");
        return 1;
    }
    pthread_join(th, NULL);
    printf("Sorted array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

