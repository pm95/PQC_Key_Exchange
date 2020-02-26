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
    Alice.private_key = 1523;
    Bob.private_key = 1597;

    // calculate public keys for Alice and Bob
    Alice.public_key = mod_pow(g, Alice.private_key, n);
    Bob.public_key = mod_pow(g, Bob.private_key, n);

    // calculate shared secret for Alice and Bob
    Alice.shared_secret = mod_pow(Bob.public_key, Alice.private_key, n);
    Bob.shared_secret = mod_pow(Alice.public_key, Bob.private_key, n);

    printf("\n\n");
    printf("n: %d\ng: %d\n\nAlice private key, a: %d\nBob private key, b: %d\n\n", n, g, Alice.private_key, Bob.private_key);
    printf("Alice public key: %d\nBob public key: %d\n\n", Alice.public_key, Bob.public_key);
    printf("Alice SS: %d\nBob SS: %d\n\n", Alice.shared_secret, Bob.shared_secret);
    printf("\n\n");
    return 0;
}