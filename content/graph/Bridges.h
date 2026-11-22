/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: https://cp-algorithms.com/graph/bridge-searching.html
 * Description: Bridges and articulation points of an undirected graph.
 * A bridge is an edge whose removal disconnects the graph, an
 * articulation point is such a node. \texttt{adj[u]} holds pairs
 * (v, edge\_id) so that parallel edges are handled correctly.
 * Usage: find_bridges(adj); // fills bridges (edge ids) and is_cut
 * Time: O(V + E)
 */
#pragma once

// tin[u] = discovery time, low[u] = smallest tin reachable from the
// subtree of u using one back edge
vi tin, low, bridges;
vector<bool> is_cut;
ll timer;

void dfs(ll u, ll parent_edge, vector<vector<ii>>& adj) {
	tin[u] = low[u] = timer++;
	ll children = 0;
	for (auto [v, id] : adj[u]) {
		if (id == parent_edge) continue;
		if (tin[v] != -1) {
			low[u] = min(low[u], tin[v]); // back edge
			continue;
		}
		dfs(v, id, adj);
		low[u] = min(low[u], low[v]);
		children++;
		if (low[v] > tin[u]) bridges.pb(id);
		if (low[v] >= tin[u] && parent_edge != -1) is_cut[u] = true;
	}
	if (parent_edge == -1 && children > 1) is_cut[u] = true;
}

void find_bridges(vector<vector<ii>>& adj) {
	ll n = SZ(adj);
	tin.assign(n, -1), low.assign(n, 0);
	is_cut.assign(n, false), bridges.clear();
	timer = 0;
	fore(u, 0, n) if (tin[u] == -1) dfs(u, -1, adj);
}
