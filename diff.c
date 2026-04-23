#include "types.h"
#include "user.h"
#define MAX_LINE_SIZE 512

int readline(int fd, char *buf){
  char c;
  int i = 0;
  while(read(fd, &c, 1) == 1){
    if(c == '\n'){
       break;
    }
    if(i < MAX_LINE_SIZE-1){
      buf[i++] = c;
    }
  }
  buf[i] = 0;
  return i;
}

int main(int argc, char *argv[]){
  int fd1, fd2;
  char l1[MAX_LINE_SIZE], l2[MAX_LINE_SIZE];
  int r1, r2;
  if(argc != 3){
    printf(2, "Wrong number of arguments.\n");
    exit();
  }
  fd1 = open(argv[1], 0);
  if(fd1 < 0){
    printf(2, "Error when trying to open %s.\n", argv[1]);
    exit();
  }
  fd2 = open(argv[2], 0);
  if(fd2 < 0){
    printf(2, "Error when trying to open %s.\n", argv[2]);
    exit();
  }
  int line_Num = 1;
  while(1){
    r1 = readline(fd1, l1);
    r2 = readline(fd2, l2);
    if(r1 == 0 && r2 == 0){
      break;
    }
    if(strcmp(l1, l2) != 0){
      printf(1, "In line %d: \"%s\" different from \"%s\"\n", line_Num, l1, l2);
    }
    line_Num++;
  }

  close(fd1);
  close(fd2);
  exit();
}
