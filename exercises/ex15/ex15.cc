// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#include "./socketuse.h"

void Usage();

int main(int argc, char **argv) {
  if (argc != 4) {
    Usage();
  }

  // open up the file
  int file_fd = open(argv[3], O_RDONLY);
  if (file_fd  == -1) {
    Usage();
  }

  unsigned short port = 0;
  if (sscanf(argv[2], "%hu", &port) != 1) {
    Usage();
  }

  struct sockaddr_storage addr;
  size_t addrlen;
  if (!LookupName(argv[1], port, &addr, &addrlen)) {
    Usage();
  }

  // Connect to the remote host.
  int socket_fd;
  if (!Connect(addr, addrlen, &socket_fd)) {
    Usage();
  }

  // Read the input file, write to the network socket.
  unsigned char readbuf[256];
  while (1) {
    int read = HelpRead(file_fd, readbuf, 256);
    if (read <= 0)
      break;

    int write = HelpWrite(socket_fd, readbuf, read);
    if (write != read)
      break;
  }

  close(socket_fd);
  close(file_fd);
  return EXIT_SUCCESS;
}

void Usage() {
  std::cerr << "usage: ./ex15  hostname port filename" << std::endl;
  exit(EXIT_FAILURE);
}
