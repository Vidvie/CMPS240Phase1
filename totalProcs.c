#include "types.h"
#include "user.h"

int main(void){
  int pid;
  for(int i=0;i<3;i++){
    pid = fork();
    if(pid == 0){
      for(int j=0;j<5;j++){
        printf(1,"child %d is running, in loop %d\n" , getpid(), j);
      }
    exit();
    }
  }
  for(int i=0;i<5;i++){
    wait();
  }
  exit();
}
