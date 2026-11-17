# Python: integers are arbitrary precision -> use it for big numbers.
import sys
from fractions import Fraction      # exact rationals
from functools import cache         # memoization: @cache above a def
from math import gcd, isqrt, comb
sys.setrecursionlimit(10**6)        # deep recursion (still slow)
input = sys.stdin.readline          # fast input (keeps the '\n')
data = sys.stdin.buffer.read().split()  # or: read all tokens at once

n, m = map(int, input().split())
a = list(map(int, input().split()))
print(pow(3, 10**18, 10**9 + 7))    # fast modular power
print(pow(3, -1, 10**9 + 7))        # modular inverse
print(Fraction(1, 3) + Fraction(1, 6))  # 1/2
print(isqrt(10**30), comb(100, 50)) # exact sqrt floor, binomial
print(" ".join(map(str, a)))        # fast output of a list
