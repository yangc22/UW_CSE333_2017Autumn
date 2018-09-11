#ifndef _SOCKETUTIL_H_
#define _SOCKETUTIL_H_

#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>

// Do a DNS lookup on name "name", and return through the output
// parameter "ret_addr" a fully-formed struct sockaddr.  The length
// of that struct sockaddr is returned through "ret_addrlen".  Also
// initialize the port to "port".
//
// On failure, returns false.  On success, returns true.
bool LookupName(char *name,
                unsigned short port,
                struct sockaddr_storage *ret_addr,
                size_t *ret_addrlen);

// A wrapper around "read" that shields the caller from dealing
// with the ugly issues of partial reads, EINTR, EAGAIN, and so
// on.
//
// Read at most "readlen" bytes from the file descriptor fd
// into the buffer "buf".  Return the number of bytes actually
// read.  On fatal error, return -1.  If EOF is hit and no
// bytes have been read, return 0.  Might read fewer bytes
// than requested.
int WrappedRead(int fd, unsigned char *buf, int readlen);

// A wrapper around "write" that shields the caller from dealing
// with the ugly issues of partial writes, EINTR, EAGAIN, and so
// on.
//
// Write "writelen" bytes to the file descriptor fd from
// the buffer "buf".  Blocks the caller until either writelen
// bytes have been written, or an error is encountered.  Return
// the total number of bytes written; if this number is less
// than writelen, it's because some fatal error was encountered,
// like the connection being dropped.
int WrappedWrite(int fd, unsigned char *buf, int writelen);

// Connect to the remote host and the specified port. Then return
// a connected socket.
//
// On failure, returns false.  On success, returns true.
bool Connect(const struct sockaddr_storage &addr,
             const size_t &addrlen,
             int *ret_fd);

// Create a listening socket that is connexted to any IP address
// and to the specified port number.
//
// On success, return a file descriptor for the listening socket.
// Also return through the output parameter of the network address family.
//
// On failure, returns -1.
int Listen(char *portnum, int *sock_family);


// Print to stdout information about the file descriptor "fd" and
// the struct sockaddr pointer to by the argument.
void printOut(int fd, struct sockaddr *addr, size_t addrlen);

// Attempt to do a reverse DNS lookup on to find the DNS name
// associated with the IP address.
void printReverseDNS(struct sockaddr *addr, size_t addrlen);

#endif  // _SOCKETUTIL_H_
