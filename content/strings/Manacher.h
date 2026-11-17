/**
 * Author: User adamant on CodeForces, rewritten for readability
 * Source: http://codeforces.com/blog/entry/12143
 * Description: Palindromes. Builds \texttt{t = \#s0\#s1\#...\#} and returns
 * \texttt{rad[i]} = radius of the longest palindrome in \texttt{t} centered at i.
 * The palindrome of \texttt{s} centered there has length \texttt{rad[i] - 1}
 * and starts at \texttt{(i - rad[i] + 1) / 2}.
 * Time: O(N)
 */
#pragma once

vi manacher(const string& s) {
	string t = "#";
	for (char c : s) t += c, t += '#';
	ll n = SZ(t);
	vi rad(n, 0);
	// [l, r) = palindrome that reaches the furthest to the right
	ll l = 0, r = 0;
	fore(i, 0, n) {
		if (i < r) rad[i] = min(r - i, rad[l + r - 1 - i]);
		while (i - rad[i] >= 0 && i + rad[i] < n &&
		       t[i - rad[i]] == t[i + rad[i]])
			rad[i]++;
		if (i + rad[i] > r) l = i - rad[i] + 1, r = i + rad[i];
	}
	return rad;
}
