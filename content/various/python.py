# ---------- Input / output ----------
import sys
input = sys.stdin.readline          # fast; strip() the line if needed
def ints(): return list(map(int, input().split()))
# n, m = map(int, input().split());  a = ints()
# whole input at once (fastest): it = iter(sys.stdin.buffer.read().split())
#   n = int(next(it))
out = []                            # collect output, print once at the end
out.append(str(42))
sys.stdout.write("\n".join(out) + "\n")
print(*[1, 2, 3])                   # 1 2 3 (space separated)
print(f"{3.14159265:.6f}", f"{7:05d}", f"{255:b}", f"{255:x}")

# ---------- Numbers ----------
from math import gcd, lcm, isqrt, comb, perm, factorial, inf, log2
MOD = 10**9 + 7
x = 2**200 + 1                      # ints never overflow
pow(3, 10**18, MOD)                 # fast modular power
pow(3, -1, MOD)                     # modular inverse (MOD prime or coprime)
-7 // 2 == -4 and -7 % 2 == 1       # floor division, never negative mod
divmod(17, 5) == (3, 2)
isqrt(10**30)                       # exact floor(sqrt), no float error
int("1011", 2) == 11 and bin(11) == "0b1011"
(11).bit_count() == 3               # popcount (Python 3.10+)
(11).bit_length() == 4              # highest bit + 1
from fractions import Fraction      # exact rationals
Fraction(1, 3) + Fraction(1, 6) == Fraction(1, 2)
from decimal import Decimal, getcontext
getcontext().prec = 50              # 50 significant digits
Decimal(2).sqrt()

# ---------- Lists, strings, 2D ----------
grid = [[0] * 5 for _ in range(3)]  # NOT [[0]*5]*3 (shares the rows)
a = [5, 1, 4, 1]
a.sort(); b = sorted(a, reverse=True)
pairs = [(2, "b"), (1, "z"), (2, "a")]
pairs.sort(key=lambda p: (-p[0], p[1]))   # by first desc, then second
a[::-1]; a[1:3]; a.index(4); a.count(1)
s = "hello world"
s.split(); s[::-1]; s.upper(); s.find("lo"); s.replace("l", "L")
"".join(sorted(s)); list(s); ord("a"); chr(97)
s.isdigit(); s.isalpha(); s.startswith("he"); s.strip()

# ---------- Collections ----------
from collections import deque, defaultdict, Counter
q = deque([1, 2]); q.appendleft(0); q.append(3); q.popleft(); q.pop()
g = defaultdict(list); g[1].append(2)     # adjacency list
cnt = Counter("abracadabra")              # cnt["a"] == 5
cnt.most_common(2)                        # [('a', 5), ('b', 2)]
d = {}; d[(1, 2)] = 3                     # tuples work as keys
d.get((5, 5), 0)                          # default if missing
st = {1, 2}; st.add(3); st.discard(9); 3 in st
st | {4}; st & {1}; st - {2}               # union, intersection, difference

# ---------- Heap (min-heap only) ----------
import heapq
h = []
heapq.heappush(h, (3, "c")); heapq.heappush(h, (1, "a"))
dist, node = heapq.heappop(h)             # smallest tuple: (1, 'a')
heapq.heappush(h, (-5, "max"))            # max-heap: push negated keys
heapq.heapify(a)                          # list -> heap in O(n)
heapq.nsmallest(2, [5, 1, 4])

# ---------- Binary search on sorted lists ----------
from bisect import bisect_left, bisect_right, insort
v = [1, 2, 2, 4]
bisect_left(v, 2) == 1                    # first index with v[i] >= 2
bisect_right(v, 2) == 3                   # first index with v[i] > 2
insort(v, 3)                              # insert keeping order, O(n)
lo, hi = 0, 10**18                        # first x with ok(x):
ok = lambda m: m * m >= 10**12
while lo < hi:
    mid = (lo + hi) // 2
    if ok(mid): hi = mid
    else: lo = mid + 1

# ---------- itertools, functools ----------
from itertools import permutations, combinations, product, accumulate
list(permutations([1, 2, 3]))             # all 6 orders
list(combinations([1, 2, 3], 2))          # (1,2) (1,3) (2,3)
list(product([0, 1], repeat=3))           # all bitstrings of length 3
list(accumulate([1, 2, 3]))               # prefix sums [1, 3, 6]
from functools import cache
@cache                                    # memoized recursion
def fib(n): return n if n < 2 else fib(n - 1) + fib(n - 2)
fib(90)

# ---------- Deep recursion ----------
# setrecursionlimit alone crashes on deep recursion (C stack);
# run main in a thread with a big stack instead:
import threading
sys.setrecursionlimit(1 << 25)
threading.stack_size(1 << 27)
def main(): pass                          # solve here
threading.Thread(target=main).start()
