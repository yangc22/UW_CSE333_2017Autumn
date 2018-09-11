// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include <iostream>
#include <sstream>
#include <cstdlib>

#include "Vector.h"

using namespace vector333;

int main(int argc, char **argv) {
  // test all the constructors
  Vector a;
  std::cout << "Test the default constructor, should be (0,0,0): ";
  std::cout << a << std::endl;
  Vector b(0.1, 0.2, 0.3);
  std::cout << "Test the normal constructor, should be (0.1,0.2,0.3): ";
  std::cout << b << std::endl;
  Vector c(b);
  std::cout << "Test the copy constructor, should be (0.1,0.2,0.3): ";
  std::cout << c << std::endl;

  // test the member function operators
  Vector d;
  d = c;
  std::cout << "Test the assignment operator, should be (0.1,0.2,0.3): ";
  std::cout << d << std::endl;
  d += c;
  std::cout << "Test the += operator, should be (0.2,0.4,0.6): ";
  std::cout << d << std::endl;
  d -= c;
  std::cout << "Test the -= operator, should be (0.1,0.2,0.3): ";
  std::cout << d << std::endl;

  Vector e;
  e = c + d;
  std::cout << "Test the + operator, should be (0.2,0.4,0.6): ";
  std::cout << e << std::endl;
  e = c - d;
  std::cout << "Test the - operator, should be (0,0,0): ";
  std::cout << e << std::endl;

  // test the non-member function operators
  Vector f(1.0, 1.0, 1.0);
  double dp = d * f;
  std::cout << "Test the * operator, should be 0.6: ";
  std::cout << dp << std::endl;

  double s = 2.0;
  e = s * d;
  std::cout << "Test the * operator, should be (0.2,0.4,0.6): ";
  std::cout << e << std::endl;
  e = d * s;
  std::cout << "Test the * operator, should be (0.2,0.4,0.6): ";
  std::cout << e << std::endl;

  return EXIT_SUCCESS;
}
