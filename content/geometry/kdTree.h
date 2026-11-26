/**
 * Author: Yan Farba
 * Date: 2026-11-26
 * Description: Balanced kd-tree for nearest-neighbour queries in 2D.
 *  KDTree<P> is static: built once from a point set, always balanced.
 *  DynKD<P> supports insertions through the logarithmic method. It keeps static
 *  trees whose sizes are distinct powers of two and merges them like a binary
 *  counter, so every tree stays balanced whatever order the points arrive in.
 *  The metric is Manhattan. For squared Euclidean distance, change dist() to
 *  dx*dx + dy*dy; the box pruning works for any metric that grows with |dx| and |dy|.
 *  The query point itself is NOT excluded: if q is in the set, the answer is 0.
 *  P needs public x, y, a constructor P(x, y) and operator< (for tie-breaking).
 * Time: build O(n log n), insert amortized O(log^2 n),
 *  query O(sqrt n) worst case per tree, about log n per tree on typical data.
 */
#pragma once
#include <algorithm>
#include <cstdlib>
#include <limits>
#include <utility>
#include <vector>

template<class P> struct KDTree {
	typedef decltype(P().x) T;
	static T& at(P& p, int d) { return d ? p.y : p.x; }
	static T at(const P& p, int d) { return d ? p.y : p.x; }
	static T dist(const P& a, const P& b) {
		return std::abs(a.x - b.x) + std::abs(a.y - b.y);
	}

	// Implicit tree: the node of range [b, e) is v[(b+e)/2], with the left
	// subtree in [b, m) and the right one in [m+1, e). No pointers, no leaks.
	std::vector<P> v;
	KDTree(std::vector<P> pts = {}) : v(std::move(pts)) { build(0, (int)v.size(), 0); }

	void build(int b, int e, int d) {
		if (e - b <= 1) return;
		int m = (b + e) / 2;
		std::nth_element(v.begin() + b, v.begin() + m, v.begin() + e,
			[&](const P& u, const P& w) { return at(u, d) < at(w, d); });
		build(b, m, !d), build(m + 1, e, !d);
	}

	// lo/hi bound the subtree's region. nth_element puts keys <= v[m] on the
	// left and >= v[m] on the right, so the boundary belongs to both halves.
	void nn(int b, int e, int d, const P& q, P lo, P hi, std::pair<T, P>& best) const {
		if (b >= e) return;
		P c(std::max(lo.x, std::min(hi.x, q.x)), std::max(lo.y, std::min(hi.y, q.y)));
		if (dist(c, q) >= best.first) return;
		int m = (b + e) / 2;
		const P& p = v[m];
		best = std::min(best, {dist(p, q), p});
		P lh = hi, rl = lo;
		at(lh, d) = at(rl, d) = at(p, d);
		if (at(q, d) < at(p, d))
			nn(b, m, !d, q, lo, lh, best), nn(m + 1, e, !d, q, rl, hi, best);
		else
			nn(m + 1, e, !d, q, rl, hi, best), nn(b, m, !d, q, lo, lh, best);
	}

	static constexpr T INF = std::numeric_limits<T>::max();
	// Improves best in place, so several trees can share one running answer.
	void search(const P& q, std::pair<T, P>& best) const {
		nn(0, (int)v.size(), 0, q, P(-INF, -INF), P(INF, INF), best);
	}
	std::pair<T, P> nearest(const P& q) const {
		std::pair<T, P> best(INF, P());
		search(q, best);
		return best;
	}
};

template<class P> struct DynKD {
	typedef KDTree<P> K;
	typedef typename K::T T;
	std::vector<K> lv; // lv[k] holds either 0 or 2^k points
	int n = 0;

	void insert(const P& p) {
		std::vector<P> c{p};
		size_t k = 0;
		for (; k < lv.size() && !lv[k].v.empty(); k++) {
			c.insert(c.end(), lv[k].v.begin(), lv[k].v.end());
			lv[k].v.clear();
		}
		if (k == lv.size()) lv.emplace_back();
		lv[k] = K(std::move(c));
		n++;
	}

	// Returns {INF, P()} when empty. The largest trees are searched first so
	// the smaller ones get pruned early.
	std::pair<T, P> nearest(const P& q) const {
		std::pair<T, P> best(K::INF, P());
		for (int k = (int)lv.size() - 1; k >= 0; k--) lv[k].search(q, best);
		return best;
	}
};
