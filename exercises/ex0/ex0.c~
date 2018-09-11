#include <stdio.h>

int main(int argc, char** argv) {
  // If the number of input parameters is not right, print error message.
  if (argc != 2) {
    printf("The number of inputs is not right! It should be ./ex0 integer\n.");
    return 1;
  }
  
  int num;

  // If the input is not an integer, print error message.
  if (sscanf(argv[1], "%d", &num) != 1) {
    printf("The input should be an integer!\n");
    return 1;
  }
  
  // If the input is negative, print error message.
  if (num < 0) {
    printf("The input can not be negative!\n");
    return 1;
  }

  double result = 3.0;
  int sign = -1;
  
  // calculate the value of each term.
  for (int i = 1; i <= num; i++) {
    sign *= -1;
    double term = sign * (4.0 / ((2 * i) * (2 * i + 1) * (2 * i + 2)));
    result += term;
  }
  printf("Our estimate of Pi is %.20f\n", result);
  return 0;
}
