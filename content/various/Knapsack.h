/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Knapsack with capacity W. \texttt{best[c]} = max value with
 * total weight at most c. 0/1: every item at most once (loop c downwards).
 * Unbounded knapsack: every item any number of times (loop c upwards).
 * For "can we reach weight exactly c" use a \texttt{bitset} (see BitTricks.h).
 * Fractional (items can be cut): no DP, greedy by value per weight,
 * best ratio first; only the last item taken is cut.
 * Usage: ll v = knapsack01(w, val, W);
 * Time: O(N W), fractional O(N \log N)
 */
#pragma once

ll knapsack01(vi& weight, vi& value, ll W) {
	vi best(W + 1, 0);
	fore(i, 0, SZ(weight))
		// downwards, so best[c - weight[i]] does not use item i yet
		for (ll c = W; c >= weight[i]; c--)
			best[c] = max(best[c], best[c - weight[i]] + value[i]);
	return best[W];
}

ll knapsack_unbounded(vi& weight, vi& value, ll W) {
	vi best(W + 1, 0);
	fore(i, 0, SZ(weight))
		fore(c, weight[i], W + 1)
			best[c] = max(best[c], best[c - weight[i]] + value[i]);
	return best[W];
}

// items can be cut: greedy, best value per weight first
double knapsack_fractional(vi& weight, vi& value, ll W) {
	ll n = SZ(weight);
	vi order(n);
	iota(ALL(order), 0);
	// best value / weight first, compared without doubles
	sort(ALL(order), [&](ll a, ll b) {
		return value[a] * weight[b] > value[b] * weight[a];
	});

	double total = 0;
	ll left = W; // capacity still free
	for (ll i : order) {
		if (left == 0) break;
		if (weight[i] <= left) { // take the whole item
			total += value[i];
			left -= weight[i];
		} else { // cut it: take what fits, bag is full
			total += (double)value[i] * left / weight[i];
			left = 0;
		}
	}
	return total;
}
