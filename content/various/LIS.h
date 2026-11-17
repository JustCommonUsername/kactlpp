/**
 * Author: Johan Sannemo, rewritten for readability
 * License: CC0
 * Description: Longest strictly increasing subsequence; returns its
 * indices. For non-decreasing use \texttt{upper\_bound} instead of
 * \texttt{lower\_bound}.
 * Time: $O(N \log N)$
 */
#pragma once

vi lis(vi& a) {
	ll n = SZ(a);
	// tails[k] = smallest last value of an increasing subsequence
	// of length k + 1, tailIdx[k] = its index in a
	vi tails, tailIdx, prev(n, -1);
	fore(i, 0, n) {
		ll k = lower_bound(ALL(tails), a[i]) - tails.begin();
		if (k == SZ(tails)) tails.pb(a[i]), tailIdx.pb(i);
		else tails[k] = a[i], tailIdx[k] = i;
		if (k > 0) prev[i] = tailIdx[k - 1];
	}
	vi res;
	for (ll i = tailIdx.empty() ? -1 : tailIdx.back(); i != -1; i = prev[i])
		res.pb(i);
	reverse(ALL(res));
	return res;
}
