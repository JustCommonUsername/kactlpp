/**
 * Author: Lukas Polacek, rewritten for readability
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Modular arithmetic for a prime modulus \texttt{MOD}:
 * fast power, inverse (Fermat: $a^{-1} = a^{p-2}$) and binomial
 * coefficients with precomputed factorials. Call \texttt{initFactorials()} first.
 * If the modulus is not prime use \texttt{modInverse} from euclid.h.
 * Always reduce negative values with \texttt{((x \% MOD) + MOD) \% MOD}.
 * Usage: initFactorials(); ll c = nCr(10, 3); // 120
 * Time: $O(\log e)$ for power/inverse, $O(1)$ for nCr.
 */
#pragma once

const ll MOD = 1e9 + 7;
const ll MAXN = 1e6 + 5;

// base^exp mod MOD
ll power(ll base, ll exp) {
	ll res = 1;
	base %= MOD;
	while (exp > 0) {
		if (exp & 1) res = res * base % MOD;
		base = base * base % MOD;
		exp >>= 1;
	}
	return res;
}

ll inverse(ll a) { return power(a, MOD - 2); }

// fact[i] = i!, invFact[i] = 1 / i!
vi fact(MAXN), invFact(MAXN);
void initFactorials() {
	fact[0] = 1;
	fore(i, 1, MAXN) fact[i] = fact[i - 1] * i % MOD;
	invFact[MAXN - 1] = inverse(fact[MAXN - 1]);
	for (ll i = MAXN - 1; i > 0; i--) invFact[i - 1] = invFact[i] * i % MOD;
}

// number of ways to choose k out of n
ll nCr(ll n, ll k) {
	if (k < 0 || k > n) return 0;
	return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}
