#include <stdio.h>
#include <math.h>

int main()
{
    printf("\n\n");

    // ***** ALICE PRIVATE DOMAIN *****
    double a = 1523;

    // ***** BOB PRIVATE DOMAIN *****
    double b = 1597;

    // ***** PUBLIC DOMAIN *****
    // n seed
    double n = 1993;

    // g seed
    double g = 127;

    printf("n: %f\ng: %f\nAlice private key, a: %f\nBob private key, b: %f\n\n", n, g, a, b);

    // pubic keys from alice and bob
    double A = pow(g, a);
    double B = pow(g, b);

    printf("Alice public key: %f\nBob public key: %f\n\n", A, B);

    // shared secret computation for alice and bob
    // ***** ALICE PRIVATE DOMAIN *****
    double a_ss = fmod(pow(B, a), n);

    // ***** BOB PRIVATE DOMAIN *****
    double b_ss = fmod(pow(A, b), n);

    printf("Alice SS: %f\nBob SS: %f\n\n", a_ss, b_ss);

    printf("\n\n");
    return 0;
}