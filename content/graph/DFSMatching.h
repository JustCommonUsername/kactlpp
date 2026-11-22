/**
 * Author: Lukas Polacek, rewritten for readability
 * Date: 2009-10-28
 * License: CC0
 * Source: folklore (Kuhn's algorithm)
 * Description: Maximum bipartite matching. \texttt{adj[l]} lists the
 * right nodes adjacent to left node \texttt{l}. Afterwards
 * \texttt{match\_right[r]} is the left partner of \texttt{r} (or -1).
 * By K\"onig, in bipartite graphs min vertex cover = max matching, and
 * max independent set = $V$ - max matching.
 * Usage: ll m = max_matching(adj, num_right);
 * Time: O(VE), fast in practice. Use Dinic for big graphs.
 */
#pragma once

vi match_right;
vector<bool> visited;

// try to find an augmenting path starting at left node l
bool try_kuhn(ll l, vector<vi>& adj) {
	for (ll r : adj[l]) {
		if (visited[r]) continue;
		visited[r] = true;
		if (match_right[r] == -1 || try_kuhn(match_right[r], adj)) {
			match_right[r] = l;
			return true;
		}
	}
	return false;
}

ll max_matching(vector<vi>& adj, ll num_right) {
	match_right.assign(num_right, -1);
	ll size = 0;
	fore(l, 0, SZ(adj)) {
		visited.assign(num_right, false);
		if (try_kuhn(l, adj)) size++;
	}
	return size;
}
