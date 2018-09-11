// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>

namespace vector333 {

class Vector {
  public:
    Vector();  // default constructor
    Vector(const float x, const float y, const float z);  // constructor
    Vector(const Vector& copyme);  // copy constructor
    ~Vector();

  //  Accessors function
  float getx() const { return x_; }
  float gety() const { return y_; }
  float getz() const { return z_; }

  // override the "=", "+=", "-=", "+", "-"
  // "*" operators
  Vector &operator=(const Vector &copyme);
  Vector &operator+=(const Vector &v);
  Vector &operator-=(const Vector &v);

  private:
    float x_, y_, z_;
};  // class Vector

Vector operator+(const Vector &a, const Vector &b);
Vector operator-(const Vector &a, const Vector &b);
float operator*(const Vector &a, const Vector &b);
Vector operator*(const Vector &a, const double s);
Vector operator*(const double s, const Vector &a);
std::ostream &operator<<(std::ostream &out, const Vector &a);
}

#endif  // _VECTOR_H_
