/**
 * Author: Johan Sannemo, rewritten for readability
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Lowest common ancestor with binary lifting.
 * \texttt{up[k][u]} = $2^k$-th ancestor of u (the root points to itself).
 * Also gives the k-th ancestor and distances in the tree. For path
 * max/min/sum, store an extra table next to \texttt{up} and combine
 * it the same way.
 * Usage: LCA lca(adj, root); lca.query(a, b); lca.dist(a, b);
 * Time: $O(N \log N)$ build, $O(\log N)$ per query.
 */
#pragma once

struct LCA {
	ll n, LOG;
	vector<vi> up;
	vi depth;
	LCA(vector<vi>& adj, ll root) : n(SZ(adj)), LOG(1), depth(n, 0) {
		while ((1LL << LOG) < n) LOG++;
		up.assign(LOG, vi(n, root));
		// iterative DFS to avoid stack overflow on deep trees
		vector<bool> seen(n, false);
		vi stk = {root};
		seen[root] = true;
		while (!stk.empty()) {
			ll u = stk.back(); stk.pop_back();
			for (ll v : adj[u]) if (!seen[v]) {
				seen[v] = true;
				up[0][v] = u, depth[v] = depth[u] + 1;
				stk.pb(v);
			}
		}
		fore(k, 1, LOG) fore(u, 0, n) up[k][u] = up[k-1][up[k-1][u]];
	}

	// ancestor of u that is k levels higher
	ll kthAncestor(ll u, ll k) {
		fore(i, 0, LOG) if (k >> i & 1) u = up[i][u];
		return u;
	}

	ll query(ll a, ll b) {
		if (depth[a] < depth[b]) swap(a, b);
		a = kthAncestor(a, depth[a] - depth[b]);
		if (a == b) return a;
		// jump both up as long as they stay different
		for (ll k = LOG - 1; k >= 0; k--)
			if (up[k][a] != up[k][b]) a = up[k][a], b = up[k][b];
		return up[0][a];
	}

	ll dist(ll a, ll b) {
		return depth[a] + depth[b] - 2 * depth[query(a, b)];
	}
};
