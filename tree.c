#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

void tree(char *path, int depth){
  int fd;
  struct dirent dir;
  struct stat s;
  char buf[512];
  fd = open(path, 0);
  if(fd < 0){
    printf(2, "Error when trying to open %s\n", path);
    return;
  }
  if(fstat(fd, &s) < 0 || s.type != T_DIR){
    close(fd);
    return;
  }
  while(read(fd, &dir, sizeof(dir)) == sizeof(dir)){
    if(dir.inum == 0){
      continue;
    }
    if(strcmp(dir.name, ".") == 0 || strcmp(dir.name, "..") == 0){
      continue;
    }
    for(int i=0; i<depth; i++){
      printf(1, "  ");
    }
    printf(1, "|-- %s\n", dir.name);
    memmove(buf, path, strlen(path));
    buf[strlen(path)] = '/';
    memmove(buf+strlen(path)+1, dir.name, strlen(dir.name)+1);
    tree(buf, depth+1);
  }
  close(fd);
}

int main(int argc, char *argv[]){
  char *p;
  if(argc > 1){
    p = argv[1];
  }
  else{
    p =  ".";
  }
  printf(1, "%s\n", p);
  tree(p, 0);
  exit();
}
