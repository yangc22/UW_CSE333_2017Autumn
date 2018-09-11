// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

// copy the elements from array1 to array2 and sort the elements in 
// non-decreasing order
void CopyAndSort(int32_t array1[], int32_t array2[], int32_t size);

// print all the elements in the array to the standard output
void printArray(int32_t array[], int32_t size);

int main(int argc, char** argv) {
  int32_t array1[11] = {3, 2, -5, 7, 13, 4, 1, 7, 8, -8, 6};
  int32_t array2[11];
  int32_t size = 11;
  
  // copy and sort the new created array
  CopyAndSort(array1, array2, size);

  // print the array to the standard output
  printArray(array2, size);
  return 0;
}

void CopyAndSort(int32_t array1[], int32_t array2[], int32_t size) {
  // for the case there is no element, just return
  if (size == 0) return;
  
  // copy the first element
  array2[0] = array1[0];

  // iterate through the first array and do an insertion sort
  for (int32_t i = 1; i < size; i++) {

    // the index from where to start inserting
    int32_t j = i;

    // compare the element with the previous elements to find
    // the right place to insert
    while (j > 0 && array2[j - 1] > array1[i]) {
      array2[j] = array2[j - 1];
      j--;
    }
    array2[j] = array1[i];
  }
}

void printArray(int32_t array[], int32_t size) {
  for (int32_t i = 0; i < size - 1; i++) {
    printf("%" PRId32 "%c ", array[i], ' ');
  }
  printf("%" PRId32 "%c", array[size - 1], '\n');
}
