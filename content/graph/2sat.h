/**
 * Author: Emil Lenngren, Simon Lindholm, rewritten for readability
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: 2-SAT. Use it when every item has exactly 2 choices
 * (take/skip, left/right, red/blue) and every rule mentions at most 2
 * items. Variable x = "item x takes choice 1". Literals: \texttt{TRUE(x)},
 * \texttt{FALSE(x)}; \texttt{a\^{}1} negates literal a. Rules for literals a, b:
 * at least one: add\_or(a, b). Not both: add\_or(a\^{}1, b\^{}1).
 * a forces b: add\_implies(a, b). Exactly one: add\_xor(a, b).
 * a equals b: add\_xor(a, b\^{}1). a must hold: set\_true(a).
 * solve() is false if no assignment works, else value[x] is one answer.
 * E.g. "Ann or Bob wears red": add\_or(TRUE(ann), TRUE(bob));
 * "Ann and Cid wear different colours": add\_xor(TRUE(ann), TRUE(cid)).
 * How it works: $a \lor b$ is the edges $\lnot a \to b$, $\lnot b \to a$; impossible
 * iff x and $\lnot$x are in the same SCC.
 * Usage: TwoSat ts(n); ts.add_or(TRUE(0), FALSE(3)); if (ts.solve()) ts.value[0];
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
	void add_or(ll a, ll b) {
		adj[a ^ 1].pb(b);
		adj[b ^ 1].pb(a);
	}
	void set_true(ll a) { add_or(a, a); }
	void add_implies(ll a, ll b) { add_or(a ^ 1, b); }
	void add_xor(ll a, ll b) { add_or(a, b), add_or(a ^ 1, b ^ 1); }

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
