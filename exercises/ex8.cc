// Copyright[2017]<Chaoyi Yang> [legalcpoyright]
// Name: Chaoyi Yang
// Student ID: 1465947
// UW Email: yangc22@uw.edu

#include <iostream>
#include <cstdlib>

using namespace std;

// recursive method to search for the factor
// if we find a factor i of the num, we just start
// the next search from i + 1 to num / i - 1.
void search(int num, int start, int end) {
  for (int i = start; i <= end; i++) {
    if ((num % i) == 0) {
      cout << i << " ";
      search(num, i + 1, (num / i) - 1);
      cout << (num / i) << " ";
      return;
    }
  }
  return;
}

int main(int argc, char **argv) {
  int num;
  cout << "Which positive integer would you like me to factorize? ";

  // store the user input number
  cin >> num;

  // sanity check
  if (num <= 0) {
    cout << "The number should be positive!" << endl;
    return EXIT_FAILURE;
  }

  // the first search starts from 1 to num
  search(num, 1, num);
  cout << endl;
  return EXIT_SUCCESS;
}
