#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cctype>
 
using namespace std;

// Read the value which is  type "T" thing from standard input stream.
// On error, exit and print error message.
template <class T> T ReadValue(istream& in);

int main(int argc, char **argv) {
  vector<double> result;
  double value;
  cout << "Enter 10 doubles:" << endl;
  for (int i = 0; i < 10; i++) {
    value = ReadValue<double>(cin);
    // cout << next << endl;
    result.push_back(value);
  }

  sort(result.begin(), result.end());

  cout << "Your sorted doubles are:" << endl;
  for (int i = 0; i < 10; i++) {
    cout << result[i] << endl;
  }

  return EXIT_SUCCESS;
}

// ReadValue implementation                                                     
template <class T> T ReadValue(istream& in) {
  T value;

  in >> value;
  if (!in.good()) {
    cerr << "The input type is not right!" << endl;
    exit(EXIT_FAILURE);
  }
  cout << "readvalue: " << value << endl;
  return value;
}
