// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include <iostream>
#include <map>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
  // sanity check
  if (argc != 2) {
    cout << "Usage(), ./ex12a filename!" << endl;
    exit(EXIT_FAILURE);
  }

  string in;
  ifstream input(argv[1]);
  map<string, int> m;
  map<string, int>::iterator it;

  // process the file input
  input >> in;
  while (input.good()) {
    it = m.find(in);
    if (it != m.end()) {
      int num = m[in];
      m[in] = (num + 1);
    } else {
      m[in] = 1;
    }
    input >> in;
  }

  // print the map
  for (auto const &e : m) {
    cout << e.first << " " << e.second << endl;
  }
  return EXIT_SUCCESS;
}
