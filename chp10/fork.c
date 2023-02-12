#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int gval = 10;

int main()
{
  pid_t pid;
  int lval = 100;

  pid = fork();
  if(pid == 0) {
    gval += 10;
    lval += 10;
    printf("i am child, gval = %d, lval = %d\n", gval, lval);
  } 
  else {
    gval -= 10;
    lval -= 10;
    printf("i am father, gval = %d, lval = %d\n", gval, lval);
  }

  return 0;
}
