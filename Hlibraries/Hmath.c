#include "Hmath.h"


bool isprime(int num);
bool iscoprime(long long totient, long long e);
long long extended_Euclidean(long long e, long long totient);
bool isEven(long long num);
long long max(long long a, long long b);
long long min(long long a, long long b);
long long standard_Euclidean(long long num1, long long num2);
const long long E_standard = 65537;


bool isprime(int num){
    if(num <= 1) return false;
    if(num == 2 || num == 3) return true;
    if(num % 2 == 0) return false;

    for(int i = 3; (long long)i*i <= num; i += 2){
        if(num % i == 0) return false;
    }
    return true;
}

bool iscoprime(long long totient, long long e){
    if(e == 0) return false;
    if(e == 1) return true;
    long long remainder = 1;
    while(remainder != 0){
        remainder = totient % e;
        totient = e;
        e = remainder;
        if(remainder == 1) return true;
    }
    return false;
}

long long standard_Euclidean(long long num1, long long num2){
    if(num1 % num2 == 0) return num2;
    return standard_Euclidean(num2, num1 % num2);
}

bool isEven(long long num){
    if(num % 2 == 0) return true;
    return false;
}

long long max(long long a, long long b){
    if(a > b) return a;
    return b;
}

long long min(long long a, long long b){
    if(a < b) return a;
    return b;
}

long long extended_Euclidean(long long e, long long totient){
    long long previous1 = 0, previous2 = 1, current1 = 1, current2 = 0;
    long long save_totient = totient;

    while(e != 0){
        long long division = totient / e;
        long long remainder = totient % e;

        long long next1 = previous1 - current1*division;
        long long next2 = previous2 - current2*division;
        totient = e;
        e = remainder;
        previous1 = current1;
        previous2 = current2;
        current1 = next1;
        current2 = next2;
    }
    if(previous1 < 0) return previous1 + save_totient;
    return previous1;
}