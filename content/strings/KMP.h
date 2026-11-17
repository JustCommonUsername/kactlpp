/**
 * Author: Johan Sannemo, rewritten for readability
 * Date: 2016-12-15
 * License: CC0
 * Description: Prefix function: \texttt{pi[i]} = length of the longest
 * proper prefix of \texttt{s[0..i]} that is also a suffix of it
 * (abacaba -> 0010123). \texttt{findAll} returns all start positions
 * of \texttt{pattern} in \texttt{text}.
 * Smallest period of s: $p = n - \pi[n-1]$ (s is a repetition iff $p \mid n$).
 * Time: O(n)
 */
#pragma once

vi prefixFunction(const string& s) {
	ll n = SZ(s);
	vi pi(n, 0);
	fore(i, 1, n) {
		ll len = pi[i - 1]; // try to extend the previous border
		while (len > 0 && s[i] != s[len]) len = pi[len - 1];
		if (s[i] == s[len]) len++;
		pi[i] = len;
	}
	return pi;
}

vi findAll(const string& text, const string& pattern) {
	ll m = SZ(pattern);
	vi pi = prefixFunction(pattern + '\0' + text), res;
	fore(i, 2 * m, SZ(pi))
		if (pi[i] == m) res.pb(i - 2 * m);
	return res;
}
