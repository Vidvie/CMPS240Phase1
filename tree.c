#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

// Box-drawing prefixes
#define PIPE_BRANCH  "|-- "
#define PIPE_LAST    "`-- "
#define PIPE_INDENT  "|   "
#define BLANK_INDENT "    "

// Max depth / indent buffer
#define MAX_DEPTH 32

static int dir_count;
static int file_count;

// indent[d] holds the prefix string for depth d
static char indent[MAX_DEPTH][8];

static char*
basename(char *path)
{
  char *p = path + strlen(path);
  while (p > path && *(p-1) != '/')
    p--;
  return p;
}

void
tree(char *path, int depth)
{
  int fd;
  struct dirent de;
  struct stat st;
  char buf[512];
  char *entries[512];
  int nentries = 0;
  int i;

  if (depth >= MAX_DEPTH)
    return;

  fd = open(path, 0);
  if (fd < 0) {
    printf(2, "tree: cannot open %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0) {
    printf(2, "tree: cannot stat %s\n", path);
    close(fd);
    return;
  }

  if (st.type != T_DIR) {
    close(fd);
    return;
  }

  // Collect non-dot entries
  while (read(fd, &de, sizeof(de)) == sizeof(de)) {
    if (de.inum == 0)
      continue;
    if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
      continue;
    if (nentries < 512) {
      entries[nentries] = malloc(DIRSIZ + 1);
      memmove(entries[nentries], de.name, DIRSIZ);
      entries[nentries][DIRSIZ] = '\0';
      nentries++;
    }
  }
  close(fd);

  // Print each entry
  for (i = 0; i < nentries; i++) {
    int is_last = (i == nentries - 1);
    int d;

    // Print accumulated indent
    for (d = 0; d < depth; d++)
      printf(1, "%s", indent[d]);

    // Branch symbol
    printf(1, "%s", is_last ? PIPE_LAST : PIPE_BRANCH);
    printf(1, "%s", entries[i]);

    // Build full path and stat it
    memmove(buf, path, strlen(path));
    buf[strlen(path)] = '/';
    memmove(buf + strlen(path) + 1, entries[i], strlen(entries[i]) + 1);

    fd = open(buf, 0);
    if (fd >= 0 && fstat(fd, &st) >= 0) {
      if (st.type == T_DIR) {
        printf(1, "\n");
        dir_count++;
        indent[depth] = is_last ? BLANK_INDENT : PIPE_INDENT;
        tree(buf, depth + 1);
      } else {
        printf(1, "\n");
        file_count++;
      }
      close(fd);
    } else {
      printf(1, "\n");
    }

    free(entries[i]);
  }
}

int
main(int argc, char *argv[])
{
  char *path = (argc > 1) ? argv[1] : ".";

  dir_count = 0;
  file_count = 0;

  printf(1, "%s\n", path);
  tree(path, 0);
  printf(1, "\n%d directories, %d files\n", dir_count, file_count);

  exit();
}
