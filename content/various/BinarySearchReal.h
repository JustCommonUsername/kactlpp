/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Binary search on real numbers. Do a fixed number of
 * iterations instead of \texttt{while (hi - lo > EPS)}: with large values
 * hi - lo can stay above EPS forever because doubles are not dense.
 * Each iteration halves the interval, so 100 iterations shrink $10^{18}$
 * to $10^{-12}$. Use \texttt{long double} if the answer needs more digits
 * and print with \texttt{setprecision}.
 * Typical use: maximize an average or a ratio $\frac{\sum a}{\sum b}$:
 * "average $\ge$ x" $\iff$ $\sum (a_i - x \cdot b_i) \ge 0$, which is easy to check.
 * Usage: double x = last_true_real(0, 1e9, [\&](double x) { return check(x); });
 * Time: 100 calls of ok.
 */
#pragma once

// largest x in [lo, hi] with ok(x), ok = true...true false...false
double last_true_real(double lo, double hi, auto ok) {
	fore(iter, 0, 100) {
		double mid = (lo + hi) / 2;
		if (ok(mid)) lo = mid;
		else hi = mid;
	}
	return lo;
}

// smallest x in [lo, hi] with ok(x), ok = false...false true...true
double first_true_real(double lo, double hi, auto ok) {
	fore(iter, 0, 100) {
		double mid = (lo + hi) / 2;
		if (ok(mid)) hi = mid;
		else lo = mid;
	}
	return hi;
}

// Example: maximum average of a subarray of length >= k.
// Average of a[l..r] >= x  <=>  sum of (a[i] - x) over [l..r] >= 0.
double max_average(vi& a, ll k) {
	ll n = SZ(a);
	auto ok = [&](double x) {
		// pre[i] = sum of (a[j] - x) for j < i
		vector<double> pre(n + 1, 0);
		fore(i, 0, n) pre[i + 1] = pre[i] + a[i] - x;
		double min_prefix = 0; // min of pre[0..r-k]
		fore(r, k, n + 1) {
			min_prefix = min(min_prefix, pre[r - k]);
			if (pre[r] - min_prefix >= 0) return true;
		}
		return false;
	};
	return last_true_real(*min_element(ALL(a)), *max_element(ALL(a)), ok);
}
