#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  int status;
  pid_t pid = fork();

  if(pid == 0)
  {
    sleep(5);
    return 123;
  }
  else 
  {
    while(!waitpid(-1, &status, WNOHANG))
    {
      sleep(3);
      puts("sleep 3");
    } 
    
    if(WIFEXITED(status))
    {
      printf("return val = %d\n", WEXITSTATUS(status));
    }
  }
    return 0;
}
