#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define N 8

int main(void) {
    pid_t pid_padre = getpid();
    pid_t pid_hijos[N]; // Para guardar los PIDs de los hijos
    pid_t pid = 0;
    int i;

    // Creamos una cadena de procesos
    for (i = 0; i < N; ++i) {
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
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

    // Primer hijo (creado directamente por el padre)
    if (i == 0 && getppid() == pid_padre) {
        sleep(1); // Esperamos que todos los procesos se creen

        // Matamos a los hermanos
        for (int j = 1; j < N; ++j) {
            kill(pid_hijos[j], SIGKILL);
        }

        // Matamos al padre
        kill(pid_padre, SIGKILL);

        printf("Primer hijo (%d): Eliminé a mis hermanos y al padre (%d)\n", getpid(), pid_padre);
    }

    pause(); // Cada proceso se queda esperando (para ser eliminado o detenido)
    return 0;
}


