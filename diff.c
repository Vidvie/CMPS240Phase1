#include "types.h"
#include "user.h"
#define MAXLINE 512

int readline(int fd, char *buf){
  int i = 0;
  char c;
  while(read(fd, &c, 1) == 1){
    if(c == '\n') break;
    if(i < MAXLINE - 1)
      buf[i++] = c;
  }
  buf[n] = 0;
  return n;
}

int main(int argc, char *argv[]){
  int fd1, fd2;
  char line1[MAXLINE], line2[MAXLINE];
  int r1, r2, lineno;

  if(argc != 3){
    printf(2, "Usage: diff file1 file2\n");
    exit();
  }

  fd1 = open(argv[1], 0);
  if(fd1 < 0){ printf(2, "diff: cannot open %s\n", argv[1]); exit(); }

  fd2 = open(argv[2], 0);
  if(fd2 < 0){ printf(2, "diff: cannot open %s\n", argv[2]); exit(); }

  lineno = 1;
  while(1){
    r1 = readline(fd1, line1);
    r2 = readline(fd2, line2);
    if(r1 == 0 && r2 == 0) break;

    if(strcmp(line1, line2) != 0)
      printf(1, "%d: < %s\n    > %s\n", lineno, line1, line2);

    lineno++;
  }

  close(fd1);
  close(fd2);
  exit();
}
