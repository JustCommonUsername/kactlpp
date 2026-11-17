/**
 * Author: chilli, rewritten for readability
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Maximum flow / minimum cut with Dinic's algorithm.
 * After \texttt{maxFlow(s, t)}, the nodes with \texttt{level[u] != 0}
 * are on the source side of a minimum cut.
 * Bipartite matching: source -> left (cap 1), left -> right (cap 1),
 * right -> sink (cap 1).
 * Usage: Dinic flow(n); flow.addEdge(u, v, cap); ll f = flow.maxFlow(s, t);
 * Time: $O(V^2 E)$, $O(E \sqrt V)$ for bipartite matching.
 */
#pragma once

struct Dinic {
	// edge u -> to with remaining capacity cap; adj[to][rev] is
	// the reverse edge (used to undo flow)
	struct Edge { ll to, rev, cap, originalCap; };
	vector<vector<Edge>> adj;
	vi level, nextEdge;
	Dinic(ll n) : adj(n), level(n), nextEdge(n) {}

	void addEdge(ll u, ll v, ll cap, ll reverseCap = 0) {
		adj[u].pb({v, SZ(adj[v]), cap, cap});
		adj[v].pb({u, SZ(adj[u]) - 1, reverseCap, reverseCap});
	}

	// BFS: level[u] = distance from s using edges with cap > 0
	bool buildLevels(ll s, ll t) {
		fill(ALL(level), 0);
		level[s] = 1;
		queue<ll> q;
		q.push(s);
		while (!q.empty()) {
			ll u = q.front(); q.pop();
			for (auto& e : adj[u])
				if (e.cap > 0 && level[e.to] == 0) {
					level[e.to] = level[u] + 1;
					q.push(e.to);
				}
		}
		return level[t] != 0;
	}

	// DFS: push flow along edges that go one level deeper
	ll pushFlow(ll u, ll t, ll flow) {
		if (u == t) return flow;
		for (ll& i = nextEdge[u]; i < SZ(adj[u]); i++) {
			Edge& e = adj[u][i];
			if (e.cap > 0 && level[e.to] == level[u] + 1) {
				ll pushed = pushFlow(e.to, t, min(flow, e.cap));
				if (pushed > 0) {
					e.cap -= pushed;
					adj[e.to][e.rev].cap += pushed;
					return pushed;
				}
			}
		}
		return 0;
	}

	ll maxFlow(ll s, ll t) {
		ll total = 0;
		while (buildLevels(s, t)) {
			fill(ALL(nextEdge), 0);
			while (ll pushed = pushFlow(s, t, LLONG_MAX)) total += pushed;
		}
		return total;
	}

	// flow on edge e = e.originalCap - e.cap (if positive)
};
