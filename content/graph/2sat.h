/**
 * Author: Emil Lenngren, Simon Lindholm, rewritten for readability
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: 2-SAT: find values for boolean variables such that a
 * conjunction of clauses $(a \lor b)$ is true. Literal \texttt{2x} is
 * "x is true", \texttt{2x+1} is "x is false" (use \texttt{TRUE(x)}, \texttt{FALSE(x)}).
 * Clause $a \lor b$ adds implications $\lnot a \to b$ and $\lnot b \to a$.
 * Unsatisfiable iff x and $\lnot$x are in the same SCC.
 * Usage: TwoSat ts(n); ts.addOr(TRUE(0), FALSE(3)); if (ts.solve()) ts.value[0];
 * Time: O(N + M) for N variables and M clauses.
 */
#pragma once

#include "SCC.h"

ll TRUE(ll x) { return 2 * x; }
ll FALSE(ll x) { return 2 * x + 1; }

struct TwoSat {
	ll n;
	vector<vi> adj; // implication graph on 2n literals
	vector<bool> value;
	TwoSat(ll N) : n(N), adj(2 * N) {}

	// a or b (a, b are literals); lit ^ 1 is the negation
	void addOr(ll a, ll b) {
		adj[a ^ 1].pb(b);
		adj[b ^ 1].pb(a);
	}
	void setTrue(ll a) { addOr(a, a); }
	void addImplies(ll a, ll b) { addOr(a ^ 1, b); }
	void addXor(ll a, ll b) { addOr(a, b), addOr(a ^ 1, b ^ 1); }

	bool solve() {
		scc(adj);
		value.assign(n, false);
		fore(x, 0, n) {
			if (comp[2 * x] == comp[2 * x + 1]) return false;
			// Tarjan numbers SCCs in reverse topological order:
			// pick the literal that comes later in topological order
			value[x] = comp[2 * x] < comp[2 * x + 1];
		}
		return true;
	}
};
