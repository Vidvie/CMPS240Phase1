#include "types.h"
#include "user.h"

int counter = 0;

void thread_func(void){
  counter++;
  printf(1, "thread: counter = %d\n", counter);
  exit();
}

int main(void){
  char *stack = malloc(4096);
  counter = 10;
  int pid = clone(stack);
  if(pid < 0){
    printf(1, "clone failed\n");
    exit();
  }
  if(pid == 0){
    thread_func();
  }
  wait();
  printf(1, "parent: counter = %d\n", counter);
  exit();
}
