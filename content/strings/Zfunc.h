/**
 * Author: chilli, rewritten for readability
 * License: CC0
 * Description: \texttt{z[i]} = length of the longest common prefix of
 * \texttt{s} and \texttt{s[i..]}, with \texttt{z[0] = 0} (abacaba -> 0010301).
 * Pattern matching: compute z of \texttt{pattern + '\#' + text}.
 * Time: O(n)
 */
#pragma once

vi z_function(const string& s) {
	ll n = SZ(s);
	vi z(n, 0);
	// [l, r) = rightmost segment that matches a prefix of s
	ll l = 0, r = 0;
	fore(i, 1, n) {
		if (i < r) z[i] = min(r - i, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
		if (i + z[i] > r) l = i, r = i + z[i];
	}
	return z;
}
