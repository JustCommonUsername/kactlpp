/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Interval DP, example: merge adjacent piles, merging costs
 * the total size. \texttt{dp[l][r]} = min cost to merge \texttt{a[l..r]} into
 * one pile; try every split point k. Process intervals by increasing
 * length so that smaller intervals are already solved. Same pattern:
 * matrix chain multiplication, optimal BST, palindrome removal.
 * Time: $O(N^3)$
 */
#pragma once

ll mergePiles(vi& a) {
	ll n = SZ(a);
	vi pre(n + 1, 0);
	fore(i, 0, n) pre[i + 1] = pre[i] + a[i];
	vector<vi> dp(n, vi(n, 0));
	fore(len, 2, n + 1) fore(l, 0, n - len + 1) {
		ll r = l + len - 1;
		dp[l][r] = LLONG_MAX;
		fore(k, l, r) // left part [l, k], right part [k + 1, r]
			dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r]);
		dp[l][r] += pre[r + 1] - pre[l];
	}
	return n == 0 ? 0 : dp[0][n - 1];
}
