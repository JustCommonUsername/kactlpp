/**
 * Author: Simon Lindholm, rewritten for readability
 * Date: 2015-02-23
 * License: CC0
 * Source: Wikipedia, folklore
 * Description: Shortest paths from \texttt{s} when edge weights can be
 * negative. Unreachable nodes get \texttt{INF}, nodes whose distance can
 * be made arbitrarily small (reachable from a negative cycle) get \texttt{-INF}.
 * Usage: vector<Edge> edges; edges.pb({u, v, w}); vi d = bellmanFord(n, edges, s);
 * Time: O(VE)
 */
#pragma once

const ll INF = LLONG_MAX / 4;
struct Edge { ll from, to, weight; };

vi bellmanFord(ll n, vector<Edge>& edges, ll s) {
	vi dist(n, INF);
	dist[s] = 0;
	// after n - 1 rounds all shortest paths are final
	fore(round, 0, n - 1)
		for (auto& e : edges)
			if (dist[e.from] != INF)
				dist[e.to] = min(dist[e.to], dist[e.from] + e.weight);
	// whatever still improves is on/after a negative cycle
	fore(round, 0, n)
		for (auto& e : edges)
			if (dist[e.from] != INF &&
			    (dist[e.from] == -INF || dist[e.from] + e.weight < dist[e.to]))
				dist[e.to] = -INF;
	return dist;
}
