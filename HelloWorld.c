#include <stdio.h>

#include "PublicDomain.h"

int main()
{
    printf("\n\n");

    // ***** ALICE PRIVATE DOMAIN *****
    int a = 1523;

    // ***** BOB PRIVATE DOMAIN *****
    int b = 1597;

    printf("n: %d\ng: %d\n\nAlice private key, a: %d\nBob private key, b: %d\n\n", n, g, a, b);

    // pubic keys from alice and bob
    int A = mod_pow(g, a, n);
    int B = mod_pow(g, b, n);

    printf("Alice public key: %d\nBob public key: %d\n\n", A, B);

    // // shared secret computation for alice and bob
    // ***** ALICE PRIVATE DOMAIN *****
    int a_ss = mod_pow(B, a, n);

    // ***** BOB PRIVATE DOMAIN *****
    int b_ss = mod_pow(A, b, n);

    printf("Alice SS: %d\nBob SS: %d\n\n", a_ss, b_ss);

    printf("\n\n");
    return 0;
}