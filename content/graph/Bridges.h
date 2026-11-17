/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: https://cp-algorithms.com/graph/bridge-searching.html
 * Description: Bridges and articulation points of an undirected graph.
 * A bridge is an edge whose removal disconnects the graph, an
 * articulation point is such a node. \texttt{adj[u]} holds pairs
 * (v, edgeId) so that parallel edges are handled correctly.
 * Usage: findBridges(adj); // fills bridges (edge ids) and isCut
 * Time: O(V + E)
 */
#pragma once

// tin[u] = discovery time, low[u] = smallest tin reachable from the
// subtree of u using one back edge
vi tin, low, bridges;
vector<bool> isCut;
ll timer;

void dfs(ll u, ll parentEdge, vector<vector<ii>>& adj) {
	tin[u] = low[u] = timer++;
	ll children = 0;
	for (auto [v, id] : adj[u]) {
		if (id == parentEdge) continue;
		if (tin[v] != -1) {
			low[u] = min(low[u], tin[v]); // back edge
			continue;
		}
		dfs(v, id, adj);
		low[u] = min(low[u], low[v]);
		children++;
		if (low[v] > tin[u]) bridges.pb(id);
		if (low[v] >= tin[u] && parentEdge != -1) isCut[u] = true;
	}
	if (parentEdge == -1 && children > 1) isCut[u] = true;
}

void findBridges(vector<vector<ii>>& adj) {
	ll n = SZ(adj);
	tin.assign(n, -1), low.assign(n, 0);
	isCut.assign(n, false), bridges.clear();
	timer = 0;
	fore(u, 0, n) if (tin[u] == -1) dfs(u, -1, adj);
}
