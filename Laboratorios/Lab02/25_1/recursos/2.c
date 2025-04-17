#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/* Este programa crea un abanico de procsos.                       */
/* Ejm 2.6 del libro UNIX Programacion Practica - Kay Robbins      */
/*                                                Steve Robbins    */

int main(int narg, char *argv[])
{ int i,status,n;
  pid_t child,pid_padre;
  
  if(narg != 2) {
      printf("Usage: %s <n>\n",argv[0]);
      exit(1);
  }
  n=atoi(argv[1]);
  
  if(!(n%2))
     n++;
  printf("%d\n",n);   
  pid_padre=getpid(); 
  for(i=0;i<n; ++i)
     if((child=fork())<=0) break;    
  if(pid_padre==getpid()) for(i=0;i<n;++i) wait(&status);
  return 0;
}


