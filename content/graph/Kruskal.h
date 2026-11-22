/**
 * Author: folklore, rewritten for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Minimum spanning tree (Kruskal). Edges are
 * \{weight, \{u, v\}\}. Returns the total weight; the chosen edges are
 * stored in \texttt{mst\_edges}. If fewer than $n-1$ edges are chosen
 * the graph is not connected (minimum spanning forest).
 * For a maximum spanning tree sort in decreasing order.
 * Time: $O(E \log E)$
 */
#pragma once

#include "../data-structures/UnionFind.h"

vector<pair<ll, ii>> mst_edges;

ll kruskal(ll n, vector<pair<ll, ii>> edges) {
	sort(ALL(edges)); // by weight
	UnionFind uf(n);
	mst_edges.clear();
	ll total = 0;
	for (auto& [w, e] : edges)
		if (uf.join(e.fst, e.snd)) {
			total += w;
			mst_edges.pb({w, e});
		}
	return total;
}
