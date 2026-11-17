/**
 * Author: Lukas Polacek, rewritten for readability
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore
 * Description: Iterative segment tree, point update and range query.
 * Change \texttt{neutral} and \texttt{combine} for other operations
 * (sum: 0 and a+b, min: LLONG\_MAX and min(a,b), gcd: 0 and gcd(a,b)).
 * Indices are 0-based, query is on $[l, r)$.
 * Usage: SegmentTree st(n); st.update(3, 7); st.query(0, n);
 * Time: O(\log N)
 */
#pragma once

struct SegmentTree {
	// tree[n + i] = a[i], tree[v] = combine(tree[2v], tree[2v+1])
	const ll neutral = LLONG_MIN;
	ll combine(ll a, ll b) { return max(a, b); }

	ll n;
	vi tree;
	SegmentTree(ll N) : n(N), tree(2 * N, neutral) {}

	// a[pos] = value
	void update(ll pos, ll value) {
		pos += n;
		tree[pos] = value;
		for (pos /= 2; pos >= 1; pos /= 2)
			tree[pos] = combine(tree[2 * pos], tree[2 * pos + 1]);
	}

	// combine of a[l], ..., a[r - 1]
	ll query(ll l, ll r) {
		ll resLeft = neutral, resRight = neutral;
		for (l += n, r += n; l < r; l /= 2, r /= 2) {
			if (l % 2 == 1) resLeft = combine(resLeft, tree[l++]);
			if (r % 2 == 1) resRight = combine(tree[--r], resRight);
		}
		return combine(resLeft, resRight);
	}
};
