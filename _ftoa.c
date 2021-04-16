// C program for implementation of ftoa()
#include <math.h>
#include <stdio.h>

// Reverses a string 'str' of length 'len'
void reverse(char *str, int len) {
  int i = 0, j = len - 1, temp;
  while (i < j) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i++;
    j--;
  }
}

// Converts a given integer x to string str[].
// d is the number of digits required in the output.
// If d is more than the number of digits in x,
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d) {
  int i = 0;
  while (x) {
    str[i++] = (x % 10) + '0';
    x = x / 10;
  }

  // If number of digits required is more, then
  // add 0s at the beginning
  while (i < d)
    str[i++] = '0';
  reverse(str, i);
  str[i] = '\0';
  return i;
}

void _ftoa(float n, char *res, int afterpoint) {
  if (n < 0.0) {
    res[0] = '-';
    res += 1;
    n *= -1;
  }
  // Extract integer part
  int ipart = (int)n;

  // Extract floating part
  float fpart = n - (float)ipart;

  // convert integer part to string
  int i = intToStr(ipart, res, 0);

  // check for display option after point
  if (afterpoint != 0) {
    res[i] = '.'; // add dot

    // Get the value of fraction part upto given no.
    // of points after dot. The third parameter
    // is needed to handle cases like 233.007
    fpart = fpart * pow(10, afterpoint);

    intToStr((int)fpart, res + i + 1, afterpoint);
  }
}

int myAtoi(char *str) {
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
  for (; str[i] != '\0'; ++i)
    res = res * 10 + str[i] - '0';
  // Return result with sign
  return sign * res;
}
