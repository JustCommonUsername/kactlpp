#include "../utilities/template.h"

#include "../../content/geometry/ConvexHull.h"
typedef Point<ll> P;
#include "../../content/geometry/ConvexHullCollinear.h"

// Brute force: all distinct points on the hull boundary, CCW from the
// lexicographically smallest one. If all points are collinear: sorted.
vector<P> bruteCollinear(vector<P> v) {
	sort(ALL(v)); v.erase(unique(ALL(v)), v.end());
	ll n = SZ(v);
	bool line = true;
	for (P p : v) line &= n < 3 || v[0].cross(v.back(), p) == 0;
	if (line) return v;
	vector<P> b;
	for (P p : v) {
		bool ok = false;
		for (P q : v) if (!(q == p)) {
			ll l = 0, r = 0;
			for (P x : v) l |= p.cross(q, x) > 0, r |= p.cross(q, x) < 0;
			ok |= !l || !r;
		}
		if (ok) b.pb(p);
	}
	P o = b[0]; // smallest point: all others lie in a half-plane
	sort(b.begin() + 1, b.end(), [&](P a, P c) {
		ll x = o.cross(a, c);
		return x ? x > 0 : (a - o).dist2() < (c - o).dist2();
	});
	ll k = SZ(b) - 1; // last ray goes back to o: reverse it
	while (k > 1 && o.cross(b[k - 1], b.back()) == 0) k--;
	reverse(b.begin() + k, b.end());
	return b;
}

vector<P> bruteStrict(vector<P> v) {
	vector<P> b = bruteCollinear(v), r;
	ll n = SZ(b);
	if (n <= 2 || b[0].cross(b[1], b.back()) == 0)
		return n ? vector<P>{b[0], b.back()} : b;
	fore(i, 0, n)
		if (b[(i + n - 1) % n].cross(b[i], b[(i + 1) % n])) r.pb(b[i]);
	return r;
}

int main() {
	mt19937 rng(1);
	auto rnd = [&](ll a, ll b) { return a + ll(rng() % (b - a + 1)); };
	fore(it, 0, 200000) {
		ll G = rnd(1, it % 10 ? 4 : 30), n = rnd(0, it % 10 ? 10 : 60);
		vector<P> v(n);
		for (P& p : v) p = P(rnd(-G, G), rnd(-G, G));
		if (rng() % 4 == 0) for (P& p : v) p.y = 2 * p.x + 1; // a line
		if (rng() % 4 == 0 && n) v.pb(v[rnd(0, n - 1)]); // duplicate
		shuffle(ALL(v), rng);
		vector<P> s = bruteStrict(v), c = bruteCollinear(v);
		if (SZ(s) == 2 && s[0] == s[1]) s.pop_back();
		assert(convexHull(v) == s);
		assert(convexHullCollinear(v) == c);
	}
	cout << "Tests passed!" << endl;
}
