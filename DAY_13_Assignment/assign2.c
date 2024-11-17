#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int ret, arr1[2],arr2[2], s;
    int n1 = 36, n2 = 56, n3, n4, n5, n6;

    ret = pipe(arr1);
    if (ret < 0) {
        perror("pipe() failed");
        _exit(1);
    }

	ret = pipe(arr2);
	if (ret < 0) {
		perror("pipe( ) failed");
		_exit(1);
	}

    ret = fork();

    if (ret == 0) { 
        close(arr1[0]);
        write(arr1[1], &n1, sizeof(n1));
        write(arr1[1], &n2, sizeof(n2));
        printf("child: written to pipe: %d\n", n1);
        printf("child: written to pipe: %d\n", n2);
        close(arr1[1]);
        
        close(arr2[1]); 
        read(arr2[0], &n6, sizeof(n6));
        printf("child: read from pipe: %d\n", n6);
        close(arr2[0]);

    } else { 
        close(arr1[1]); 
        read(arr1[0], &n3, sizeof(n3));
        read(arr1[0], &n4, sizeof(n4));
        printf("parent: read from pipe: %d\n", n3);
        printf("parent: read from pipe: %d\n", n4);
        
        n5 = n3 + n4;
        close(arr2[0]);

        //ret = pipe(arr);  // Recreate the pipe for writing back to the child
        write(arr2[1], &n5, sizeof(n5));
        printf("parent: written to pipe: %d\n", n5);
        close(arr2[1]); 
        
        waitpid(ret, &s, 0);
    }

    return 0;
}
