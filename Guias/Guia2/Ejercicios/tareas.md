# Tareas de SO (Lab 2: Procesos, Parte A)
## Conceptos importantes: ¿Como funciona fork() y como importa para la creacion del arbol de procesos?

## Tarea 1

### Pregunta a)

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
  pid_t child, parent;
  int status = 0;
  if ((child = fork())){
    fprintf(stderr,"[PARENT] child process = %d\nparent process=%d\n", child, getpid());
  }else{
    fprintf(stderr, "[CHILD] child process=%d\nchild PID=%d\n",child, getpid());
    system("pstree > procesos.txt");
  }  
  while ((parent = wait(&status)) > 0); 
  return 0;
}
```
### Pregunta b)
La respuesta es que sh es el proceso de shell, y debido a que estamos ejecutando system(), este se crea pasandole 
el command line de ```pstree > procesos.txt```

### Pregunta c)
```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
  pid_t child, parent;
  int status = 0;
  if ((child = fork())){
    fprintf(stderr,"[PARENT] child process = %d\nparent process=%d\n", child, getpid());
  }else{
    parent = getppid();
    char commandline[260];
    sprintf(commandline, "pstree -p %d > procesos.txt", parent);
    fprintf(stderr, "[CHILD] child process=%d\nchild PID=%d\n",child, getpid());
    system(commandline);
  }  
  while ((parent = wait(&status)) > 0); 
  return 0;
}
```


### Pregunta d)

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    pid_t child, parent;
    int status = 0;
    char current_directory[260];
    char commandline[520]; 
    if (getcwd(current_directory, sizeof(current_directory)) == NULL) {
        perror("getcwd() error");
        return 1;
    }
    if ((child = fork())) {
        fprintf(stderr, "[PARENT] child process = %d\nparent process = %d\n", child, getpid());
    } else {
        parent = getppid();
        snprintf(commandline, sizeof(commandline), "pstree -p %d > %s/procesos.txt", parent, current_directory);
        fprintf(stderr, "[CHILD] child process = %d\nchild PID = %d\n", child, getpid());
        if (system(commandline) == -1) {
            perror("system() error");
            exit(EXIT_FAILURE);
        }
    }
    while ((parent = wait(&status)) > 0);
    return 0;
}
```

## Tarea 2

### Pregunta a)

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
  int i, status;
  pid_t child, parent;
  char command_line[256];
  parent = getpid();
  for (int i = 0; i < 4; i++){
    if ((child = fork())){
      break;
    }  
    fprintf(stderr, "Vuelta %d\n", i);
    fprintf(stderr, "Recibi de fork() el valor %d\n", child);
    fprintf(stderr, "Soy proceso %d con padre %d\n", getpid(), getppid());
    while(wait(&status) > 0);
  }
  snprintf(command_line, sizeof(command_line), "pstree -p %d > chainp.txt", parent);
  system(command_line);
  return 0;
}
```

### Pregunta b)
```c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/* 
   Este programa crea un abanico de procesos. Es decir el padre crea 
   tres hijos.
   Ejm 2.6 del libro UNIX Programacion Practica - Kay Robbins
   Steve Robbins
   Modificado por Alejandro Bello Ruiz - Informática PUCP 
*/

int main(void) {
    int i, status;
    pid_t child, pid_padre;
    char  command_line[256];
    pid_padre = getpid(); 
    for (i = 1; i <= 3; ++i) {   
        if ((child = fork()) <= 0) break;   
        else fprintf(stderr, "Este es el ciclo Nro %d y se está creando el proceso %d\n", i, child);   
    } 
    if (pid_padre == getpid()) {  
      snprintf(command_line, sizeof(command_line), "pstree -p %d > fanp.txt", pid_padre);
      system(command_line);
      for (i = 1; i <= 3; ++i) {
        wait(&status);  
      }
    } 
    fprintf(stderr, "Este es el proceso %d con padre %d\n", getpid(), getppid()); 
    return 0;
}
```

## Tarea 3

### Pregunta a)
```c
/* 
   multifork.c (c) 2005-2009 Rahmat M. Samik-Ibrahim, GPL-like 
*/

/* *********** *********************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define DISPLAY1 "PID INDUK** ** pid (%5.5d) ** ***********\n"
#define DISPLAY2 "vall(%5.5d) val2(%5.5d) val3(%5.5d)\n"

int main(void) {
    pid_t vall, val2, val3, parent, wpid;
    int status;
    parent = getpid();
    printf(DISPLAY1, (int) getpid());
    fflush(stdout); 
    vall = fork();
    //waitpid(-1, NULL, 0); 
    val2 = fork();
    //waitpid(-1, NULL, 0); 
    val3 = fork();
    //waitpid(-1, NULL, 0); 
    printf(DISPLAY2, (int) vall, (int) val2, (int) val3);
    if (parent == getpid()) {
         char command_line[256];
         snprintf(command_line, sizeof(command_line), "pstree -p %d > multifork.txt", parent);
         system(command_line);
         while ((wpid = waitpid(-1, &status, WUNTRACED)) > 0) {
             kill(wpid, SIGCONT);  
             waitpid(wpid, &status, 0); 
         }
         while (waitpid(-1, &status, 0) > 0);
     }else{
        kill(getpid(), SIGSTOP);
     }
   
    return 0;
}

```
### Pregunta  b)
```c



```

### Pregunta  c)
```c
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//Solucion parcial (funciona para tomar todos los procesos vivos, pero no da el mismo output).
int main(void) {
    int ii = 0, status;
    pid_t parent = getpid();
    pid_t wpid, par1, par2, par3; 
    par1 = fork();
    if (par1 == 0){
       ii++;
    }
    //waitpid(-1, NULL, 0);
    par2 = fork();
    if (par2 == 0){
       ii++;
    } 
    //waitpid(-1, NULL, 0);
    par3 = fork();
    if(par3 == 0){
       ii++;
    }
    //waitpid(-1, NULL, 0); 
    printf("Result = %3.3d\n", ii);
    if (parent == getpid()) {
        char command_line[256];
        snprintf(command_line, sizeof(command_line), "pstree -p %d > isengfork.txt", parent);
        system(command_line);
        while ((wpid = waitpid(-1, &status, WUNTRACED)) > 0) {
            kill(wpid, SIGCONT);  
            waitpid(wpid, &status, 0); 
        }
        while (waitpid(-1, &status, 0) > 0);
    }else{
       kill(getpid(), SIGSTOP);
    }
    return 0;
