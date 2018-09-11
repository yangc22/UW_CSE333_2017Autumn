// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "Vector.h"

#define N 10  // Test vector length.

// Print the elements in the vector on a line.
static void PrintIntVector(vector_t v);

int main(int argc, char *argv[]) {
  uint32_t i;
  vector_t v = VectorCreate(4);

  if (v == NULL) {
    return EXIT_FAILURE;
  }

  // Place some elements in the vector.
  for (i = 0; i < N; ++i) {
    int *x = (int*)malloc(sizeof(int));
    if (x == NULL) {
      return EXIT_FAILURE;
    }
    element_t old;
    *x = i;
    bool result = VectorSet(v, i, x, &old);
    if (!result) {
      return EXIT_FAILURE;
    }
  }

  PrintIntVector(v);

  return EXIT_SUCCESS;
}

static void PrintIntVector(vector_t v) {
  uint32_t i;
  size_t length;

  assert(v != NULL);

  length = VectorLength(v);

  if (length > 0) {
    printf("[%d", *((int*)VectorGet(v, 0)));
    for (i = 1; i < VectorLength(v); ++i)
      printf(",%d", *((int*)VectorGet(v, i)));
    printf("]\n");
  }
}

