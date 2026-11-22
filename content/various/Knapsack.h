/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Knapsack with capacity W. \texttt{best[c]} = max value with
 * total weight at most c. 0/1: every item at most once (loop c downwards).
 * Unbounded knapsack: every item any number of times (loop c upwards).
 * For "can we reach weight exactly c" use a \texttt{bitset} (see BitTricks.h).
 * Usage: ll v = knapsack01(w, val, W);
 * Time: O(N W)
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
