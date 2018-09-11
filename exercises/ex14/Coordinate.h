// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#ifndef _COORDINATE_H_
#define _COORDINATE_H_
#include <string>

class Coordinate {
  public:

    // virtual destructor
    virtual ~Coordinate() { }

    // appropriate string representation of the coordinate
    virtual std::string ToString() const = 0;
};

#endif  // _COORDINATE_H_
