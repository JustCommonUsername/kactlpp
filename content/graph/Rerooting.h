/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Rerooting DP: an answer for every node as the root, in
 * $O(N)$ instead of $O(N^2)$. Pass 1 (children before parent): \texttt{down[u]}
 * = answer inside the subtree of u. Pass 2 (parent before children):
 * \texttt{up[v]} = answer from everything outside the subtree of v, computed
 * from u = parent(v) as "all of u except the part coming from v".
 * If the combine can be undone (sum) subtract v's part; otherwise (max)
 * keep the best two children, or prefix/suffix maxima over the children.
 * \texttt{sumDist[u]} = sum of distances from u to all nodes.
 * \texttt{farthest[u]} = max distance from u to any node.
 * Usage: rerootSumDist(adj); rerootFarthest(adj);
 * Time: O(N)
 */
#pragma once

vi order, par;
// BFS order from node 0: parents come before their children
void buildOrder(vector<vi>& adj) {
	ll n = SZ(adj);
	order = {0}, par.assign(n, -1);
	for (ll i = 0; i < SZ(order); i++) {
		ll u = order[i];
		for (ll v : adj[u]) if (v != par[u]) par[v] = u, order.pb(v);
	}
}

vi sumDist;
void rerootSumDist(vector<vi>& adj) {
	ll n = SZ(adj);
	buildOrder(adj);
	vi size(n, 1), down(n, 0); // down[u] = sum of dist from u into subtree
	for (ll i = n - 1; i > 0; i--) {
		ll u = order[i], p = par[u];
		size[p] += size[u];
		down[p] += down[u] + size[u]; // every node of u is 1 step further
	}
	sumDist.assign(n, 0);
	sumDist[0] = down[0];
	fore(i, 1, n) {
		ll v = order[i], u = par[v];
		// moving the root u -> v: size[v] nodes get 1 closer, n - size[v] further
		sumDist[v] = sumDist[u] - size[v] + (n - size[v]);
	}
}

vi farthest;
void rerootFarthest(vector<vi>& adj) {
	ll n = SZ(adj);
	buildOrder(adj);
	// best1[u], best2[u] = two largest depths into different children,
	// bestChild[u] = child that gives best1
	vi best1(n, 0), best2(n, 0), bestChild(n, -1), up(n, 0);
	for (ll i = n - 1; i > 0; i--) {
		ll u = order[i], p = par[u], d = best1[u] + 1;
		if (d > best1[p]) best2[p] = best1[p], best1[p] = d, bestChild[p] = u;
		else if (d > best2[p]) best2[p] = d;
	}
	// up[v] = longest path starting at v that first goes to parent(v)
	fore(i, 1, n) {
		ll v = order[i], u = par[v];
		ll downWithoutV = bestChild[u] == v ? best2[u] : best1[u];
		up[v] = 1 + max(up[u], downWithoutV);
	}
	farthest.assign(n, 0);
	fore(u, 0, n) farthest[u] = max(best1[u], up[u]);
}
