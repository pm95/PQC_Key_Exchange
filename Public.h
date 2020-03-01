#include <stdio.h>
#include <math.h>

#define n 1993
#define g 127
#define MAX 80
#define PORT 8080

struct Person
{
    //private variable, do not peak
    int private_key;

    // public key
    int public_key;

    // shared secret with another person
    int shared_secret;
};

int mod_pow(int base, int exp, int N)
{
    int result = 1;
    for (int i = 1; i <= exp; i++)
        result = fmod(result * fmod(base, N), N);
    return result;
}

// char a - '0' -> integer value of ascii char