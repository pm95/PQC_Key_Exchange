#include <math.h>
#include <stdio.h>

int mod_pow(int base, int exp, int n)
{
    int result = 1;

    for (int i = 1; i <= exp; i++)
        result = fmod(result * fmod(base, n), n);

    return result;
}

// n seed
const int n = 1993;

// g seed
const int g = 127;