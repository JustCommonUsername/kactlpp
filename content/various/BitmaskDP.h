/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Bitmask DP over subsets, example: travelling salesman.
 * \texttt{dp[mask][u]} = cheapest path that starts at 0, visits exactly
 * the nodes in \texttt{mask} and ends at u. Feasible for $n \le 20$.
 * Returns the cheapest cycle through all nodes (\texttt{INF} if none).
 * Time: $O(2^n n^2)$, memory $O(2^n n)$.
 */
#pragma once

const ll INF = LLONG_MAX / 4;

ll tsp(vector<vi>& cost) {
	ll n = SZ(cost);
	vector<vi> dp(1 << n, vi(n, INF));
	dp[1][0] = 0;
	fore(mask, 1, 1 << n) fore(u, 0, n) {
		if (dp[mask][u] == INF) continue;
		fore(v, 0, n) {
			if (mask >> v & 1) continue; // v already visited
			ll next = mask | (1 << v);
			dp[next][v] = min(dp[next][v], dp[mask][u] + cost[u][v]);
		}
	}
	ll best = INF;
	fore(u, 0, n) if (dp[(1 << n) - 1][u] < INF)
		best = min(best, dp[(1 << n) - 1][u] + cost[u][0]);
	return best;
}
