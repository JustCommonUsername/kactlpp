#include "../utilities/template.h"

#include "../../content/geometry/kdTree.h"

int main() {
	mt19937 rng(2);
	fore(it, 0, 3000) {
		ll R = rng() % 2 ? 5 : 1000000; // small range => many duplicates
		auto rp = [&]() { return P(ll(rng() % (2*R+1)) - R, ll(rng() % (2*R+1)) - R); };
		vector<P> v(rng() % 50);
		for (P& p : v) p = rp();
		KDTree kd(v);
		multiset<P> ms(ALL(v));
		fore(op, 0, 200) {
			ll t = rng() % 3;
			if (t == 0) { P p = rp(); kd.insert(p); ms.insert(p); }
			else if (t == 1) {
				P p = !ms.empty() && rng() % 4 ? *next(ms.begin(), rng() % SZ(ms)) : rp();
				kd.erase(p);
				if (ms.count(p)) ms.erase(ms.find(p));
			} else {
				P q = rp();
				T best = INF;
				for (P p : ms) best = min(best, (p - q).dist2());
				auto r = kd.nearest(q);
				assert(r.fst == best);
				if (best != INF) assert(ms.count(r.snd) && (r.snd - q).dist2() == best);
			}
		}
	}
	cout << "Tests passed!" << endl;
}
