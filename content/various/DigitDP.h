/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Digit DP, example: count $x \in [0, N]$ whose digit sum is
 * S. Go through the digits of N from the left; \texttt{tight} = the prefix
 * so far equals the prefix of N (so the next digit is limited).
 * For $[L, R]$ use \texttt{count(R) - count(L - 1)}. Add more state (last
 * digit, remainder, "started") to the memo for other conditions.
 * Time: $O(\text{digits} \cdot \text{states} \cdot 10)$
 */
#pragma once

string digits;
ll target;
// memo[pos][sum][tight], -1 = not computed
vector<vector<array<ll, 2>>> memo;

ll go(ll pos, ll sum, bool tight) {
	if (sum > target) return 0;
	if (pos == SZ(digits)) return sum == target;
	ll& res = memo[pos][sum][tight];
	if (res != -1) return res;
	res = 0;
	ll limit = tight ? digits[pos] - '0' : 9;
	fore(d, 0, limit + 1)
		res += go(pos + 1, sum + d, tight && d == limit);
	return res;
}

ll count_digit_sum(ll N, ll S) {
	if (N < 0) return 0;
	digits = to_string(N), target = S;
	memo.assign(SZ(digits), vector<array<ll, 2>>(S + 1, {-1, -1}));
	return go(0, 0, true);
}
