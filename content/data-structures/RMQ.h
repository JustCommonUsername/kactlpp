/**
 * Author: Johan Sannemo, pajenegod, rewritten for readability
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Sparse table for range minimum queries on a static
 * array. Works for any idempotent operation (min, max, gcd, and, or).
 * Usage: SparseTable st(a); st.query(l, r); // min of a[l..r-1]
 * Time: $O(N \log N)$ build, $O(1)$ query.
 */
#pragma once

struct SparseTable {
	// table[k][i] = min of a[i .. i + 2^k - 1]
	vector<vi> table;
	SparseTable(vi& a) {
		ll n = SZ(a);
		table.pb(a);
		for (ll k = 1; (1LL << k) <= n; k++) {
			ll half = 1LL << (k - 1);
			table.pb(vi(n - (1LL << k) + 1));
			fore(i, 0, SZ(table[k]))
				table[k][i] = min(table[k-1][i], table[k-1][i + half]);
		}
	}

	// min of a[l .. r - 1], requires l < r
	ll query(ll l, ll r) {
		ll k = __lg(r - l);
		return min(table[k][l], table[k][r - (1LL << k)]);
	}
};
