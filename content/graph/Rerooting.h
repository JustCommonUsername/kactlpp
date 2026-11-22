/**
 * Author: team, rewritten for readability
 * Date: 2026-11-21
 * License: CC0
 * Source: folklore
 * Description: Rerooting DP: an answer for every node as the root in
 * $O(N)$ instead of $O(N^2)$. Recipe:
 * (1) root the tree at 0 and compute subtree info with a DFS,
 * (2) compute the answer for root 0,
 * (3) DFS again and move the root from u to each child x:
 * ans[x] = ans[u] + (change for nodes outside x's subtree)
 * + (change for nodes inside x's subtree).
 * If the answer is a sum, the change is easy (example 1). If it is a
 * max, also keep the best two children (example 2).
 * The DFS is recursive; on a path of $10^6$ nodes the stack may
 * overflow, then use the iterative order from TreeDP.h.
 * Usage: vi s = sum_of_distances(adj); vi f = farthest_node(adj);
 * Time: O(N)
 */
#pragma once

// sum of distances from every node to all other nodes
vi sum_of_distances(vector<vi>& adj) {
	ll n = SZ(adj);
	// step 1: subtree sizes and depths with root 0
	vi subtree_size(n, 1), depth(n, 0);
	auto dfs_size = [&](ll u, ll p, auto&& self) -> void {
		for (ll x : adj[u]) {
			if (x == p) continue;
			depth[x] = depth[u] + 1;
			self(x, u, self);
			subtree_size[u] += subtree_size[x];
		}
	};
	dfs_size(0, -1, dfs_size);

	// step 2: answer for root 0 = sum of all depths
	vi sum_dist(n);
	sum_dist[0] = accumulate(ALL(depth), 0LL);

	// step 3: move the root from u to x. The subtree_size[x] nodes
	// inside get 1 closer, the n - subtree_size[x] outside 1 further.
	auto reroot = [&](ll u, ll p, auto&& self) -> void {
		for (ll x : adj[u]) {
			if (x == p) continue;
			sum_dist[x] = sum_dist[u] + (n - subtree_size[x]) - subtree_size[x];
			self(x, u, self);
		}
	};
	reroot(0, -1, reroot);
	return sum_dist;
}

// distance from every node to the farthest node
vi farthest_node(vector<vi>& adj) {
	ll n = SZ(adj);
	// step 1: down1[u] = longest path down from u, down2[u] = second
	// longest through a DIFFERENT child, best_child[u] = child of down1
	vi down1(n, 0), down2(n, 0), best_child(n, -1);
	auto dfs_down = [&](ll u, ll p, auto&& self) -> void {
		for (ll x : adj[u]) {
			if (x == p) continue;
			self(x, u, self);
			ll len = down1[x] + 1;
			if (len > down1[u]) {
				down2[u] = down1[u];
				down1[u] = len, best_child[u] = x;
			} else if (len > down2[u]) {
				down2[u] = len;
			}
		}
	};
	dfs_down(0, -1, dfs_down);

	// step 2: up[u] = longest path that starts at u and goes to its
	// parent first; the root has no parent, so up[0] = 0
	vi up(n, 0);

	// step 3: from x, going up to u, we may continue up from u or go
	// down from u, but not back into x (so use down2 if x is u's best)
	auto reroot = [&](ll u, ll p, auto&& self) -> void {
		for (ll x : adj[u]) {
			if (x == p) continue;
			ll down_avoiding_x = best_child[u] == x ? down2[u] : down1[u];
			up[x] = 1 + max(up[u], down_avoiding_x);
			self(x, u, self);
		}
	};
	reroot(0, -1, reroot);

	vi farthest(n);
	fore(u, 0, n) farthest[u] = max(down1[u], up[u]);
	return farthest;
}
