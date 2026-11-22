/**
 * Author: team
 * Date: 2026-11-22
 * License: CC0
 * Source: folklore
 * Description: Two players move in turns and both play optimally, so
 * every state has a fixed result: try all moves recursively and store
 * it in dp. Judge a state from the player TO MOVE. Needs a game
 * without cycles (every move makes progress, e.g. fewer stones).
 * (1) Win/lose: winning iff SOME move leads to a losing state for the
 * opponent, losing iff ALL moves lead to winning states (no move =
 * losing if whoever cannot move loses).
 * (2) Score: P1 maximizes and P2 minimizes P1's total, so take the max
 * on P1's turn and the min on P2's turn. Greedy is wrong: on
 * [8, 15, 3, 7] taking 8 gives 15, minimax takes 7 and gets 22.
 * To adapt: state = smallest info describing the game, then change
 * the moves and the end. If n is too big for dp: print is\_winning(i)
 * for small i and look for a pattern (here: losing iff n \% 4 == 0).
 * Several independent games at once: use Grundy.h instead.
 * Usage: dp.assign(n + 1, -1); is_winning(n);
 * dp2.assign(n, vector<array<ll, 2>>(n, {-1, -1})); minimax(0, n - 1, 1);
 * Time: $O(\textrm{states} \cdot \textrm{moves})$
 */
#pragma once

// (1) win/lose. state = number of stones, take 1, 2 or 3
vector<int> dp; // -1 = unknown, 0 = losing, 1 = winning

bool is_winning(ll state) {
	if (dp[state] != -1) return dp[state];
	bool win = false; // no move = losing
	// try every move from this state
	for (ll take : {1, 2, 3}) {          // <- your moves here
		if (take > state) continue;      // <- move not allowed
		ll next = state - take;          // <- state after the move
		if (!is_winning(next)) win = true; // opponent loses
	}
	dp[state] = win;
	return win;
}

// (2) minimax. take a[l] or a[r]; returns player 1's total
vi a;
vector<vector<array<ll, 2>>> dp2; // [l][r][turn], -1 = unknown

// turn = 1 if player 1 moves
ll minimax(ll l, ll r, ll turn) {
	if (l > r) return 0; // <- game over: final score
	ll& res = dp2[l][r][turn];
	if (res != -1) return res;
	// the two moves: take the left or the right end
	ll take_left  = minimax(l + 1, r, 1 - turn);
	ll take_right = minimax(l, r - 1, 1 - turn);
	if (turn == 1) // player 1: maximize
		res = max(a[l] + take_left, a[r] + take_right);
	else // player 2: minimize (P2's numbers don't count)
		res = min(take_left, take_right);
	return res;
}
