/**
 * Author: Lukas Polacek, rewritten for readability
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set union (union by size + path compression).
 * Usage: UnionFind uf(n); uf.join(a, b); uf.connected(a, b);
 * Time: $O(\alpha(N))$ per operation, practically constant.
 */
#pragma once

struct UnionFind {
	// parent[u] = parent of u, a root is its own parent
	// size[r] = number of nodes in the set of root r
	ll num_sets;
	vi parent, size;
	UnionFind(ll N) : num_sets(N), parent(N), size(N, 1) {
		iota(parent.begin(), parent.end(), 0);
	}

	ll root(ll u) {
		if (parent[u] == u) return u;
		return parent[u] = root(parent[u]);
	}

	// returns false if a and b were already in the same set
	bool join(ll a, ll b) {
		a = root(a), b = root(b);
		if (a == b) return false;
		if (size[a] < size[b]) swap(a, b);
		parent[b] = a;
		size[a] += size[b];
		num_sets--;
		return true;
	}

	bool connected(ll a, ll b) { return root(a) == root(b); }
	ll set_size(ll u) { return size[root(u)]; }
};
