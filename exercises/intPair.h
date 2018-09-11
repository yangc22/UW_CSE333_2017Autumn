// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#ifndef _INTPAIR_H_
#define _INTPAIR_H_

class intPair {
  public:
    intPair(const int x, const int y);  // constructor
    void get(int *x, int *y);  // get the integer pair of the intPair
    void set(const int x, const int y);  // set the integer pair of the intPair

  private:
    int x_;  // data member
    int y_;  // data member
};  // class intPair

#endif  // _INTPAIR_H_
