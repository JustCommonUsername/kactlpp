/**
 * Author: Simon Lindholm, rewritten for readability
 * Date: 2015-05-12
 * License: CC0
 * Source: own work
 * Description: Maximum of a unimodal function (strictly increasing, then
 * strictly decreasing). For the minimum flip the comparisons.
 * Integer version: binary search on the slope $f(m) < f(m+1)$.
 * Usage: double x = ternaryReal(0, 1e9, f); ll i = ternaryInt(0, n - 1, f);
 * Time: O(\log(hi - lo))
 */
#pragma once

double ternaryReal(double lo, double hi, auto f) {
	fore(iter, 0, 200) {
		double m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
		if (f(m1) < f(m2)) lo = m1; // maximum is right of m1
		else hi = m2;
	}
	return lo;
}

// smallest i in [lo, hi] where f is maximal
ll ternaryInt(ll lo, ll hi, auto f) {
	while (lo < hi) {
		ll mid = lo + (hi - lo) / 2;
		if (f(mid) < f(mid + 1)) lo = mid + 1; // still increasing
		else hi = mid;
	}
	return lo;
}
