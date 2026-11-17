/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Find a cycle and return its nodes in order (empty if the
 * graph has none). Directed: DFS with colors, an edge to a gray node
 * (still on the DFS path) closes a cycle. Undirected: \texttt{adj[u]} holds
 * (v, edgeId) like in Bridges.h, an edge to a visited node that is not
 * the edge we came from closes a cycle. Both DFS are iterative.
 * Other cycle questions: is there a directed cycle at all
 * $\iff$ TopoSort returns fewer than n nodes; negative cycle $\Rightarrow$
 * BellmanFord; shortest cycle (girth) $\Rightarrow$ BFS from every node, $O(VE)$;
 * undirected graph is a forest $\iff$ UnionFind.join never fails.
 * Usage: vi cyc = findCycleDirected(adj); // e.g. {2, 5, 3}: 2->5->3->2
 * Time: O(V + E)
 */
#pragma once

vi findCycleDirected(vector<vi>& adj) {
	ll n = SZ(adj);
	// color: 0 = unvisited, 1 = on the current DFS path, 2 = finished
	vi color(n, 0), parent(n, -1), nextEdge(n, 0);
	fore(start, 0, n) {
		if (color[start] != 0) continue;
		vi stk = {start};
		color[start] = 1;
		while (!stk.empty()) {
			ll u = stk.back();
			if (nextEdge[u] == SZ(adj[u])) { // all edges done
				color[u] = 2;
				stk.pop_back();
				continue;
			}
			ll v = adj[u][nextEdge[u]++];
			if (color[v] == 0) {
				color[v] = 1, parent[v] = u;
				stk.pb(v);
			} else if (color[v] == 1) { // back edge u -> v
				vi cycle = {v};
				for (ll x = u; x != v; x = parent[x]) cycle.pb(x);
				reverse(cycle.begin() + 1, cycle.end());
				return cycle;
			}
		}
	}
	return {};
}

vi findCycleUndirected(vector<vector<ii>>& adj) {
	ll n = SZ(adj);
	vi parent(n, -1), parentEdge(n, -1), nextEdge(n, 0), depth(n, -1);
	fore(start, 0, n) {
		if (depth[start] != -1) continue;
		vi stk = {start};
		depth[start] = 0;
		while (!stk.empty()) {
			ll u = stk.back();
			if (nextEdge[u] == SZ(adj[u])) { stk.pop_back(); continue; }
			auto [v, id] = adj[u][nextEdge[u]++];
			if (id == parentEdge[u]) continue; // edge we came from
			if (depth[v] == -1) {
				depth[v] = depth[u] + 1, parent[v] = u, parentEdge[v] = id;
				stk.pb(v);
			} else if (depth[v] <= depth[u]) { // v is an ancestor of u
				vi cycle;
				for (ll x = u; x != v; x = parent[x]) cycle.pb(x);
				cycle.pb(v);
				return cycle;
			}
		}
	}
	return {};
}
