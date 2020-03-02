#include <stdio.h>
#include <math.h>

// client/server communication parameters
#define MAX 80
#define PORT 8080

int mod_exp(int base, int exp, int N)
{
    int result = 1;
    for (int i = 1; i <= exp; i++)
        result = fmod(result * fmod(base, N), N);
    return result;
}
