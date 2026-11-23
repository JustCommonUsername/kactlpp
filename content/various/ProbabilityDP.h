/**
 * Author: team
 * Date: 2026-11-23
 * License: CC0
 * Source: folklore
 * Description: Probability / expected value with recursion + dp. Same
 * shape as GameDP.h, only the combine step is a weighted sum.
 * For a probability: f(state) = sum over moves of p(move) * f(next); at the
 * end 1 if you succeeded, else 0.
 * For an expected value: f(state) = cost of this step + sum over moves of
 * p(move) * f(next); at the end 0.
 * Self-loop (stay with prob p): f = 1 + p f + rest, so
 * f = (1 + rest) / (1 - p); solve it before recursing.
 * Answer mod $10^9+7$: use ll and replace / 6 by * inverse(6) \% MOD
 * (ModularArithmetic.h). Print doubles with fixed << setprecision(9).
 * Linearity of expectation: E[X + Y] = E[X] + E[Y] always, often no dp needed.
 * Usage: dp.assign(n + 1, vector<double>(s + 1, -1)); prob(0, s);
 * dp2.assign(goal, -1); expected(0);
 * Time: $O(\textrm{states} \cdot \textrm{moves})$
 */
#pragma once

// (1) n dice, probability that the sum is exactly s
ll n;
vector<vector<double>> dp; // dp[i][s], -1 = unknown

// probability that throws i..n-1 add up to exactly s
double prob(ll i, ll s) {
	if (s < 0) return 0; // overshot: impossible
	if (i == n) return s == 0 ? 1 : 0; // no throws left
	double& res = dp[i][s];
	if (res != -1) return res;
	res = 0;
	for (ll face = 1; face <= 6; face++) {
		res += prob(i + 1, s - face) / 6; // each face: prob 1/6
	}
	return res;
}

// (2) start at 0, each throw moves 1..6 forward,
// expected number of throws to reach position >= goal
ll goal;
vector<double> dp2; // -1 = unknown

double expected(ll pos) {
	if (pos >= goal) return 0; // already there
	double& res = dp2[pos];
	if (res != -1) return res;
	res = 1; // this throw
	for (ll face = 1; face <= 6; face++) {
		res += expected(pos + face) / 6;
	}
	return res;
}
