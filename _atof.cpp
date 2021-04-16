// https://github.com/yuanyuanxiang
// https://github.com/Ardillo/atof/blob/master/src/MichelTest.cpp
#include "_atof.h"
#include "_atoi.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>

// double _atof(const char *src) {
//   const char *p = src;
//   while (*p && '.' != *p)
//     ++p;
//   return '.' == *p ? _atoi(src) + __atof(p) : _atoi(src);
// }

// double __atof(const char *str) {
//   const char *p = str;
//   _assert('0' == *p || '.' == *p || ('-' == *p && '0' == p[1]));
//   _assert(strlen(p) < 24);
//   static const double e[][10] = {
//       0,     1E-01, 2E-01, 3E-01, 4E-01, 5E-01, 6E-01, 7E-01, 8E-01, 9E-01, 0,     1E-02, 2E-02,
//       3E-02, 4E-02, 5E-02, 6E-02, 7E-02, 8E-02, 9E-02, 0,     1E-03, 2E-03, 3E-03, 4E-03, 5E-03,
//       6E-03, 7E-03, 8E-03, 9E-03, 0,     1E-04, 2E-04, 3E-04, 4E-04, 5E-04, 6E-04, 7E-04, 8E-04,
//       9E-04, 0,     1E-05, 2E-05, 3E-05, 4E-05, 5E-05, 6E-05, 7E-05, 8E-05, 9E-05, 0,     1E-06,
//       2E-06, 3E-06, 4E-06, 5E-06, 6E-06, 7E-06, 8E-06, 9E-06, 0,     1E-07, 2E-07, 3E-07, 4E-07,
//       5E-07, 6E-07, 7E-07, 8E-07, 9E-07, 0,     1E-08, 2E-08, 3E-08, 4E-08, 5E-08, 6E-08, 7E-08,
//       8E-08, 9E-08, 0,     1E-09, 2E-09, 3E-09, 4E-09, 5E-09, 6E-09, 7E-09, 8E-09, 9E-09, 0,
//       1E-10, 2E-10, 3E-10, 4E-10, 5E-10, 6E-10, 7E-10, 8E-10, 9E-10, 0,     1E-11, 2E-11, 3E-11,
//       4E-11, 5E-11, 6E-11, 7E-11, 8E-11, 9E-11, 0,     1E-12, 2E-12, 3E-12, 4E-12, 5E-12, 6E-12,
//       7E-12, 8E-12, 9E-12, 0,     1E-13, 2E-13, 3E-13, 4E-13, 5E-13, 6E-13, 7E-13, 8E-13, 9E-13,
//       0,     1E-14, 2E-14, 3E-14, 4E-14, 5E-14, 6E-14, 7E-14, 8E-14, 9E-14, 0,     1E-15, 2E-15,
//       3E-15, 4E-15, 5E-15, 6E-15, 7E-15, 8E-15, 9E-15, 0,     1E-16, 2E-16, 3E-16, 4E-16, 5E-16,
//       6E-16, 7E-16, 8E-16, 9E-16, 0,     1E-17, 2E-17, 3E-17, 4E-17, 5E-17, 6E-17, 7E-17, 8E-17,
//       9E-17, 0,     1E-18, 2E-18, 3E-18, 4E-18, 5E-18, 6E-18, 7E-18, 8E-18, 9E-18, 0,     1E-19,
//       2E-19, 3E-19, 4E-19, 5E-19, 6E-19, 7E-19, 8E-19, 9E-19, 0,     1E-20, 2E-20, 3E-20, 4E-20,
//       5E-20, 6E-20, 7E-20, 8E-20, 9E-20, 0,     1E-21, 2E-21, 3E-21, 4E-21, 5E-21, 6E-21, 7E-21,
//       8E-21, 9E-21, 0,     1E-22, 2E-22, 3E-22, 4E-22, 5E-22, 6E-22, 7E-22, 8E-22, 9E-22, 0,
//       1E-23, 2E-23, 3E-23, 4E-23, 5E-23, 6E-23, 7E-23, 8E-23, 9E-23, 0,     1E-24, 2E-24, 3E-24,
//       4E-24, 5E-24, 6E-24, 7E-24, 8E-24, 9E-24};
//   double s = 0;
//   const double *t = e[0];
//   const int &d = '0' == *p ? 2 : ('.' == *p ? 1 : 3);
//   for (const char *i = p + d; *i; ++i, t += 10) {
//     _assert('0' <= *i && *i <= '9');
//     s += t[*i - '0'];
//   }
//   return d < 3 ? s : -s;
// }

