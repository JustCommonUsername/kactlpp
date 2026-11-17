/**
 * Author: Simon Lindholm, rewritten for readability
 * Date: 2019-05-22
 * License: CC0
 * Description: Chinese Remainder Theorem.
 * \texttt{crt(a, m, b, n)} returns $x$ with $x\equiv a \pmod m$, $x\equiv b \pmod n$
 * and $0 \le x < \text{lcm}(m, n)$, or -1 if there is no solution.
 * Moduli need not be coprime. For more equations, combine them one by
 * one: \texttt{(a, m) = (crt(a, m, b, n), lcm(m, n))}.
 * Assumes $\text{lcm}(m, n) < 2^{62}$.
 * Time: $\log(n)$
 */
#pragma once

#include "euclid.h"

ll crt(ll a, ll m, ll b, ll n) {
	a = (a % m + m) % m, b = (b % n + n) % n;
	ll p, q;
	ll g = extGcd(m, n, p, q); // m*p + n*q = g
	if ((b - a) % g != 0) return -1;
	ll lcm = m / g * n;
	// x = a + m * t  with  m * t = b - a (mod n)
	ll t = (__int128)((b - a) / g) * p % (n / g);
	ll x = (a + (__int128)m * t) % lcm;
	return (x + lcm) % lcm;
}
