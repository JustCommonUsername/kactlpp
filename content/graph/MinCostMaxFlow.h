/**
 * Author: Stanford, rewritten for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore (successive shortest paths with SPFA)
 * Description: Min-cost max-flow. Each round finds a cheapest augmenting
 * path with Bellman-Ford/SPFA, so negative costs are fine as long as
 * there is no negative cycle. Returns \{max flow, min cost\}.
 * To limit the flow to $k$, stop once \texttt{flow} reaches $k$.
 * Usage: MinCostFlow mcf(n); mcf.add_edge(u, v, cap, cost); auto [f, c] = mcf.solve(s, t);
 * Time: $O(F \cdot VE)$ in the worst case, usually much faster.
 */
#pragma once

struct MinCostFlow {
	// adj[to][rev] is the reverse edge of an edge u -> to
	struct Edge { ll to, rev, cap, cost; };
	const ll INF = LLONG_MAX / 4;
	ll n;
	vector<vector<Edge>> adj;
	MinCostFlow(ll N) : n(N), adj(N) {}

	void add_edge(ll u, ll v, ll cap, ll cost) {
		adj[u].pb({v, SZ(adj[v]), cap, cost});
		adj[v].pb({u, SZ(adj[u]) - 1, 0, -cost});
	}

	ii solve(ll s, ll t) {
		ll flow = 0, cost = 0;
		while (true) {
			// SPFA: cheapest path s -> t in the residual graph
			vi dist(n, INF), prev_node(n, -1), prev_edge(n, -1);
			vector<bool> in_queue(n, false);
			queue<ll> q;
			dist[s] = 0, q.push(s);
			while (!q.empty()) {
				ll u = q.front(); q.pop();
				in_queue[u] = false;
				fore(i, 0, SZ(adj[u])) {
					Edge& e = adj[u][i];
					if (e.cap > 0 && dist[u] + e.cost < dist[e.to]) {
						dist[e.to] = dist[u] + e.cost;
						prev_node[e.to] = u, prev_edge[e.to] = i;
						if (!in_queue[e.to]) in_queue[e.to] = true, q.push(e.to);
					}
				}
			}
			if (dist[t] == INF) break;
			// bottleneck capacity along the path
			ll push = INF;
			for (ll v = t; v != s; v = prev_node[v])
				push = min(push, adj[prev_node[v]][prev_edge[v]].cap);
			for (ll v = t; v != s; v = prev_node[v]) {
				Edge& e = adj[prev_node[v]][prev_edge[v]];
				e.cap -= push;
				adj[v][e.rev].cap += push;
			}
			flow += push;
			cost += push * dist[t];
		}
		return {flow, cost};
	}
};
