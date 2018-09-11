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

// Feature test macro for strtok_r (c.f., Linux Programming Interface p. 63)
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "libhw1/CSE333.h"
#include "memindex.h"
#include "filecrawler.h"

static void Usage(void);

int main(int argc, char **argv) {
  if (argc != 2)
    Usage();

  // Implement searchshell!  We're giving you very few hints
  // on how to do it, so you'll need to figure out an appropriate
  // decomposition into functions as well as implementing the
  // functions.  There are several major tasks you need to build:
  //
  //  - crawl from a directory provided by argv[1] to produce and index
  //  - prompt the user for a query and read the query from stdin, in a loop
  //  - split a query into words (check out strtok_r)
  //  - process a query against the index and print out the results
  //
  // When searchshell detects end-of-file on stdin (cntrl-D from the
  // keyboard), searchshell should free all dynamically allocated
  // memory and any other allocated resources and then exit.
  char input[1024];
  char *token;
  char *saveptr;
  DocTable doctable;
  MemIndex index;
  LinkedList searchresult;
  LLIter llit;
  SearchResult *rs;

  printf("Indexing \'%s\'\n", argv[1]);
  // crawl from directory argv[1]
  if (CrawlFileTree(argv[1], &doctable, &index) == 0) {
    // terminate the program if crawl failed
    Usage();
  }

  Verify333(doctable != NULL);
  Verify333(index != NULL);

  while (1) {
    printf("enter query:\n");
    if (fgets(input, 1024, stdin) != NULL) {
      char **query = (char **) malloc(512 * sizeof(char *));
      Verify333(query != NULL);

      uint8_t qlen = 0;
      char *str = input;
      while (1) {
        token = strtok_r(str, " ", &saveptr);
        if (token == NULL)
          break;
        query[qlen] = token;
        qlen++;
        str = NULL;
      }


      char *p = strchr(query[qlen - 1], '\n');
      if (p) {
        *p = '\0';
      }

      searchresult = MIProcessQuery(index, query, qlen);
      if (searchresult != NULL) {
        llit = LLMakeIterator(searchresult, 0);
        Verify333(llit != NULL);

        do {
          LLIteratorGetPayload(llit, (void **) &rs);
          printf("  %s (%u)\n", DTLookupDocID(doctable, rs->docid), rs->rank);
        } while (LLIteratorNext(llit));

        LLIteratorFree(llit);
      }

      free(query);
    }
  }

  FreeDocTable(doctable);
  FreeMemIndex(index);

  return EXIT_SUCCESS;
}

static void Usage(void) {
  fprintf(stderr, "Usage: ./searchshell <docroot>\n");
  fprintf(stderr,
          "where <docroot> is an absolute or relative " \
          "path to a directory to build an index under.\n");
  exit(EXIT_FAILURE);
}

