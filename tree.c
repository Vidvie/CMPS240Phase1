#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

void
tree(char *path, int depth)
{
  int fd, i;
  struct dirent de;
  struct stat st;
  char buf[512];

  fd = open(path, 0);
  if(fd < 0){
    printf(2, "tree: cannot open %s\n", path);
    return;
  }
  if(fstat(fd, &st) < 0 || st.type != T_DIR){
    close(fd);
    return;
  }

  while(read(fd, &de, sizeof(de)) == sizeof(de)){
    if(de.inum == 0) continue;
    if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) continue;

    for(i = 0; i < depth; i++)
      printf(1, "  ");
    printf(1, "|-- %s\n", de.name);

    memmove(buf, path, strlen(path));
    buf[strlen(path)] = '/';
    memmove(buf + strlen(path) + 1, de.name, strlen(de.name) + 1);
    tree(buf, depth + 1);
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  char *path = argc > 1 ? argv[1] : ".";
  printf(1, "%s\n", path);
  tree(path, 0);
  exit();
}
