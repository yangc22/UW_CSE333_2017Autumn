#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv) {
  int num;
  cout << "Which positive integer would you like me to factorize? ";
  cin >> num;
  for (int i = 1; i <= num; i++) {
    if (num % i ==0) {
      cout << i << " ";
    }
  }
  cout << endl;
  return EXIT_SUCCESS;  
}
