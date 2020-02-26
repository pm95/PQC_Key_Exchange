#include <stdio.h>

#include "PublicDomain.h"

int main()
{
    printf("\n\n");

    // ***** ALICE PRIVATE DOMAIN *****
    double a = 1523;

    // ***** BOB PRIVATE DOMAIN *****
    double b = 1597;

    printf("n: %f\ng: %f\nAlice private key, a: %f\nBob private key, b: %f\n\n", n, g, a, b);

    // pubic keys from alice and bob
    double A = mod_pow(g, a, n);
    double B = mod_pow(g, b, n);

    printf("Alice public key: %f\nBob public key: %f\n\n", A, B);

    // // shared secret computation for alice and bob
    // // ***** ALICE PRIVATE DOMAIN *****
    // double a_ss = mod_pow(B, a, n);

    // // ***** BOB PRIVATE DOMAIN *****
    // double b_ss = mod_pow(A, b, n);

    // printf("Alice SS: %f\nBob SS: %f\n\n", a_ss, b_ss);

    // printf("\n\n");
    return 0;
}