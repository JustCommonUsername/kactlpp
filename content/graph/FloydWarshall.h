/**
 * Author: Simon Lindholm, rewritten for readability
 * Date: 2016-12-15
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Floyd-Warshall_algorithm
 * Description: All-pairs shortest paths. Input: \texttt{dist[i][j]} =
 * weight of edge i -> j, or \texttt{INF} if there is none. Afterwards
 * \texttt{dist[i][j]} is the shortest distance, \texttt{INF} if there is no
 * path and \texttt{-INF} if the path can use a negative cycle.
 * Time: O(N^3)
 */
#pragma once

const ll INF = LLONG_MAX / 4;

void floyd_warshall(vector<vi>& dist) {
	ll n = SZ(dist);
	fore(i, 0, n) dist[i][i] = min(dist[i][i], 0LL);
	// k = intermediate node that paths may now use
	fore(k, 0, n) fore(i, 0, n) fore(j, 0, n)
		if (dist[i][k] != INF && dist[k][j] != INF)
			dist[i][j] = min(dist[i][j], max(dist[i][k] + dist[k][j], -INF));
	// a node k with dist[k][k] < 0 lies on a negative cycle
	fore(k, 0, n) if (dist[k][k] < 0)
		fore(i, 0, n) fore(j, 0, n)
			if (dist[i][k] != INF && dist[k][j] != INF) dist[i][j] = -INF;
}
