#ifndef HMATH_H
#define HMATH_H

#include <stdbool.h>
extern const long long E_standard;

bool isprime(int num);
bool iscoprime(long long totient, long long e);
long long extended_Euclidean(long long e, long long totient);
bool isEven(long long num);
long long max(long long a, long long b);
long long min(long long a, long long b);
long long standard_Euclidean(long long num1, long long num2);

#endif