// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include <iostream>
#include <cstdlib>
#include "intPair.h"

void Test(intPair i) {
  int x, y;

  i.get(&x, &y);
  i.set(x + 1, y + 1);
}

int main(int argc, char **argv) {
  intPair t(0, 0);
  Test(t);

  int x, y;
  t.get(&x, &y);
  if ((x == 1) || (y == 1)) {
    std::cout << "Is pass by reference\n";
  } else {
    std::cout << "Is pass by value\n";
  }
  return EXIT_SUCCESS;
}
