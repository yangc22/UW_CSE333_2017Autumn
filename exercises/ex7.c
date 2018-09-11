// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define SIZE 1024  // maximum size of the buffer

// function to distinguish whether the file name
// ends with ".txt"

int EndsWith(const char *str, const char *suffix) {
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: ./dirdump <path>\n");
    exit(1);
  }

  // get the DIR pointer of the specified directory
  DIR* dirp = opendir(argv[1]);

  if (dirp == NULL) {
    fprintf(stderr, "Could not open directory\n");
    exit(1);
  }

  struct dirent *entry;

  entry = readdir(dirp);
  while (entry) {
    // tell whether the file name ends with ".txt"
    if (EndsWith(entry->d_name, ".txt")) {
      // if the file name ends with ".txt"
      // create the file descriptor, read and write
      int fd = open(entry->d_name, O_RDONLY);
      if (fd == -1) {
        fprintf(stderr, "Could not open file for reading\n");
        exit(1);
      }

      char buf[SIZE] = "";
      ssize_t len = 0;

      // begin reading the file
      do {
        len = read(fd, buf, SIZE);
        if (len == -1) {
          if (errno != EINTR) {
            close(fd);
            perror(NULL);
            exit(1);
          }
          continue;
        }
      } while (len > 0);

      // after reading the whole file, print to stdout
      printf("%s", buf);
      close(fd);  // close the file
    }
    entry = readdir(dirp);  // read the next file
  }

  closedir(dirp);  // close the directory descriptor
  return 0;
}
