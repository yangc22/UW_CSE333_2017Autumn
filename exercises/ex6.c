// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

void usage(char *p) {
  fprintf(stderr, "%s", p);
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  FILE *f;

  if (argc != 2) {
    usage("usage: ./ex6 filename\n");
  }

  // open, read, and print the file in reverse order
  f  = fopen(argv[1], "rb");  // "rb" --> read, binary mode
  if (f == NULL) {
    usage("fopen failed --\n");
  }

  // get the length of the file first, then read each byte in
  // order one by one
  int64_t totalLength;
  if (fseek(f, 0, SEEK_END) != 0) {
    usage("error, seeking the end of the file\n");
  }
  totalLength = ftell(f);  // get the total size of the file
  if (totalLength < 0) {
    usage("error, getting the size of the file\n");
  }

  for (int64_t i = -1; i>= -totalLength; i--) {
    char c;
    if (fseek(f, i, SEEK_END) != 0) {
      usage("error, seeking the right byte of the file\n");
    }
    if (fread((void *) &c, sizeof(c), 1, f) != sizeof(c)) {
      usage("error, reading the byte of the file\n");
    }
    printf("%c", c);
  }
  return EXIT_SUCCESS;
}
