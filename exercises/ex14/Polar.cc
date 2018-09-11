// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include <cmath>
#include <sstream>

#include "./Polar.h"

std::string Polar::ToString() const {
  std::stringstream ss;
  ss << "Polar Coordinate (" << r_ << ", " << theta_ << ")";
  std::string s = ss.str();
  return s;
}

double Polar::Distance(const Polar &other) const {
  double sum = 0;
  double x = (other.r_*cos(other.theta_) - r_*cos(theta_));
  double y = (other.r_*sin(other.theta_) - r_*sin(theta_));
  sum += x * x + y * y;
  return sqrt(sum);
}
