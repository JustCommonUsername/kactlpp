/**
 * Author: Unknown, rewritten for readability
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Topological sort (Kahn's algorithm) of a directed graph.
 * Every edge goes from left to right in the returned order.
 * If the result has fewer than $n$ nodes, the graph has a cycle.
 * For the lexicographically smallest order use a min-heap instead of the queue.
 * Time: O(V + E)
 */
#pragma once

vi topo_sort(vector<vi>& adj) {
	ll n = SZ(adj);
	vi in_degree(n, 0), order;
	for (auto& out : adj) for (ll v : out) in_degree[v]++;
	queue<ll> q;
	fore(u, 0, n) if (in_degree[u] == 0) q.push(u);
	while (!q.empty()) {
		ll u = q.front();
		q.pop();
		order.pb(u);
		for (ll v : adj[u])
			if (--in_degree[v] == 0) q.push(v);
	}
	return order;
}
