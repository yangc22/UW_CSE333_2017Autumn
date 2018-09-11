// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#ifndef _SOCKETUSE_H_
#define _SOCKETUSE_H_

#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>

// DNS lookup on name , and return through the output parameter "ret_addr"
// The length of that struct sockaddr is returned through "ret_addrlen".
// initialize the port to "port".
// Returns true on success, return false on failure
bool LookupName(char *name,
                unsigned short port,
                struct sockaddr_storage *ret_addr,
                size_t *ret_addrlen);

// Connect to the remote host and port specified by addr/addrlen.
// Return a connected socket through the output parameter "ret_fd".
// On failure, returns false.  On success, returns true.
bool Connect(const struct sockaddr_storage &addr,
             const size_t &addrlen,
             int *ret_fd);

int HelpRead(int fd, unsigned char *buf, int readlen);

int HelpWrite(int fd, unsigned char *buf, int writelen);

#endif  // _SOCKETUSE_H_
