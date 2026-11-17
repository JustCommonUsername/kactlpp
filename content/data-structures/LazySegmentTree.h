/**
 * Author: Simon Lindholm, rewritten for readability
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with range add and range sum.
 * For range min/max with range add: \texttt{combine} = min/max,
 * \texttt{neutral} = $\pm$inf and in \texttt{apply} do not multiply by the length.
 * For range assignment, store the assigned value in \texttt{lazy}
 * and use a flag for "no assignment".
 * Indices are 0-based, all ranges are $[l, r)$.
 * Usage: LazySegmentTree st(a); st.update(2, 5, 10); st.query(0, n);
 * Time: O(\log N) per operation.
 */
#pragma once

struct LazySegmentTree {
	// node v covers [lo, hi), children are 2v and 2v+1
	// sum[v] = real sum of the range of v (lazy[v] already applied)
	// lazy[v] = value that still has to be added to the children
	const ll neutral = 0;
	ll combine(ll a, ll b) { return a + b; }

	ll n;
	vi sum, lazy;
	LazySegmentTree(vi& a) : n(SZ(a)), sum(4 * n), lazy(4 * n) {
		build(1, 0, n, a);
	}

	void build(ll v, ll lo, ll hi, vi& a) {
		if (hi - lo == 1) { sum[v] = a[lo]; return; }
		ll mid = (lo + hi) / 2;
		build(2 * v, lo, mid, a), build(2 * v + 1, mid, hi, a);
		sum[v] = combine(sum[2 * v], sum[2 * v + 1]);
	}

	// add x to every element in the range [lo, hi) of node v
	void apply(ll v, ll lo, ll hi, ll x) {
		sum[v] += x * (hi - lo);
		lazy[v] += x;
	}

	void push(ll v, ll lo, ll hi) {
		if (lazy[v] == 0) return;
		ll mid = (lo + hi) / 2;
		apply(2 * v, lo, mid, lazy[v]);
		apply(2 * v + 1, mid, hi, lazy[v]);
		lazy[v] = 0;
	}

	void update(ll v, ll lo, ll hi, ll l, ll r, ll x) {
		if (r <= lo || hi <= l) return;
		if (l <= lo && hi <= r) { apply(v, lo, hi, x); return; }
		push(v, lo, hi);
		ll mid = (lo + hi) / 2;
		update(2 * v, lo, mid, l, r, x);
		update(2 * v + 1, mid, hi, l, r, x);
		sum[v] = combine(sum[2 * v], sum[2 * v + 1]);
	}

	ll query(ll v, ll lo, ll hi, ll l, ll r) {
		if (r <= lo || hi <= l) return neutral;
		if (l <= lo && hi <= r) return sum[v];
		push(v, lo, hi);
		ll mid = (lo + hi) / 2;
		return combine(query(2 * v, lo, mid, l, r),
		               query(2 * v + 1, mid, hi, l, r));
	}

	// a[i] += x for all i in [l, r)
	void update(ll l, ll r, ll x) { update(1, 0, n, l, r, x); }
	// a[l] + ... + a[r - 1]
	ll query(ll l, ll r) { return query(1, 0, n, l, r); }
};
