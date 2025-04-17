#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>

int n;
pid_t padre;
void crea_arbol(int nivel);
int main(int narg, char *argv[]){
    if (narg != 2) {
        fprintf(stderr, "Uso: %s <niveles>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    n = atoi(argv[1]);
    padre = getpid();
    crea_arbol(0);//empezamos en el nivel 0
    if(getpid() == padre){
        char cadena[60];
        sprintf(cadena,"pstree -p %d > ntree.txt", getpid());
        system(cadena);
        for(int i = 0; i <n;i++)wait(NULL);
    }
    return 0;
}

void crea_arbol(int nivel){
    pid_t child;
    if(nivel >= n){// Llegamos al maximo de niveles
        sleep(10); // Lo mandamos a dormir,para poder usar pstree
        return;
    }
    for(int i = 0; i < n; ++i){//crea n hijos
       if((child = fork()) <= 0) {// el hijo crea 1 nivel extra
        crea_arbol(nivel + 1);
        exit(0);
    }
    }
    if(getpid() != padre){
        for(int i = 0; i <n;i++)wait(NULL);
    }
}