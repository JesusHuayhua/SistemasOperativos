#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

#define N 8
#define BUFSIZE 64

int main(void) {
    pid_t pid_padre = getpid();
    pid_t pid_hijos[N]; // Para guardar los PIDs de los hijos
    pid_t pid = 0;
    int i;
    int pipe_fd[2];
    pipe(pipe_fd);// Creamos las tuberias

    // Creamos una cadena de procesos
    for (i = 0; i < N; ++i) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            if(i == 0){// Unicamente para el primer hijo
                close(pipe_fd[1]);
            }else{//Cerramos las tuberias para los demas hijos
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }
            // Estamos en el hijo
            break;
        } else {
            // Proceso padre guarda el PID del hijo
            pid_hijos[i] = pid;

            // Solo el padre original guarda todos los PIDs
            if (getpid() != pid_padre) {
                break;
            }
        }
    }
    // el padre le va a enviar los pids al primer hijo
    if(pid_padre == getpid()){
        close(pipe_fd[0]); // cerramos la lectura
        for(int ii = 0; ii < N ; ii++){
            char message[BUFSIZE];
            sprintf(message,"%d",pid_hijos[ii]);
            message[strlen(message)] = '\0';
            write(pipe_fd[1], message, sizeof(message) - 1);
        }
        close(pipe_fd[1]);//Dejamos de escribir

    }

    if (i == 0 && getppid() == pid_padre) {

        sleep(1); // Esperamos que todos los procesos se creen
        int ii;
        char buffer[BUFSIZE];
        while( ( ii = read(pipe_fd[0],buffer,BUFSIZE - 1)) != 0){
            pid_hijos[i] = atoi(buffer);
            i++;
            memset(buffer,0,sizeof(buffer));
        }
        close(pipe_fd[0]);
        /*Funcion de impresion para verificar que se recibieron correctamente los hijos*/
        /*
        for(int k = 0; k < N; k++){
            fprintf(stderr,"%d\n",pid_hijos[k]);
        }
        */

        // Matamos a los hermanos
        for (int j = 1; j < N; ++j) {
            kill(pid_hijos[j], SIGKILL);
        }

        // Matamos al padre
        kill(pid_padre, SIGKILL);

        printf("Primer hijo (%d): Eliminé a mis hermanos y al padre (%d)\n", getpid(), pid_padre);
        exit(0);
    }

    pause(); // Cada proceso se queda esperando (para ser eliminado o detenido)
    return 0;
}


