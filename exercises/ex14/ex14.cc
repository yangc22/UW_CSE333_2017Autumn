// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include <stdlib.h>
#include <iostream>

#include "./Coordinate.h"
#include "./Cartesian.h"
#include "./Polar.h"

int main(int argc, char **argv) {
  Cartesian a(1, 0), b(0, 1);
  Polar c(1, 0.5), d(2, -1);

  std::cout << "a: " << a.ToString() << "\n";
  std::cout << "b: " << b.ToString() << "\n";
  std::cout << "distance between a and b: " << a.Distance(b) << "\n";

  std::cout << "c: " << c.ToString() << "\n";
  std::cout << "d: " << d.ToString() << "\n";
  std::cout << "distance between c and d: " << c.Distance(d) << "\n";

  return EXIT_SUCCESS;
}
