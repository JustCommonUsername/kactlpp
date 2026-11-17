/**
 * Author: Lukas Polacek, rewritten for readability
 * Date: 2009-10-28
 * License: CC0
 * Source: folklore (Kuhn's algorithm)
 * Description: Maximum bipartite matching. \texttt{adj[l]} lists the
 * right nodes adjacent to left node \texttt{l}. Afterwards
 * \texttt{matchRight[r]} is the left partner of \texttt{r} (or -1).
 * By K\"onig, in bipartite graphs min vertex cover = max matching, and
 * max independent set = $V$ - max matching.
 * Usage: ll m = maxMatching(adj, numRight);
 * Time: O(VE), fast in practice. Use Dinic for big graphs.
 */
#pragma once

vi matchRight;
vector<bool> visited;

// try to find an augmenting path starting at left node l
bool tryKuhn(ll l, vector<vi>& adj) {
	for (ll r : adj[l]) {
		if (visited[r]) continue;
		visited[r] = true;
		if (matchRight[r] == -1 || tryKuhn(matchRight[r], adj)) {
			matchRight[r] = l;
			return true;
		}
	}
	return false;
}

ll maxMatching(vector<vi>& adj, ll numRight) {
	matchRight.assign(numRight, -1);
	ll size = 0;
	fore(l, 0, SZ(adj)) {
		visited.assign(numRight, false);
		if (tryKuhn(l, adj)) size++;
	}
	return size;
}
