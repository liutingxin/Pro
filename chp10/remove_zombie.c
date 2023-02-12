#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

void read_child(int sig)
{

  int status = 0;
  pid_t pid = waitpid(-1, &status, WNOHANG);
  if(WIFEXITED(status))
  {
    printf("reamove child: %d\n", pid);
    printf("return val: %d\n", WEXITSTATUS(status));
  }
}

int main(int argc, char* argv[])
{

  pid_t pid;
  struct sigaction act;
  act.sa_handler = read_child;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  sigaction(SIGCHLD, &act, 0);

  pid = fork();
  if(pid == 0)
  {

    puts("Hi i am 1 child");
    sleep(6);
    return 3412;
  }
  else 
  {
    printf("child 1: %d\n", pid);
    pid = fork();
    if(pid == 0)
    {
      puts("i am 2 child\n");
      sleep(12);
      exit(612);
    }
    else
    {

      int i;
      printf("Child proc id: %d \n", pid);

      for(int i = 0; i < 5; ++i)
      {
        puts("wait...");
        sleep(5);
      }
    }
  }
  return 0;

}


