/**
 * Author: team, rewritten for readability
 * Date: 2026-11-19
 * License: CC0
 * Source: folklore
 * Description: Merge sort tree: a segment tree where every node stores
 * the sorted values of its range. Static array (no updates).
 * \texttt{count(l, r, lo, hi)} = number of i in $[l, r)$ with lo $\le$ a[i] $\le$ hi.
 * Number of elements < x in a range: \texttt{count(l, r, LLONG\_MIN, x - 1)}.
 * k-th smallest in a range: binary search on x with this count.
 * Usage: MergeSortTree mst(a); mst.count(2, 7, 10, 20);
 * Time: $O(N \log N)$ build and memory, $O(\log^2 N)$ per query.
 */
#pragma once

struct MergeSortTree {
	// tree[n + i] = {a[i]}, tree[v] = sorted(tree[2v] + tree[2v+1])
	ll n;
	vector<vi> tree;
	MergeSortTree(vi& a) : n(SZ(a)), tree(2 * n) {
		fore(i, 0, n) tree[n + i] = {a[i]};
		for (ll v = n - 1; v >= 1; v--) {
			vi& L = tree[2 * v];
			vi& R = tree[2 * v + 1];
			tree[v].resize(SZ(L) + SZ(R));
			merge(ALL(L), ALL(R), tree[v].begin());
		}
	}

	// values in [lo, hi] inside one sorted node
	ll count_node(vi& vals, ll lo, ll hi) {
		return upper_bound(ALL(vals), hi) - lower_bound(ALL(vals), lo);
	}

	// number of i in [l, r) with lo <= a[i] <= hi
	ll count(ll l, ll r, ll lo, ll hi) {
		ll res = 0;
		if (lo > hi) return 0; // else upper - lower would be negative
		for (l += n, r += n; l < r; l /= 2, r /= 2) {
			if (l % 2 == 1) res += count_node(tree[l++], lo, hi);
			if (r % 2 == 1) res += count_node(tree[--r], lo, hi);
		}
		return res;
	}
};
