#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(){
    printf("I'm the parent PID: %d\n",getpid());
    int n, status, f1, f2, rando, file;

    f1 = fork(); //fork() returns 0 (false) if it's the child
    if (f1){
        f2 = fork();
    }

    if (!f1){
        printf("I'm child 1 PID: %d\n",getpid());
        file = open("/dev/random", O_RDONLY);
        read(file, &rando, sizeof(rando));
        close(file);
        n = (abs(rando) % 9) + 2;
        sleep(n);
        printf("Child 1 finished sleeping.\n");
        return n;
    }
    else{
        if (!f2){
        printf("I'm child 2 PID: %d\n",getpid());
        file = open("/dev/random", O_RDONLY);
        read(file, &rando, sizeof(rando));
        close(file);
        n = (abs(rando) % 9) + 2;
        sleep(n);
        printf("Child 2 finished sleeping\n");
        return n;
        }
        else{
            int childx = wait(&status);
            printf("Child PID: %d slept for %d seconds\n",childx, WEXITSTATUS(status));
            int childy = wait(&status);
            printf("Child PID: %d slept for %d seconds\n",childy, WEXITSTATUS(status));
        }
    }

}