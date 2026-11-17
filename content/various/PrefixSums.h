/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Prefix sums: \texttt{pre[i]} = a[0] + ... + a[i-1], so the sum of
 * \texttt{a[l..r-1]} is \texttt{pre[r] - pre[l]}. 2D: sum of the rectangle
 * rows $[r_1, r_2)$, columns $[c_1, c_2)$ by inclusion-exclusion.
 * Difference array: add x to \texttt{a[l..r-1]} with \texttt{diff[l] += x,
 * diff[r] -= x}, then a = prefix sums of diff.
 * Two pointers: longest window with sum $\le$ S (needs $a_i \ge 0$).
 * Time: O(N) build, O(1) per query.
 */
#pragma once

struct Prefix2D {
	vector<vi> pre; // pre[i][j] = sum of the rectangle [0, i) x [0, j)
	Prefix2D(vector<vi>& a) {
		ll R = SZ(a), C = SZ(a[0]);
		pre.assign(R + 1, vi(C + 1, 0));
		fore(i, 0, R) fore(j, 0, C)
			pre[i+1][j+1] = a[i][j] + pre[i][j+1] + pre[i+1][j] - pre[i][j];
	}
	ll sum(ll r1, ll c1, ll r2, ll c2) {
		return pre[r2][c2] - pre[r1][c2] - pre[r2][c1] + pre[r1][c1];
	}
};

ll longestWindow(vi& a, ll S) {
	ll best = 0, sum = 0, l = 0;
	fore(r, 0, SZ(a)) {
		sum += a[r]; // window is a[l..r]
		while (sum > S) sum -= a[l++];
		best = max(best, r - l + 1);
	}
	return best;
}
