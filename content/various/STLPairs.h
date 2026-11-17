/**
 * Author: folklore, written for readability
 * Date: 2026-11-17
 * License: CC0
 * Source: folklore
 * Description: Pairs and comparators. Pairs compare lexicographically:
 * first by \texttt{.fst}, then by \texttt{.snd}. To search by the first value
 * only, pair x with the smallest/largest possible second value.
 * \texttt{sort} comparator: return true if a must come BEFORE b.
 * \texttt{priority\_queue} comparator: return true if a has LOWER priority
 * than b (the top is the "largest"), so it looks reversed compared to sort.
 * Comparators must be strict: \texttt{<} or \texttt{>}, never \texttt{<=}.
 */
#pragma once

void pairExamples() {
	vector<ii> v = {{3, 1}, {1, 5}, {3, 0}, {2, 2}};

	// ---- sorting ----
	sort(ALL(v));                                  // (1,5) (2,2) (3,0) (3,1)
	sort(ALL(v), greater<ii>());                   // decreasing
	sort(ALL(v), [](const ii& a, const ii& b) {    // by second, then first
		return make_pair(a.snd, a.fst) < make_pair(b.snd, b.fst);
	});
	sort(ALL(v), [](const ii& a, const ii& b) {    // first desc, second asc
		if (a.fst != b.fst) return a.fst > b.fst;
		return a.snd < b.snd;
	});
	// more keys: compare tuples, e.g. tie(a.x, b.y) < tie(b.x, a.y)

	// ---- binary search on a sorted vector<pair> ----
	sort(ALL(v));
	ll x = 3;
	// first element with .fst >= x
	auto it1 = lower_bound(ALL(v), ii(x, LLONG_MIN));
	// first element with .fst > x
	auto it2 = upper_bound(ALL(v), ii(x, LLONG_MAX));
	ll countX = it2 - it1;                         // elements with .fst == x
	// search by .snd only (v sorted by .snd): custom compare
	auto it3 = lower_bound(ALL(v), x,
		[](const ii& p, ll val) { return p.snd < val; });

	// ---- set<pair>: e.g. disjoint intervals {start, end} ----
	set<ii> intervals = {{1, 3}, {5, 8}, {10, 12}};
	ll point = 6;
	// interval with the largest start <= point
	auto it = intervals.upper_bound(ii(point, LLONG_MAX));
	if (it != intervals.begin()) {
		--it;
		bool inside = it->fst <= point && point <= it->snd; // (5, 8)
		(void)inside;
	}
	// smallest pair with .fst >= point (or end())
	auto nxt = intervals.lower_bound(ii(point, LLONG_MIN));  // (10, 12)
	intervals.erase(ii(1, 3));                     // erase by value

	// ---- map with pair keys / values ----
	map<ii, ll> cost;                              // ordered: works as is
	cost[{1, 2}] = 7;
	if (cost.count({1, 2})) cost[{1, 2}]++;
	// unordered_map needs a hash for pairs:
	struct PairHash {
		size_t operator()(const ii& p) const {
			return hash<ll>()(p.fst) * 1000003 ^ hash<ll>()(p.snd);
		}
	};
	unordered_map<ii, ll, PairHash> seen;
	seen[{3, 4}] = 1;

	// ---- priority_queue with pairs ----
	priority_queue<ii> maxHeap;                    // largest .fst on top
	priority_queue<ii, vector<ii>, greater<ii>> minHeap; // smallest on top
	minHeap.push({5, 1}), minHeap.push({2, 9});
	auto [d, node] = minHeap.top();                // (2, 9), Dijkstra style
	maxHeap.push({-d, node});                      // or: negate for min-heap

	// lambda comparator: smallest .snd on top
	auto bySecond = [](const ii& a, const ii& b) { return a.snd > b.snd; };
	priority_queue<ii, vector<ii>, decltype(bySecond)> pq(bySecond);
	pq.push({1, 7}), pq.push({2, 3});              // top = (2, 3)

	// struct comparator (usable as a type, e.g. in a global)
	struct LargestSecond {
		bool operator()(const ii& a, const ii& b) const { return a.snd < b.snd; }
	};
	priority_queue<ii, vector<ii>, LargestSecond> pq2; // top = largest .snd

	// set with a custom order (no two "equal" elements allowed!)
	set<ii, LargestSecond> byValue;

	// ---- other algorithms on pairs ----
	auto mn = *min_element(ALL(v), [](const ii& a, const ii& b) {
		return a.snd < b.snd;                      // pair with smallest .snd
	});
	bool found = binary_search(ALL(v), ii(2, 2));  // exact pair, v sorted
	auto [lo, hi] = equal_range(ALL(v), ii(3, 0)); // range of equal pairs
	(void)countX, (void)it3, (void)nxt, (void)mn, (void)found, (void)lo, (void)hi;
}

// own struct in sort / set / priority_queue: define operator<
struct Event {
	ll time, type, id;
	bool operator<(const Event& o) const {         // by time, then type
		return tie(time, type) < tie(o.time, o.type);
	}
};
// priority_queue<Event> = latest time on top; for earliest use
// priority_queue<Event, vector<Event>, greater<Event>> + operator>
