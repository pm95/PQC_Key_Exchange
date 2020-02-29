#include <stdio.h>
#include <math.h>

struct Person
{
    //private variable, do not peak
    int private_key;

    // public key
    int public_key;

    // shared secret with another person
    int shared_secret;
};

int mod_pow(int base, int exp, int n)
{
    int result = 1;
    for (int i = 1; i <= exp; i++)
        result = fmod(result * fmod(base, n), n);
    return result;
}

#define n 1993
#define g 127