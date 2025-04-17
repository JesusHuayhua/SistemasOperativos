#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 8

int main(int argc, char const *argv[]){
    int i, status;
    pid_t child, pid_padre;
    pid_padre = getpid();
    for(i = 0; i < N; ++i){
        if(!(child = fork()) <= 0) break;
    }    

    if(pid_padre == getpid()) for(i = 0; i < N; ++i) wait(&status);
    return 0;
}
