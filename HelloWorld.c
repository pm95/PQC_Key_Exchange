#include <stdio.h>
#include <math.h>

struct Person
{
    //private variable, do not peak
    int p;

    // public key
    int P;

    // shared secret with another person
    int p_ss;
};

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

int main()
{
    // structs for Alice and Bob
    struct Person Alice;
    struct Person Bob;

    // define private keys for Alice and Bob
    Alice.p = 1523;
    Bob.p = 1597;

    // calculate public keys for Alice and Bob
    Alice.P = mod_pow(g, Alice.p, n);
    Bob.P = mod_pow(g, Bob.p, n);

    // calculate shared secret for Alice and Bob
    Alice.p_ss = mod_pow(Bob.P, Alice.p, n);
    Bob.p_ss = mod_pow(Alice.P, Bob.p, n);

    printf("\n\n");
    printf("n: %d\ng: %d\n\nAlice private key, a: %d\nBob private key, b: %d\n\n", n, g, Alice.p, Bob.p);
    printf("Alice public key: %d\nBob public key: %d\n\n", Alice.P, Bob.P);
    printf("Alice SS: %d\nBob SS: %d\n\n", Alice.p_ss, Bob.p_ss);
    printf("\n\n");
    return 0;
}