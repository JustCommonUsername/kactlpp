/**
 * Author: Lukas Polacek, rewritten for readability
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Fenwick tree (binary indexed tree). Point add and
 * prefix sum. Internally 1-based, the interface is 0-based.
 * For range add + point query: \texttt{add(l, x), add(r, -x)}
 * and the value at $i$ is \texttt{prefixSum(i + 1)}.
 * Usage: FenwickTree ft(n); ft.add(i, 5); ft.rangeSum(l, r);
 * Time: O(\log N) per operation.
 */
#pragma once

struct FenwickTree {
	// bit[i] = sum of a[i - lowbit(i) + 1 .. i] (1-based)
	ll n;
	vi bit;
	FenwickTree(ll N) : n(N), bit(N + 1, 0) {}

	// a[pos] += delta
	void add(ll pos, ll delta) {
		for (pos++; pos <= n; pos += pos & -pos) bit[pos] += delta;
	}

	// a[0] + ... + a[r - 1]
	ll prefixSum(ll r) {
		ll res = 0;
		for (; r > 0; r -= r & -r) res += bit[r];
		return res;
	}

	// a[l] + ... + a[r - 1]
	ll rangeSum(ll l, ll r) { return prefixSum(r) - prefixSum(l); }
};
