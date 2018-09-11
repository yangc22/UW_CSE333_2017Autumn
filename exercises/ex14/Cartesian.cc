// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include <cmath>
#include <sstream>

#include "./Cartesian.h"

std::string Cartesian::ToString() const {
  std::stringstream ss;
  ss << "Cartesian Coordinate (" << x_ << ", " << y_ << ")";
  std::string s = ss.str();
  return s;
}

double Cartesian::Distance(const Cartesian &other) const {
  double sum = 0;
  sum += (other.x_ - x_) * (other.x_ - x_);
  sum += (other.y_ - y_) * (other.y_ - y_);
  return sqrt(sum);
}
