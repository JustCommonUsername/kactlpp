/**
 * Author: Lukas Polacek, rewritten for readability
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Strongly connected components of a directed graph
 * (Tarjan). \texttt{comp[u]} = id of the component of \texttt{u}.
 * Components are numbered in reverse topological order: an edge
 * u -> v between components always has \texttt{comp[u] >= comp[v]}.
 * Usage: ll k = scc(adj); // comp[] filled, k = number of components
 * Time: O(V + E)
 */
#pragma once

// tin[u] = discovery time, low[u] = smallest tin reachable from the
// subtree of u using at most one back edge; stack = nodes not yet
// assigned to a component
vi tin, low, comp, stk;
vector<bool> on_stack;
ll timer, num_comps;

void tarjan(ll u, vector<vi>& adj) {
	tin[u] = low[u] = timer++;
	stk.pb(u), on_stack[u] = true;
	for (ll v : adj[u]) {
		if (tin[v] == -1) {
			tarjan(v, adj);
			low[u] = min(low[u], low[v]);
		} else if (on_stack[v]) {
			low[u] = min(low[u], tin[v]);
		}
	}
	if (low[u] == tin[u]) { // u is the root of a component
		while (true) {
			ll v = stk.back();
			stk.pop_back(), on_stack[v] = false;
			comp[v] = num_comps;
			if (v == u) break;
		}
		num_comps++;
	}
}

ll scc(vector<vi>& adj) {
	ll n = SZ(adj);
	tin.assign(n, -1), low.assign(n, 0), comp.assign(n, -1);
	on_stack.assign(n, false), stk.clear();
	timer = num_comps = 0;
	fore(u, 0, n) if (tin[u] == -1) tarjan(u, adj);
	return num_comps;
}
