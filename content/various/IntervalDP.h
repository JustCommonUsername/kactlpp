/**
 * Author: team
 * Date: 2026-11-23
 * License: CC0
 * Source: folklore
 * Description: Interval DP: dp[i][j] = answer for the interval a[i..j].
 * Solve intervals by increasing length, so the shorter ones inside are
 * already done. Usually: try every split point k into [i, k] and
 * [k + 1, j], and/or use that the two ends a[i], a[j] are equal.
 * Same pattern: matrix chain multiplication, optimal BST.
 * Usage: a.insert(a.begin(), 0); // now 1-indexed a[1..n]
 * merge_piles(a, n); palindrome_removal(a, n);
 * Time: $O(N^3)$
 */
#pragma once

// merge adjacent piles into one; a merge costs the total size
ll merge_piles(vi& a, ll n) {
	vi pre(n + 1, 0);
	for (ll i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];

	vector<vi> dp(n + 2, vi(n + 2, LLONG_MAX));
	for (ll i = 1; i <= n; i++) dp[i][i] = 0; // one pile

	for (ll len = 2; len <= n; len++) {
		for (ll i = 1; i + len - 1 <= n; i++) {
			ll j = i + len - 1;

			for (ll k = i; k < j; k++) { // [i, k] + [k + 1, j]
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
			}

			dp[i][j] += pre[j] - pre[i - 1]; // the last merge
		}
	}
	return dp[1][n];
}

// min steps to delete all, a step deletes a palindrome
ll palindrome_removal(vi& a, ll n) {
	vector<vi> dp(n + 2, vi(n + 2, n + 1)); // n + 1 = infinity
	for (ll i = 1; i <= n; i++) {
		dp[i][i - 1] = 1; // equal pair costs 1
		dp[i][i] = 1;
	}

	for (ll len = 2; len <= n; len++) {
		for (ll i = 1; i + len - 1 <= n; i++) {
			ll j = i + len - 1;

			for (ll k = i; k < j; k++) { // split into two parts
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
			}

			if (a[i] == a[j]) { // ends join the last palindrome
				dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
			}
		}
	}
	return dp[1][n];
}
