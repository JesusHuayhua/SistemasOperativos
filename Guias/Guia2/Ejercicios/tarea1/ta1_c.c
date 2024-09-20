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
    sprintf(commandline, "pstree -p %d > procesos_c.txt", parent);
    fprintf(stderr, "[CHILD] child process=%d\nchild PID=%d\n",child, getpid());
    system(commandline);
  }  
  while ((parent = wait(&status)) > 0); 
  return 0;
}