/**
 * Author: chilli, c1729, Simon Lindholm, rewritten for readability
 * Date: 2019-03-28
 * License: CC0
 * Source: Wikipedia, https://miller-rabin.appspot.com/
 * Description: Deterministic Miller-Rabin primality test for all
 * 64-bit numbers. Use it when $n$ is too big for a sieve.
 * Time: About $7 \cdot 64$ modular multiplications.
 */
#pragma once

typedef unsigned long long ull;
ull mulMod(ull a, ull b, ull m) { return (__uint128_t)a * b % m; }
ull powMod(ull b, ull e, ull m) {
	ull res = 1;
	for (b %= m; e > 0; e >>= 1, b = mulMod(b, b, m))
		if (e & 1) res = mulMod(res, b, m);
	return res;
}

bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	// n - 1 = d * 2^s with d odd
	ull d = n - 1;
	ll s = 0;
	while (d % 2 == 0) d /= 2, s++;
	for (ull a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
		ull x = powMod(a, d, n);
		if (a % n == 0 || x == 1 || x == n - 1) continue;
		bool composite = true;
		fore(i, 1, s) {
			x = mulMod(x, x, n);
			if (x == n - 1) { composite = false; break; }
		}
		if (composite) return false;
	}
	return true;
}
