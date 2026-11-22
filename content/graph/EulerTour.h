/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Tree flattening (Euler tour). Numbers the nodes in DFS
 * order: \texttt{tin[u]} = position of u, and the subtree of u is exactly the
 * positions $[\texttt{tin[u]}, \texttt{tout[u]})$. Put \texttt{value[u]} at
 * position \texttt{tin[u]} of a Fenwick/segment tree, then:
 * subtree sum of u = query(tin[u], tout[u]); add to all of the subtree
 * = range update on the same range (lazy segment tree).
 * Path root $\to$ u sums: add x at tin[u] and -x at tout[u] in a Fenwick
 * tree of size n + 1, then the sum of the path to u is prefix\_sum(tin[u] + 1).
 * \texttt{is\_ancestor(a, b)}: a is on the path from the root to b.
 * Usage: flatten(adj, 0); ft.add(tin[u], val); ft.range_sum(tin[u], tout[u]);
 * Time: O(N)
 */
#pragma once

vi tin, tout, node_at; // node_at[pos] = node with tin = pos

void flatten(vector<vi>& adj, ll root) {
	ll n = SZ(adj), timer = 0;
	tin.assign(n, -1), tout.assign(n, 0), node_at.assign(n, 0);
	vi parent(n, -1), next_edge(n, 0), stk = {root};
	tin[root] = timer++, node_at[0] = root;
	while (!stk.empty()) { // iterative DFS, no stack overflow
		ll u = stk.back();
		if (next_edge[u] == SZ(adj[u])) { // subtree of u is finished
			tout[u] = timer;
			stk.pop_back();
			continue;
		}
		ll v = adj[u][next_edge[u]++];
		if (v == parent[u]) continue;
		parent[v] = u;
		node_at[timer] = v, tin[v] = timer++;
		stk.pb(v);
	}
}

bool is_ancestor(ll a, ll b) { return tin[a] <= tin[b] && tout[b] <= tout[a]; }
