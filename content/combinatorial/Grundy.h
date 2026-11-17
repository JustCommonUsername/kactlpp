/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore (Sprague-Grundy theorem)
 * Description: Impartial games (both players have the same moves, the
 * player who cannot move loses). grundy(state) = mex of the grundy values
 * of all states reachable in one move; a state is losing iff it is 0.
 * Several independent games played together: XOR their grundy values
 * (normal Nim: XOR of the heap sizes). Example: from a heap of size x
 * you may remove any amount listed in \texttt{moves}.
 * Usage: vi g = grundyTable(100, {1, 3, 4}); first player wins iff g[x] != 0
 * Time: O(N \cdot |moves|)
 */
#pragma once

vi grundyTable(ll N, vi moves) {
	vi g(N + 1, 0);
	fore(x, 0, N + 1) {
		set<ll> reachable;
		for (ll m : moves) if (m <= x) reachable.insert(g[x - m]);
		ll mex = 0; // smallest value not in reachable
		while (reachable.count(mex)) mex++;
		g[x] = mex;
	}
	return g;
}
