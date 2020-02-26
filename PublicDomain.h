#include <math.h>
#include <stdio.h>

// recursive form of modular exponentiation
double mod_pow_recursive(double base, double exp, double n)
{
    // base case
    if (exp == 1)
        return fmod(pow(base, 1), n);
    return fmod(fmod(mod_pow_recursive(base, exp - 1, n), n) * fmod(pow(base, 1), n), n);
}

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
const double n = 1993;

// g seed
const double g = 127;