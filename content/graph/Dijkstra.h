/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Shortest paths from \texttt{s} with non-negative edge
 * weights. \texttt{adj[u]} holds pairs (v, w) for an edge u -> v of weight w.
 * Unreachable nodes have distance \texttt{INF}. To get the path, follow
 * \texttt{parent[]} back from the target.
 * For 0/1 weights a deque BFS is enough: push weight-0 edges to the
 * front and weight-1 edges to the back.
 * Usage: vector<vector<ii>> adj(n); adj[u].pb({v, w}); vi d = dijkstra(adj, s);
 * Time: O((V + E) \log V)
 */
#pragma once

const ll INF = LLONG_MAX / 4;
vi parent;

vi dijkstra(vector<vector<ii>>& adj, ll s) {
	ll n = SZ(adj);
	vi dist(n, INF);
	parent.assign(n, -1);
	// min-heap of (distance, node)
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	dist[s] = 0;
	pq.push({0, s});
	while (!pq.empty()) {
		auto [d, u] = pq.top();
		pq.pop();
		if (d > dist[u]) continue; // outdated entry
		for (auto [v, w] : adj[u]) {
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				parent[v] = u;
				pq.push({dist[v], v});
			}
		}
	}
	return dist;
}
