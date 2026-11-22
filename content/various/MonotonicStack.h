/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: \texttt{next\_greater[i]} = first j > i with a[j] > a[i] (or n).
 * The stack holds indices whose answer is still unknown, with decreasing
 * values. Same idea: previous smaller, largest rectangle in a histogram.
 * \texttt{sliding\_min} = minimum of every window of length k; the deque holds
 * indices with increasing values, the front is the minimum.
 * Time: O(N)
 */
#pragma once

vi next_greater(vi& a) {
	ll n = SZ(a);
	vi res(n, n), stk;
	fore(i, 0, n) {
		while (!stk.empty() && a[stk.back()] < a[i]) {
			res[stk.back()] = i;
			stk.pop_back();
		}
		stk.pb(i);
	}
	return res;
}

vi sliding_min(vi& a, ll k) {
	vi res;
	deque<ll> dq;
	fore(i, 0, SZ(a)) {
		while (!dq.empty() && a[dq.back()] >= a[i]) dq.pop_back();
		dq.pb(i);
		if (dq.front() <= i - k) dq.pop_front(); // left the window
		if (i >= k - 1) res.pb(a[dq.front()]);
	}
	return res;
}
