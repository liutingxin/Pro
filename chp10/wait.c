#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
 int status; 
 pid_t pid = fork();
 if(pid == 0)
 {
   return 3;
 }
 else {
    printf("child :%d \n", pid);
    pid = fork();
    if(pid == 0){
      exit(100);     
    } else {
      wait(&status);
      if(WIFEXITED(status))
        printf("ok, return val : %d \n", WEXITSTATUS(status));
      wait(&status);

      if(WIFEXITED(status))
        printf("ok, return val : %d \n", WEXITSTATUS(status));
      sleep(5);
    }
 }  

  return 0;
}
