import sys

sys.setrecursionlimit(100000000)


def mod_pow(a, k, n):
    if k == 1:
        return pow(a, k) % n
    return (mod_pow(a, k-1, n) % n)*(pow(a, 1) % n) % n


a = 127
k = 1523
n = 1993


print(mod_pow(a, k, n))
