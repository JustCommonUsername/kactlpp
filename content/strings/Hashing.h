/**
 * Author: Simon Lindholm, rewritten for readability
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Polynomial string hashing modulo $2^{61}-1$ with a random
 * base, so anti-hash tests cannot break it. \texttt{get(l, r)} is the
 * hash of \texttt{s[l..r-1]}; equal substrings have equal hashes.
 * Use for substring comparison, LCP by binary search, palindromes
 * (hash of the reversed string), counting distinct substrings.
 * Usage: Hash h(s); if (h.get(0, 3) == h.get(5, 8)) ...
 * Time: O(n) build, O(1) per query.
 */
#pragma once

typedef unsigned long long ull;
const ull HMOD = (1ULL << 61) - 1;

ull mulMod(ull a, ull b) { return (__uint128_t)a * b % HMOD; }

const ull BASE = mt19937_64(
	chrono::steady_clock::now().time_since_epoch().count())() % (HMOD - 1000) + 500;

struct Hash {
	// pre[i] = hash of s[0..i-1], pw[i] = BASE^i
	vector<ull> pre, pw;
	Hash(const string& s) : pre(SZ(s) + 1, 0), pw(SZ(s) + 1, 1) {
		fore(i, 0, SZ(s)) {
			pre[i + 1] = (mulMod(pre[i], BASE) + (unsigned char)s[i]) % HMOD;
			pw[i + 1] = mulMod(pw[i], BASE);
		}
	}
	ull get(ll l, ll r) { // hash of s[l..r-1]
		return (pre[r] + HMOD - mulMod(pre[l], pw[r - l])) % HMOD;
	}
};
