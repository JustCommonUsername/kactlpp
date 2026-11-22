/**
 * Author: Unknown, rewritten for readability
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Extended Euclid: finds $x, y$ with $ax + by = \gcd(a, b)$.
 * \texttt{mod\_inverse(a, m)} works for any modulus m (not only primes)
 * and returns -1 if $\gcd(a, m) \neq 1$. For just the gcd use \texttt{gcd(a, b)}.
 * Time: O(\log \min(a, b))
 */
#pragma once

ll ext_gcd(ll a, ll b, ll& x, ll& y) {
	if (b == 0) { x = 1, y = 0; return a; }
	ll x1, y1;
	ll g = ext_gcd(b, a % b, x1, y1);
	// b*x1 + (a % b)*y1 = g  and  a % b = a - (a/b)*b
	x = y1;
	y = x1 - (a / b) * y1;
	return g;
}

ll mod_inverse(ll a, ll m) {
	ll x, y;
	if (ext_gcd(a, m, x, y) != 1) return -1;
	return (x % m + m) % m;
}
