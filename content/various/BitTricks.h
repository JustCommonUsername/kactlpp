/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Bit operations and \texttt{bitset}. Use \texttt{1LL << i} for
 * bits $\ge 31$, and the \texttt{ll} versions of builtins.
 * A bitset of size N does AND/OR/XOR/shift 64x faster than a
 * \texttt{bool} array: subset sum or reachability in $O(N^2 / 64)$.
 * Sum over subsets (SOS): \texttt{f[mask]} = sum of \texttt{a[sub]} over all submasks, $O(2^n n)$.
 */
#pragma once

void bitExamples(ll x, ll i, ll m) {
	bool isSet = x >> i & 1;
	x |= 1LL << i;              // set bit i
	x &= ~(1LL << i);           // clear bit i
	x ^= 1LL << i;              // toggle bit i
	ll lowest = x & -x;         // lowest set bit (as a value)
	ll ones = __builtin_popcountll(x);
	ll trailing = __builtin_ctzll(x);  // x != 0
	ll highBit = 63 - __builtin_clzll(x); // = __lg(x), x != 0
	bool powerOfTwo = x > 0 && (x & (x - 1)) == 0;
	// all submasks of m, including m and 0: O(3^n) over all m
	for (ll s = m; ; s = (s - 1) & m) {
		/* use s */
		if (s == 0) break;
	}
	// next bigger number with the same popcount (x > 0)
	ll c = x & -x, r = x + c, next = (((r ^ x) >> 2) / c) | r;
	(void)isSet, (void)lowest, (void)ones, (void)trailing;
	(void)highBit, (void)powerOfTwo, (void)next;
}

vi sumOverSubsets(vi a, ll n) { // a has size 2^n
	fore(b, 0, n) fore(mask, 0, 1LL << n)
		if (mask >> b & 1) a[mask] += a[mask ^ (1LL << b)];
	return a;
}

const ll MAXS = 100001;
// reachable[s] = some subset of w has sum s
bitset<MAXS> subsetSums(vi& w) {
	bitset<MAXS> reachable;
	reachable[0] = 1;
	for (ll x : w) reachable |= reachable << x;
	return reachable; // .count(), ._Find_first(), ._Find_next(i)
}
