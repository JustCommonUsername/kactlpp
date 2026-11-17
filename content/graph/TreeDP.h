/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: DP on a tree without recursion (no stack overflow for
 * $N = 10^6$). Builds a BFS order from the root, then handles the nodes
 * in reverse order so that children come before their parent.
 * The example computes subtree sizes and maximum independent set, with
 * \texttt{take[u]} = best with u chosen, \texttt{skip[u]} = best without u.
 * Usage: ll best = treeDP(adj, 0);
 * Time: O(N)
 */
#pragma once

vi parent, subtreeSize;

ll treeDP(vector<vi>& adj, ll root) {
	ll n = SZ(adj);
	parent.assign(n, -1), subtreeSize.assign(n, 1);
	vi order = {root};
	vector<bool> seen(n, false);
	seen[root] = true;
	// plain for: order grows inside the loop (fore fixes the bound)
	for (ll i = 0; i < SZ(order); i++) {
		ll u = order[i];
		for (ll v : adj[u]) if (!seen[v]) {
			seen[v] = true, parent[v] = u;
			order.pb(v);
		}
	}
	vi take(n, 1), skip(n, 0);
	for (ll i = SZ(order) - 1; i >= 0; i--) {
		ll u = order[i], p = parent[u];
		if (p == -1) continue;
		subtreeSize[p] += subtreeSize[u];
		take[p] += skip[u];                // u cannot be taken with p
		skip[p] += max(take[u], skip[u]);
	}
	return max(take[root], skip[root]);
}
