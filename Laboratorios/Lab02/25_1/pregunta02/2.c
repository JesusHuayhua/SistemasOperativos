#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/signal.h>

#include <string.h>
/* Este programa crea un abanico de procsos.                       */
/* Ejm 2.6 del libro UNIX Programacion Practica - Kay Robbins      */
/*                                                Steve Robbins    */

#define BUFSIZE 64
int hijo_del_medio;
pid_t pid_hijo_del_medio;
int main(int narg, char *argv[]) {
   int i, status, n;
   pid_t child, pid_padre;

   if (narg != 2) {
      printf("Usage: %s <n>\n", argv[0]);
      exit(1);
   }
   n = atoi(argv[1]);
   if (!(n % 2))
      n++;
   hijo_del_medio = (n/2) + 1;
   //printf("%d\n", hijo_del_medio);
   pid_padre = getpid();
   pid_t pid_hijos[n];// para almacenar el valor de todos los hijos.
   //Tuberia
   int pipe_fd[2];
   pipe(pipe_fd);
   // Crea el abanico de N hijos
   for (i = 0; i < n; ++i)
      if ((child = fork()) <= 0){
         // Almacenamos el pid del hijo del medio.
         if(i + 1 == hijo_del_medio){
            pid_hijo_del_medio = getpid();
            close(pipe_fd[1]);// Cerramos la de escritura
         }else{ // para todo los hijos, cerramos la tuberia
            close(pipe_fd[0]);
            close(pipe_fd[1]);
         }
         break;
      }else
         pid_hijos[i] = child;
   
   if(getpid() == pid_padre){// El padre le va a pasar la lista de pids al hijo del medio
      close(pipe_fd[0]);//cerramos la tuberia de lectura
      char message[BUFSIZE];
      for(int i = 0; i < n; i++){
         sprintf(message,"%d",pid_hijos[i]);
         message[strlen(message)- 1] = '\0';
         write(pipe_fd[1], message, sizeof(message) - 1);
         //fprintf(stderr,"Hijo %d: %d\n", i,pid_hijos[i]);
      }
   }else if(getpid() == pid_hijo_del_medio){// El hijo del medio, va a recibir los pids de todos.
      int ii,k = 0;
      char buffer[BUFSIZE];
      while( (ii = read(pipe_fd[0],buffer, BUFSIZE - 1)) != 0){
         pid_hijos[k] = atoi(buffer);
         memset(buffer,0,sizeof(buffer));
         k++;
      }
      close(pipe_fd[0]);
   }
   if (pid_padre == getpid()){
      for (i = 0; i < n-1; ++i){
         char pstree[BUFSIZE];
         sprintf(pstree, "pstree -p %d", getpid());
         system(pstree);
         wait(&status);
      }
      close(pipe_fd[1]);
      sleep(1);//espera a que el hijo lo mate xD
   }else if(pid_hijo_del_medio == getpid()){
      char pstree[BUFSIZE];
      sprintf(pstree, "pstree -p %d", getpid());
      system(pstree);
      for(int l = 0; l < n; l++){
         if(l + 1 == hijo_del_medio) continue;
         kill(pid_hijos[l],SIGKILL);
      }
      kill(getppid(), SIGKILL); // eliminado al padre
      close(pipe_fd[0]);
      exit(1);
   }
   return 0;
}
