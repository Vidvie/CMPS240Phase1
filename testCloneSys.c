#include "types.h"
#include "user.h"

int count = 0;

void Testfunc(void){
  count++;
  printf(1, "thread: counter = %d\n", count);
  exit();
}

int main(void){
  char *s = malloc(4096);
  count = 10;
  int pid = clone(s);
  if(pid < 0){
    printf(1, "Error when trying to clone.\n");
    exit();
  }
  if(pid == 0){
    Testfunc();
  }
  wait();
  printf(1, "parent: counter = %d\n", counter);
  exit();
}
