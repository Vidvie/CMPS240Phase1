#include "types.h"
#include "user.h"

int count = 0;

int main(void){
  count = 10;
  int pid = clone();
  if(pid == 0){
    count++;
    printf(1, "thread: counter = %d\n", count);
    exit();
  }
  wait();
  printf(1, "parent: counter = %d\n", count);
  exit();
}
