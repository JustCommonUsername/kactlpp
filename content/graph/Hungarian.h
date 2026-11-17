/**
 * Author: e-maxx, rewritten for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: https://cp-algorithms.com/graph/hungarian-algorithm.html
 * Description: Assignment problem: \texttt{cost[i][j]} = cost of giving job j
 * to worker i ($n \le m$). Assigns every worker a different job with
 * minimum total cost. Returns \{cost, job of each worker\}.
 * For maximum profit negate the costs. Uses potentials u, v (1-based
 * internally, row/column 0 is a dummy).
 * Usage: auto [total, job] = hungarian(cost);
 * Time: $O(n^2 m)$
 */
#pragma once

pair<ll, vi> hungarian(vector<vi>& cost) {
	ll n = SZ(cost), m = SZ(cost[0]);
	const ll INF = LLONG_MAX / 4;
	vi u(n + 1), v(m + 1), p(m + 1, 0), way(m + 1, 0);
	// p[j] = worker assigned to job j (0 = none)
	fore(i, 1, n + 1) {
		p[0] = i;
		ll j0 = 0;
		vi minv(m + 1, INF);
		vector<bool> used(m + 1, false);
		do { // Dijkstra-like search for an augmenting path
			used[j0] = true;
			ll i0 = p[j0], delta = INF, j1 = 0;
			fore(j, 1, m + 1) if (!used[j]) {
				ll cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
				if (cur < minv[j]) minv[j] = cur, way[j] = j0;
				if (minv[j] < delta) delta = minv[j], j1 = j;
			}
			fore(j, 0, m + 1) {
				if (used[j]) u[p[j]] += delta, v[j] -= delta;
				else minv[j] -= delta;
			}
			j0 = j1;
		} while (p[j0] != 0);
		do { // flip the path
			ll j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while (j0 != 0);
	}
	vi job(n);
	fore(j, 1, m + 1) if (p[j]) job[p[j] - 1] = j - 1;
	ll total = 0;
	fore(i, 0, n) total += cost[i][job[i]];
	return {total, job};
}
