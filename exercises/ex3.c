// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

// a structured type called Point3d, which has three
// fields: x, y, z as its coordinates.
typedef struct Point_3d {
  int32_t x;
  int32_t y;
  int32_t z;
} Point3d, *Point3d_ptr;

// take three int32_t as arguments and return a Point3d pointer
// using malloc to allocate the space of the pointer, caller should
// free the space after using it.
Point3d_ptr AllocatePoint3d(int32_t p_x, int32_t p_y, int32_t p_z) {
  // allocate the pointer of exact size of the Point3d
  Point3d *retval = (Point3d *) malloc(sizeof(Point3d));

  // if it failed to allocate the space, infrom the caller.
  if (retval == NULL) {
    printf("Failed to allocate space for the Point3d pointer");
    return NULL;
  }

  // assign the value of each field
  retval->x = p_x;
  retval->y = p_y;
  retval->z = p_z;
  return retval;
}

int main(int argc, char** argv) {
  Point3d *point = AllocatePoint3d(1, 2, 3);
  // check if the allocation fails
  if (point == NULL) {
    printf("Allocate failed!");
    return EXIT_FAILURE;
  }

  // check if the allocation is right
  if (point->x != 1 || point->y != 2 || point->z != 3) {
    printf("Failed to construct the right struct!");
    return EXIT_FAILURE;
  }

  // free the heap space
  free(point);
  return EXIT_SUCCESS;
}
