#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

void handler(int signumber){
  printf("Signal with number %i has arrived\n",signumber);
}

int main(){

  signal(SIGTERM,handler); //handler = SIG_IGN - ignore the signal (not SIGKILL,SIGSTOP), 
                           //handler = SIG_DFL - back to default behavior 
  signal(SIGUSR1,handler);                         
  
  pid_t child=fork();
  if (child>0)
  { 
    pause(); //waits till a signal arrive 
    printf("Signal arrived\n",SIGTERM);

    sleep(1);
    kill(child, SIGUSR1);

    int status;
    wait(&status);
    printf("Parent process ended\n");
  }
  else 
  {
    printf("Waits 3 seconds, then send a SIGTERM %i signal\n",SIGTERM);
    sleep(3);
    kill(getppid(),SIGTERM); 
    pause();
    printf("The signal %i recieved\n", SIGUSR1);
    printf("Child process ended\n");  
  }
  return 0;
}
