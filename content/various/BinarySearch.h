/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Binary search on integers. \texttt{ok} must be monotone:
 * \texttt{first\_true} needs false...false true...true and returns the first
 * true (hi + 1 if none), \texttt{last\_true} needs true...true false...false
 * and returns the last true (lo - 1 if none).
 * On a sorted array: \texttt{my\_lower\_bound} = first index with a[i] $\ge$ x,
 * \texttt{my\_upper\_bound} = first index with a[i] > x (n if none);
 * x occurs \texttt{my\_upper\_bound - my\_lower\_bound} times.
 * Search on the answer: "minimize the maximum" / "maximize the minimum"
 * $\Rightarrow$ guess the answer and check it greedily (example below).
 * \texttt{compress} maps values to 0..k-1 keeping their order.
 * Usage: ll x = first_true(0, 2e18, [\&](ll x) { return check(x); });
 * Time: O(\log(hi - lo)) calls of ok.
 */
#pragma once

ll first_true(ll lo, ll hi, auto ok) {
	// invariant: answer is in [lo, hi + 1]
	hi++;
	while (lo < hi) {
		ll mid = lo + (hi - lo) / 2; // no overflow, rounds down
		if (ok(mid)) hi = mid;
		else lo = mid + 1;
	}
	return lo;
}

ll last_true(ll lo, ll hi, auto ok) {
	// invariant: answer is in [lo - 1, hi]
	lo--;
	while (lo < hi) {
		ll mid = lo + (hi - lo + 1) / 2; // round up, else infinite loop
		if (ok(mid)) lo = mid;
		else hi = mid - 1;
	}
	return lo;
}

ll my_lower_bound(vi& a, ll x) {
	return first_true(0, SZ(a) - 1, [&](ll i) { return a[i] >= x; });
}
ll my_upper_bound(vi& a, ll x) {
	return first_true(0, SZ(a) - 1, [&](ll i) { return a[i] > x; });
}

// Example: split a (a[i] >= 0) into at most k consecutive parts so
// that the largest part sum is minimal. Check: greedily fill parts.
ll min_largest_part(vi& a, ll k) {
	auto ok = [&](ll limit) {
		ll parts = 1, sum = 0;
		for (ll x : a) {
			if (x > limit) return false;
			if (sum + x > limit) parts++, sum = 0;
			sum += x;
		}
		return parts <= k;
	};
	return first_true(0, accumulate(ALL(a), 0LL), ok);
}

// coordinate compression: a[i] becomes its rank among distinct values
vi compress(vi& a) {
	vi vals = a;
	sort(ALL(vals));
	vals.erase(unique(ALL(vals)), vals.end());
	for (ll& x : a) x = lower_bound(ALL(vals), x) - vals.begin();
	return vals; // vals[rank] = original value
}
