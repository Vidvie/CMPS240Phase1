#include "types.h"
#include "user.h"

int count = 0;

int main(void){
  count = 10;
  int pid = clone();
  if(pid < 0){
    printf(1, "clone failed\n");
    exit();
  }
  if(pid == 0){
    count++;
    printf(1, "thread counter is %d\n", count);
    exit();
  }
  wait();
  printf(1, "parent counter is %d\n", count);
  exit();
}
