#include "types.h"
#include "user.h"

int counter = 0;

void thread_func(void){
  counter++;
  printf(1, "thread: counter = %d\n", counter);
  exit();
}

int main(void){
  char *stack = (char*)malloc(4096);
  stack = (char*)(((uint)stack + 4095) & ~0xfff);
  counter = 10;
  int pid = clone(stack);
  if(pid < 0){
    printf(1, "clone failed\n");
    exit();
  }
  wait();
  printf(1, "parent: counter = %d\n", counter);
  exit();
}
