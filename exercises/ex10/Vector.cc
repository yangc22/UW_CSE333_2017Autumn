// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include <iostream>
#include <sstream>

#include "Vector.h"

namespace vector333 {

Vector::Vector() {
  this->x_ = 0;
  this->y_ = 0;
  this->z_ = 0;
}

Vector::Vector(const float x, const float y, const float z) {
  this->x_ = x;
  this->y_ = y;
  this->z_ = z;
}

Vector::Vector(const Vector& copyme) {
  this->x_ = copyme.x_;
  this->y_ = copyme.y_;
  this->z_ = copyme.z_;
}

Vector::~Vector() {
}

Vector &Vector::operator=(const Vector &copyme) {
  if (this != &copyme) {
    this->x_ = copyme.x_;
    this->y_ = copyme.y_;
    this->z_ = copyme.z_;
  }
  return *this;
}

Vector &Vector::operator+=(const Vector &a) {
  this->x_ += a.x_;
  this->y_ += a.y_;
  this->z_ += a.z_;
  return *this;
}

Vector &Vector::operator-=(const Vector &a) {
  this->x_ -= a.x_;
  this->y_ -= a.y_;
  this->z_ -= a.z_;
  return *this;
}

Vector operator+(const Vector &a, const Vector &b) {
  Vector tmp(a);
  tmp += b;
  return tmp;
}

Vector operator-(const Vector &a, const Vector &b) {
  Vector tmp(a);
  tmp -= b;
  return tmp;
}

float operator*(const Vector &a, const Vector &b) {
  float sum;
  sum = a.getx() * b.getx() + a.gety() * b.gety() + a.getz() * b.getz();
  return sum;
}

Vector operator*(const Vector &a, const double s) {
  Vector result((float) (a.getx() * s),
  (float) (a.gety() * s), (float) (a.getz() * s));
  return result;
}

Vector operator*(const double s, const Vector &a) {
  Vector result((float) (a.getx() * s),
  (float) (a.gety() * s), (float) (a.getz() * s));
  return result;
}

std::ostream &operator<<(std::ostream &out, const Vector &a) {
  out << "(" << a.getx() << "," << a.gety() << "," << a.getz() << ")";
  return out;
}

}  // namespace vector333
