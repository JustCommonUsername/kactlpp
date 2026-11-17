/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Classic two-string DPs. \texttt{dp[i][j]} is the answer for
 * the prefixes \texttt{a[0..i-1]} and \texttt{b[0..j-1]}.
 * Edit distance: min number of insert/delete/replace to turn a into b.
 * \texttt{lcs}: longest common subsequence (walk back through dp to get it).
 * Time: O(|a| |b|)
 */
#pragma once

ll editDistance(const string& a, const string& b) {
	ll n = SZ(a), m = SZ(b);
	vector<vi> dp(n + 1, vi(m + 1));
	fore(i, 0, n + 1) dp[i][0] = i; // delete everything
	fore(j, 0, m + 1) dp[0][j] = j; // insert everything
	fore(i, 1, n + 1) fore(j, 1, m + 1) {
		ll replace = dp[i-1][j-1] + (a[i-1] != b[j-1]);
		dp[i][j] = min({replace, dp[i-1][j] + 1, dp[i][j-1] + 1});
	}
	return dp[n][m];
}

ll lcs(const string& a, const string& b) {
	ll n = SZ(a), m = SZ(b);
	vector<vi> dp(n + 1, vi(m + 1, 0));
	fore(i, 1, n + 1) fore(j, 1, m + 1) {
		if (a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
		else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
	}
	return dp[n][m];
}
