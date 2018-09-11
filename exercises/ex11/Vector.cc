// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include <iostream>
using namespace std;

#include "./Vector.h"

namespace vector333 {

  Vector::Vector() {
    field = (float *) malloc(3 * sizeof(float));
    field[0] = 0;
    field[1] = 0;
    field[2] = 0;
  }

  Vector::Vector(const float x, const float y, const float z) {
    field = (float *) malloc(3 * sizeof(float));
    field[0] = x;
    field[1] = y;
    field[2] = z;
  }

  Vector::Vector(const Vector& copyme) {
    field = (float *) malloc(3 * sizeof(float));
    field[0] = copyme.field[0];
    field[1] = copyme.field[1];
    field[2] = copyme.field[2];
  }

  Vector::~Vector() {
    free(field);
  }

  // Vector assignment
  Vector &Vector::operator=(const Vector &rhs) {
    // replace state of this with values from rhs; do nothing if
    // self-asignment. (Even though in this particular case there would
    // be no harm, it's always best to check for self-assignment and do
    // nothing if detected.)
    if (this != &rhs) {
      field[0] = rhs.field[0];
      field[1] = rhs.field[1];
      field[2] = rhs.field[2];
    }
    // return reference to lhs of assignment
    return *this;
  }

  // Updating assignments for vectors

  Vector &Vector::operator+=(const Vector &rhs) {
    field[0] += rhs.field[0];
    field[1] += rhs.field[1];
    field[2] += rhs.field[2];
    return *this;
  }

  Vector &Vector::operator-=(const Vector &rhs) {
    field[0] -= rhs.field[0];
    field[1] -= rhs.field[1];
    field[2] -= rhs.field[2];
    return *this;
  }

  // Friend functions that are not members of class Vector

  // dot-product: if a is (a,b,c) and b is (x,y,z),
  // return ax+by+cz
  double operator*(const Vector &a, const Vector &b) {
    return a.field[0]*b.field[0] + a.field[1]*b.field[1]
            + a.field[2]*b.field[2];
  }

  // scalar multiplication: if v is (a,b,c), return (ak,bk,ck)
  Vector operator*(const double k, const Vector &v) {
    return Vector(v.field[0] * k, v.field[1] * k, v.field[2] * k);
  }
  Vector operator*(const Vector &v, const double k) {
    return Vector(v.field[0] * k, v.field[1] * k, v.field[2] * k);
  }

  // Stream output: << for Vectors
  ostream & operator<<(ostream &out, const Vector &v) {
    out << "(" << v.field[0] << "," << v.field[1] << "," << v.field[2] << ")";
    return out;
  }

  // Additional non-member functions that are part of the Vector absraction

  // Vector addition
  Vector operator+(const Vector &a, const Vector &b) {
    Vector tmp = a;
    tmp += b;
    return tmp;
  }

  // Vector subtraction
  Vector operator-(const Vector &a, const Vector &b) {
    Vector tmp = a;
    tmp -= b;
    return tmp;
  }

} // namespace vector333
