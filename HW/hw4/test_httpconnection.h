/*
 * Copyright ©2017 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Autumn Quarter 2017 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#ifndef _HW4_TEST_HTTPCONNECTION_H_
#define _HW4_TEST_HTTPCONNECTION_H_

#include "gtest/gtest.h"

namespace hw4 {

class Test_HttpConnection : public ::testing::Test {
 protected:
  Test_HttpConnection() {
    // Do set-up work for each test here.
  }

  virtual ~Test_HttpConnection() {
    // Do clean-up work for each test here.
  }

  virtual void SetUp() {
    // Code here will be called after the constructor and
    // right before each test.
  }

  virtual void TearDown() {
    // Code here will be called after each test and
    // right before the destructor.
  }

  static void SetUpTestCase() {
    // Code here will be called once for the entire
    // text fixture.  Note it is a static member function
    // (i.e., a class method, not an object instance method).
  }

  static void TearDownTestCase() {
    // Code here will be called once for the entire
    // text fixture.  Note it is a static member function
    // (i.e., a class method, not an object instance method).
  }

  // Objects declared here can be used by all tests in
  // the test case.
};  // class Test_HttpConnection

}  // namespace hw4

#endif  // _HW4_TEST_HTTPCONNECTION_H_