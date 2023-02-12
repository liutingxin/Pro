#include <stdio.h>
#include <unistd.h>

int main()
{
  pid_t pid = fork();

  if(pid == 0) {
    puts("hi i am child p\n");
  }
  else {
    sleep(30);
  } 
  if(pid == 0) {
    puts("end child");
  }else {
    puts("end fath");
  }   
  return 0;
} 
