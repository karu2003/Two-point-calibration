#include "_atoi.h"
int _atoi(const char *str) {
  // Initialize result
  int res = 0;
  // Initialize sign as positive
  int sign = 1;
  // Initialize index of first digit
  int i = 0;
  // If number is negative,
  // then update sign
  if (str[0] == '-') {
    sign = -1;
    // Also update index of first digit
    i++;
  }
  // Iterate through all digits
  // and update the result
  for (; str[i] != '\0'; ++i) {
    if (str[i] == '.') {
      break;
    }
    res = res * 10 + str[i] - '0';
  }
  // Return result with sign
  return sign * res;
}