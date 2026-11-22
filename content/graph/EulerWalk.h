/**
 * Author: Simon Lindholm, rewritten for readability
 * Date: 2019-12-31
 * License: CC0
 * Source: folklore (Hierholzer's algorithm)
 * Description: Eulerian path/cycle that uses every edge exactly once.
 * \texttt{adj[u]} holds pairs (v, edge\_id); for undirected graphs add the
 * edge in both directions with the same id. Returns the nodes of the
 * walk starting at \texttt{start}, or \{\} if no such walk exists.
 * Existence (undirected): connected and 0 or 2 nodes of odd degree
 * (start at an odd one). Directed: in = out everywhere, except
 * possibly start (out = in + 1) and end (in = out + 1).
 * Usage: vi walk = euler_walk(adj, num_edges, start);
 * Time: O(V + E)
 */
#pragma once

vi euler_walk(vector<vector<ii>>& adj, ll num_edges, ll start) {
	ll n = SZ(adj);
	vi next_edge(n, 0), walk, stk = {start};
	vector<bool> used(num_edges, false);
	// balance < 0 at the end means start was a bad choice
	vi balance(n, 0);
	balance[start]++;
	while (!stk.empty()) {
		ll u = stk.back();
		// skip edges that were already used
		while (next_edge[u] < SZ(adj[u]) && used[adj[u][next_edge[u]].snd])
			next_edge[u]++;
		if (next_edge[u] == SZ(adj[u])) { // dead end: add to walk
			walk.pb(u);
			stk.pop_back();
		} else {
			auto [v, id] = adj[u][next_edge[u]];
			used[id] = true;
			balance[u]--, balance[v]++;
			stk.pb(v);
		}
	}
	for (ll b : balance) if (b < 0) return {};
	if (SZ(walk) != num_edges + 1) return {}; // graph not connected
	reverse(ALL(walk));
	return walk;
}
