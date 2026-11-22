/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: STL patterns that are easy to get wrong in a contest.
 * \texttt{lower\_bound} = first $\ge$ x, \texttt{upper\_bound} = first > x.
 * Use the member \texttt{s.lower\_bound(x)} on set/map, not \texttt{std::lower\_bound}
 * (that one is $O(N)$ there). \texttt{priority\_queue} is a max-heap.
 * A comparator must be strict (\texttt{<}, never \texttt{<=}).
 */
#pragma once

void stl_examples() {
	vi v = {5, 1, 4};
	sort(ALL(v), greater<ll>());                    // decreasing
	sort(ALL(v), [](ll a, ll b) { return abs(a) < abs(b); });
	ll idx = lower_bound(ALL(v), 4) - v.begin();    // v must be sorted
	ll cnt = upper_bound(ALL(v), 4) - lower_bound(ALL(v), 4);

	set<ll> s = {1, 5, 9};
	auto it = s.lower_bound(6);              // -> 9
	if (it != s.begin()) --it;               // largest < 6 -> 5
	multiset<ll> ms = {1, 1, 2};
	ms.erase(ms.find(1));                    // erase ONE copy only

	map<string, ll> freq;
	freq["abc"]++;                           // missing key starts at 0
	for (auto& [key, value] : freq) cout << key << value; // by key

	priority_queue<ll, vi, greater<ll>> min_heap;
	priority_queue<pair<ll, ll>> max_heap;    // largest first, then second

	// fixed precision output of doubles
	cout << fixed << setprecision(9) << 3.14159265358979 << '\n';
	// __int128 has no cout: convert to string by hand
	__int128 big = (__int128)1e18 * 1000;
	string out;
	do out += char('0' + big % 10), big /= 10; while (big > 0);
	reverse(ALL(out));
	// read until end of input
	ll x;
	while (cin >> x) {}
	string line;
	getline(cin >> ws, line);                // whole line, skip whitespace
	(void)idx, (void)cnt;
}
