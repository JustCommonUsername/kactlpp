/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Trie over lowercase letters. \texttt{countEnd[v]} = number of
 * words ending at node v, \texttt{countPass[v]} = number of words through v
 * (= number of words with that prefix). For max XOR of numbers, use a
 * binary trie with 2 children and insert the bits from high to low.
 * Usage: Trie t; t.insert("abc"); t.countPrefix("ab");
 * Time: O(|word|) per operation.
 */
#pragma once

struct Trie {
	vector<array<ll, 26>> next; // next[v][c] = child or -1
	vi countEnd, countPass;
	Trie() { newNode(); }

	ll newNode() {
		next.pb({}), next.back().fill(-1);
		countEnd.pb(0), countPass.pb(0);
		return SZ(next) - 1;
	}

	void insert(const string& word) {
		ll v = 0;
		countPass[v]++;
		for (char ch : word) {
			ll c = ch - 'a';
			if (next[v][c] == -1) {
				ll child = newNode(); // may reallocate next
				next[v][c] = child;
			}
			v = next[v][c];
			countPass[v]++;
		}
		countEnd[v]++;
	}

	// node of the prefix, or -1 if no word starts with it
	ll find(const string& prefix) {
		ll v = 0;
		for (char ch : prefix) {
			v = next[v][ch - 'a'];
			if (v == -1) return -1;
		}
		return v;
	}

	ll countPrefix(const string& p) { ll v = find(p); return v < 0 ? 0 : countPass[v]; }
	ll countWord(const string& w) { ll v = find(w); return v < 0 ? 0 : countEnd[v]; }
};
