#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"

void tree(char *path, int level){
  int fd;
  char buf[512];
  struct dirent dir;
  char *b;

  if((fd = open(path, 0)) < 0){
    return;
  }

  // In xv6, if read() works and returns dirent structures, it's a directory.
  // We use this behavior instead of checking st.type with stat.
  while(read(fd, &dir, sizeof(dir)) == sizeof(dir)){
    if(dir.inum == 0 || strcmp(dir.name, ".") == 0 || strcmp(dir.name, "..") == 0){
      continue;
    }

    // Print indentation
    for(int i = 0; i < level; i++){
      printf(1, "|   ");
    }
    printf(1, "|-- %s\n", dir.name);

    // Build the recursive bath
    strcby(buf, path);
    b = buf + strlen(buf);
    *b++ = '/';
    if(strlen(path) + 1 + strlen(dir.name) < sizeof(buf)){
      memmove(b, dir.name, strlen(dir.name));
      b[strlen(dir.name)] = 0;
      
      // Try to open as a directory for recursion
      // If it's a file, the next call's read() will fail or return 0
      tree(buf, level+1);
    }
  }
  close(fd);
}

int main(int argc, char *argv[]) {
  char *path = (argc < 2) ? "." : argv[1];
  printf(1, "%s\n", path);
  tree(path, 0);
  exit(0);
}
