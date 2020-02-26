import sys

sys.setrecursionlimit(100000000)


def mod_pow_memo(a, k, n):
    base_case = pow(a, 1) % n

    def mod_pow_func(a, k, n):
        if k == 1:
            return base_case
        return (mod_pow_func(a, k-1, n) % n)*(base_case) % n

    return mod_pow_func(a, k, n)


def mod_pow(a, k, n):
    if k == 1:
        return pow(a, k) % n
    return (mod_pow(a, k-1, n) % n)*(pow(a, 1) % n) % n


a = 127
k = 1523
n = 1993


print("normal: %s" % mod_pow(a, k, n))
print("memoized: %s" % mod_pow_memo(a, k, n))
