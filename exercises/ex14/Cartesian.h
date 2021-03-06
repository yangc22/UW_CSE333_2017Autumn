// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#ifndef _CARTESIAN_H_
#define _CARTESIAN_H_

#include <string>

#include "./Coordinate.h"

class Cartesian : public Coordinate {
  public:
    Cartesian(double x, double y) : x_(x), y_(y) {}
    virtual ~Cartesian() {}

    // string representation for Cartesian coordiante
    std::string ToString() const override;

    // distance between two Cartesian points
    double Distance(const Cartesian &other) const;

  private:
    double x_, y_;  // cartesian coordinates
};

#endif  // _CARTESIAN_H_
