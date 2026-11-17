/**
 * Author: folklore, rewritten for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: https://cp-algorithms.com/string/suffix-array.html
 * Description: \texttt{sa[i]} = start of the i-th smallest suffix of s.
 * \texttt{lcp[i]} = longest common prefix of the suffixes \texttt{sa[i]} and
 * \texttt{sa[i+1]} (Kasai). Number of distinct substrings:
 * $n(n+1)/2 - \sum lcp$. Longest repeated substring: $\max lcp$.
 * Usage: SuffixArray sa(s); sa.sa[0]; sa.lcp[0];
 * Time: $O(n \log^2 n)$ build (sort by pairs of ranks), $O(n)$ LCP.
 */
#pragma once

struct SuffixArray {
	ll n;
	vi sa, rnk, lcp;
	SuffixArray(const string& s) : n(SZ(s)), sa(n), rnk(n), lcp(max(n - 1, 0LL)) {
		fore(i, 0, n) sa[i] = i, rnk[i] = s[i];
		// sort by the first 2k characters using ranks of the first k
		for (ll k = 1; n > 0; k *= 2) {
			auto key = [&](ll i) {
				return ii(rnk[i], i + k < n ? rnk[i + k] : -1);
			};
			sort(ALL(sa), [&](ll a, ll b) { return key(a) < key(b); });
			vi newRank(n, 0);
			fore(i, 1, n)
				newRank[sa[i]] = newRank[sa[i-1]] + (key(sa[i-1]) < key(sa[i]));
			rnk = newRank;
			if (rnk[sa[n - 1]] == n - 1 || k >= n) break;
		}
		// Kasai: lcp decreases by at most 1 when moving to the next suffix
		ll h = 0;
		fore(i, 0, n) {
			if (rnk[i] == n - 1) { h = 0; continue; }
			ll j = sa[rnk[i] + 1];
			while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
			lcp[rnk[i]] = h;
			if (h > 0) h--;
		}
	}
};
