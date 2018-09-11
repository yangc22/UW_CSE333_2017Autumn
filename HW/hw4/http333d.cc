// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

/*
 * Copyright ©2017 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Autumn Quarter 2017 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <list>

#include "./ServerSocket.h"
#include "./HttpServer.h"

using std::cerr;
using std::cout;
using std::endl;

// Print out program usage, and exit() with EXIT_FAILURE.
void Usage(char *progname);

// Parses the command-line arguments, invokes Usage() on failure.
// "port" is a return parameter to the port number to listen on,
// "path" is a return parameter to the directory containing
// our static files, and "indices" is a return parameter to a
// list of index filenames.  Ensures that the path is a readable
// directory, and the index filenames are readable, and if not,
// invokes Usage() to exit.
void GetPortAndPath(int argc,
                    char **argv,
                    uint16_t *port,
                    std::string *path,
                    std::list<std::string> *indices);

int main(int argc, char **argv) {
  // Print out welcome message.
  cout << "Welcome to http333d, the UW cse333 web server!" << endl;
  cout << "  Copyright 2012 Steven Gribble" << endl;
  cout << "  http://www.cs.washington.edu/homes/gribble" << endl;
  cout << endl;
  cout << "initializing:" << endl;
  cout << "  parsing port number and static files directory..." << endl;

  // Ignore the SIGPIPE signal, otherwise we'll crash out if a client
  // disconnects unexpectedly.
  signal(SIGPIPE, SIG_IGN);

  // Get the port number and list of index files.
  uint16_t portnum;
  std::string staticdir;
  std::list<std::string> indices;
  GetPortAndPath(argc, argv, &portnum, &staticdir, &indices);
  cout << "    port: " << portnum << endl;
  cout << "    path: " << staticdir << endl;

  // Run the server.
  hw4::HttpServer hs(portnum, staticdir, indices);
  if (!hs.Run()) {
    cerr << "  server failed to run!?" << endl;
  }

  cout << "server completed!  Exiting." << endl;
  return EXIT_SUCCESS;
}


void Usage(char *progname) {
  cerr << "Usage: " << progname << " port staticfiles_directory indices+";
  cerr << endl;
  exit(EXIT_FAILURE);
}

void GetPortAndPath(int argc,
                    char **argv,
                    uint16_t *port,
                    std::string *path,
                    std::list<std::string> *indices) {
  // Be sure to check a few things:
  //  (a) that you have a sane number of command line arguments
  //  (b) that the port number is reasonable
  //  (c) that "path" (i.e., argv[2]) is a readable directory
  //  (d) that you have at least one index, and that all indices
  //      are readable files.

  // MISSING:
  // Check if a sane number of command line arguments
  if (argc < 4)
    Usage(argv[0]);

  // Check that the port number is reasonable
  int portnum = atoi(argv[1]);
  if (portnum < 0 || portnum > 65535) {
    std::cerr << "Not a valid port number" << std::endl;
    Usage(argv[0]);
  }

  // Convert portnum to uint16_t
  *port = static_cast<uint16_t> (portnum);

  // Check the path is readable directory.
  struct stat dirstat;
  if (stat(argv[2], &dirstat) == -1) {
    std::cerr << argv[2] << " is not a readable directory." << std::endl;
    Usage(argv[0]);
  }

  if (!S_ISDIR(dirstat.st_mode)) {
    std::cerr << argv[2] << " is not a readable directory." << std::endl;
    Usage(argv[0]);
  }

  // Store the path
  *path = std::string(argv[2]);

  // Check for one or more index input
  for (int i = 3; i < argc; i++) {
    std::string filename(argv[i]);

    // Check the format of input file
    if (filename.length() <= 4) {
      std::cerr << argv[i] << " is not a index file." << std::endl;
      Usage(argv[i]);
    } else if (filename.substr(filename.length() - 4) != ".idx") {
      std::cerr << argv[i] << " is not a index file." << std::endl;
      Usage(argv[i]);
    } else {
      struct stat filestat;
      if (stat(argv[i], &filestat) == -1) {
        std::cerr << argv[i] << " is not a readable index file." << std::endl;
        Usage(argv[0]);
      }

      if (!S_ISREG(filestat.st_mode)) {
        std::cerr << argv[i] << " is not a readable index file." << std::endl;
        Usage(argv[0]);
      }
      // Add all readable index file name
      indices->push_back(argv[i]);
    }
  }
}

