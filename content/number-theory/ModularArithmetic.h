/**
 * Author: Lukas Polacek, rewritten for readability
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Modular arithmetic for a prime modulus \texttt{MOD}:
 * fast power, inverse (Fermat: $a^{-1} = a^{p-2}$) and binomial
 * coefficients with precomputed factorials. Call \texttt{init\_factorials()} first.
 * If the modulus is not prime use \texttt{mod\_inverse} from euclid.h.
 * Always reduce negative values with \texttt{((x \% MOD) + MOD) \% MOD}.
 * Usage: init_factorials(); ll c = ncr(10, 3); // 120
 * Time: $O(\log e)$ for power/inverse, $O(1)$ for ncr.
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

// fact[i] = i!, inv_fact[i] = 1 / i!
vi fact(MAXN), inv_fact(MAXN);
void init_factorials() {
	fact[0] = 1;
	fore(i, 1, MAXN) fact[i] = fact[i - 1] * i % MOD;
	inv_fact[MAXN - 1] = inverse(fact[MAXN - 1]);
	for (ll i = MAXN - 1; i > 0; i--) inv_fact[i - 1] = inv_fact[i] * i % MOD;
}

// number of ways to choose k out of n
ll ncr(ll n, ll k) {
	if (k < 0 || k > n) return 0;
	return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}
