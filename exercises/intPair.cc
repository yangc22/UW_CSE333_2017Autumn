// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include "intPair.h"

intPair::intPair(const int x, const int y) {
  this->x_ = x;
  this->y_ = y;
}

void intPair::get(int *x, int *y) {
  *x = x_;
  *y = y_;
}

void intPair::set(const int x, const int y) {
  this->x_ = x;
  this->y_ = y;
}
