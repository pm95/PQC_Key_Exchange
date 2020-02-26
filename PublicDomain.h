#include <math.h>
#include <stdio.h>

double mod_pow(double base, double exp, double n)
{
    double result = 1;

    for (double i = 1; i <= exp; i++)
    {
        result = fmod(result * fmod(base, n), n);
    }

    return fmod(result, n);
}

// n seed
const double n = 19908990;

// g seed
const double g = 121;