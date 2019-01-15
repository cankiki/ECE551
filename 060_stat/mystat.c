#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
void print_first_three(struct stat sb);
void printAccess(struct stat sb);
void printTime(struct stat sb);

int main(int argc, char * argv[]) {
  struct stat sb;

  if (argc < 2) {  //take an arbitrary number of arguments
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  int i;
  for (i = 1; i < argc; i++) {
    if (lstat(argv[i], &sb) == -1) {
      perror("lstat");
      exit(EXIT_FAILURE);
    }
    else {
      if (S_ISLNK(sb.st_mode)) {  //check if the file is a symbolic link
        char linktarget[256];
        ssize_t len = readlink(argv[i], linktarget, 256);
        if (len == -1) {
          perror("readlink");
        }
        linktarget[len] = '\0';
        printf("  File: %s -> %s\n", argv[i], linktarget);
      }
      else {
        printf("  File: %s\n", argv[i]);
      }
      print_first_three(sb);
      printAccess(sb);
      printTime(sb);
    }
  }
  return EXIT_SUCCESS;
}

void print_first_three(struct stat sb) {  //print out the first THREE lines stat
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu ",
         (long unsigned)sb.st_size,
         (long unsigned)sb.st_blocks,
         (long unsigned)sb.st_blksize);
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      printf("block special file\n");
      break;
    case S_IFCHR:
      printf("character special file\n");
      break;
    case S_IFDIR:
      printf("directory\n");
      break;
    case S_IFIFO:
      printf("fifo\n");
      break;
    case S_IFLNK:
      printf("symbolic link\n");
      break;
    case S_IFREG:
      if (sb.st_size == 0) {  //check for empty file
        printf("regular empty file\n");
      }
      else {
        printf("regular file\n");
      }
      break;
    case S_IFSOCK:
      printf("socket\n");
      break;
    default:
      printf("unknown?\n");
      break;
  }
  if (S_ISCHR(sb.st_mode) || S_ISBLK(sb.st_mode)) {  //checking if the file is a device
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
           sb.st_dev,
           sb.st_dev,
           (long unsigned)sb.st_ino,
           (long unsigned)sb.st_nlink,
           major(sb.st_rdev),
           minor(sb.st_rdev));
  }
  else {
    printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
           sb.st_dev,
           sb.st_dev,
           (long unsigned)sb.st_ino,
           (long unsigned)sb.st_nlink);
  }
}
void printAccess(struct stat sb) {  //print out the FOURTH line
  char s[11];
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      s[0] = 'b';
      break;
    case S_IFCHR:
      s[0] = 'c';
      break;
    case S_IFDIR:
      s[0] = 'd';
      break;
    case S_IFIFO:
      s[0] = 'p';
      break;
    case S_IFLNK:
      s[0] = 'l';
      break;
    case S_IFREG:
      s[0] = '-';
      break;
    case S_IFSOCK:
      s[0] = 's';
      break;
  }
  if ((sb.st_mode & S_IRUSR) != 0) {
    s[1] = 'r';
  }
  else {
    s[1] = '-';
  }
  if ((sb.st_mode & S_IWUSR) != 0) {
    s[2] = 'w';
  }
  else {
    s[2] = '-';
  }
  if ((sb.st_mode & S_IXUSR) != 0) {
    s[3] = 'x';
  }
  else {
    s[3] = '-';
  }
  if ((sb.st_mode & S_IRGRP) != 0) {
    s[4] = 'r';
  }
  else {
    s[4] = '-';
  }
  if ((sb.st_mode & S_IWGRP) != 0) {
    s[5] = 'w';
  }
  else {
    s[5] = '-';
  }
  if ((sb.st_mode & S_IXGRP) != 0) {
    s[6] = 'x';
  }
  else {
    s[6] = '-';
  }
  if ((sb.st_mode & S_IROTH) != 0) {
    s[7] = 'r';
  }
  else {
    s[7] = '-';
  }
  if ((sb.st_mode & S_IWOTH) != 0) {
    s[8] = 'w';
  }
  else {
    s[8] = '-';
  }
  if ((sb.st_mode & S_IXOTH) != 0) {
    s[9] = 'x';
  }
  else {
    s[9] = '-';
  }
  s[10] = '\0';
  struct passwd * pwd = getpwuid(sb.st_uid);

  struct group * gp = getgrgid(sb.st_gid);
  printf("Access: (%04o/%s)", sb.st_mode & ~S_IFMT, s);
  printf("  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n", sb.st_uid, pwd->pw_name, sb.st_gid, gp->gr_name);
}
//This function is for step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}
void printTime(struct stat sb) {  //print out the last four lines
  char * a_timestr = time2str(&sb.st_atime, sb.st_atim.tv_nsec);
  printf("Access: %s\n", a_timestr);
  free(a_timestr);
  char * m_timestr = time2str(&sb.st_mtime, sb.st_mtim.tv_nsec);
  printf("Modify: %s\n", m_timestr);
  free(m_timestr);
  char * c_timestr = time2str(&sb.st_ctime, sb.st_ctim.tv_nsec);
  printf("Change: %s\n", c_timestr);
  free(c_timestr);
  printf(" Birth: -\n");
}
