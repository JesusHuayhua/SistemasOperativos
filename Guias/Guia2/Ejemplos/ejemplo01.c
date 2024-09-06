#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
    pid_t child;
    if ((child = fork())){
        fprintf(stderr,"\nFork() devolvio  %d por tanto soy el padre con ID = %d",child, getpid());
    }else{
        fprintf(stderr,"\nFork() devolvio  %d por tanto soy el hijo con ID = %d\n",child, getpid());
        system("pstree > aprocess.txt");
    }
    return 0;
}