// double _atof(const char *s) {
//   double val, power;
//   int i, sign;

//   for (i = 0; isspace(s[i]); i++)
//     ;
//   sign = (s[i] == '-') ? -1 : 1;
//   if (s[i] == '+' || s[i] == '-')
//     i++;
//   for (val = 0.0; isdigit(s[i]); i++)
//     val = 10.0 * val + (s[i] - '0');
//   if (s[i] == '.')
//     i++;
//   for (power = 1.0; isdigit(s[i]); i++) {
//     val = 10.0 * val + (s[i] - '0');
//     power *= 10.0;
//   }
//   return sign * val / power;
// }

double _atof(const char *s) {
  double tf;
  int nc, i, neg;
  tf = 0.0;

  if (s[0] == '-') {
    neg = 1;
  } else {
    neg = 0;
  }
  /* search for decimal point */
  for (nc = neg; (isdigit(s[nc]) && (s[nc] != '.') && (s[nc] != '\0')); nc++)
    ;
  for (i = neg; ((isdigit(s[i]) || (s[i] == '.')) && (s[i] != '\0'));
       i++) { /* printf("%c %d %lf\n",s[i],nc-i,tf); */
    switch ((nc - i)) {
    case 0:
      break; /* we're at the decimal point */
    case 1:
      tf += (s[i] - '0');
      break; /* one's place */
    case 2:
      tf += (s[i] - '0') * 10;
      break;
    case 3:
      tf += (s[i] - '0') * 100;
      break;
    case 4:
      tf += (s[i] - '0') * 1000;
      break;
    case 5:
      tf += (s[i] - '0') * 10000;
      break;
    case 6:
      tf += (s[i] - '0') * 100000;
      break;
    case 7:
      tf += (s[i] - '0') * 1000000;
      break;
    case 8:
      tf += (s[i] - '0') * 10000000;
      break;
    case 9:
      tf += (s[i] - '0') * 100000000.0;
      break;
    case 10:
      tf += (s[i] - '0') * 1000000000.0;
      break;
    case 11:
      tf += (s[i] - '0') * 10000000000.0;
      break;
    case 12:
      tf += (s[i] - '0') * 100000000000.0;
      break;
    case 13:
      tf += (s[i] - '0') * 1000000000000.0;
      break;
    case 14:
      tf += (s[i] - '0') * 10000000000000.0;
      break;
    case 15:
      tf += (s[i] - '0') * 100000000000000.0;
      break;
    case 16:
      tf += (s[i] - '0') * 1000000000000000.0;
      break;
    case 17:
      tf += (s[i] - '0') * 10000000000000000.0;
      break;
    case 18:
      tf += (s[i] - '0') * 100000000000000000.0;
      break;
    case 19:
      tf += (s[i] - '0') * 1000000000000000000.0;
      break;
    case -1:
      tf += (s[i] - '0') * 0.1;
      break;
    case -2:
      tf += (s[i] - '0') * 0.01;
      break;
    case -3:
      tf += (s[i] - '0') * 0.001;
      break;
    case -4:
      tf += (s[i] - '0') * 0.0001;
      break;
    case -5:
      tf += (s[i] - '0') * 0.00001;
      break;
    case -6:
      tf += (s[i] - '0') * 0.000001;
      break;
    case -7:
      tf += (s[i] - '0') * 0.0000001;
      break;
    case -8:
      tf += (s[i] - '0') * 0.00000001;
      break;
    case -9:
      tf += (s[i] - '0') * 0.000000001;
      break;
    case -10:
      tf += (s[i] - '0') * 0.0000000001;
      break;
    case -11:
      tf += (s[i] - '0') * 0.00000000001;
      break;
    case -12:
      tf += (s[i] - '0') * 0.000000000001;
      break;
    case -13:
      tf += (s[i] - '0') * 0.0000000000001;
      break;
    case -14:
      tf += (s[i] - '0') * 0.00000000000001;
      break;
    case -15:
      tf += (s[i] - '0') * 0.000000000000001;
      break;
    case -16:
      tf += (s[i] - '0') * 0.0000000000000001;
      break;
    case -17:
      tf += (s[i] - '0') * 0.00000000000000001;
      break;
    case -18:
      tf += (s[i] - '0') * 0.000000000000000001;
      break;
    case -19:
      tf += (s[i] - '0') * 0.0000000000000000001;
      break;
    default:
      break;
    }
  }
  if (neg)
    tf *= -1.0;
  return (tf);
}
