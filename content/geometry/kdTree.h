/**
 * Author: Stanford, rewritten after CMU kd-tree notes (C. Kingsford)
 * Date: 2026-11-24
 * Source: https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/kdtrees.pdf
 * Description: 2D kd-tree with insertion, deletion and nearest neighbour.
 * Node at depth $d$ splits on coordinate $d \bmod 2$: left subtree is
 * strictly smaller, right is $\geq$. Deletion replaces the node by the
 * min (in its cutting dim) of the right subtree, or of the left subtree
 * which then becomes the right one. Not rebalanced: rebuild if needed.
 * Time: build $O(n \log n)$, insert/delete $O(\text{depth})$,
 * nearest $O(\log n)$ on average for random points.
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

typedef ll T;
typedef Point<T> P;
const T INF = numeric_limits<T>::max();
T& at(P& p, ll d) { return d ? p.y : p.x; }

struct KDTree {
	struct Node { P p; Node *l = 0, *r = 0; };
	Node* root = 0;
	KDTree(vector<P> v = {}) { root = build(ALL(v), 0); }
	template<class I> Node* build(I b, I e, ll d) {
		if (b == e) return 0;
		I m = b + (e - b) / 2;
		nth_element(b, m, e, [&](P& u, P& w) {
			return at(u,d) < at(w,d); });
		T v = at(*m, d); // equal keys must go right
		m = partition(b, m, [&](P& u) { return at(u,d) < v; });
		return new Node{*m, build(b, m, !d), build(m + 1, e, !d)};
	}
	void ins(Node*& t, P p, ll d) {
		if (!t) t = new Node{p};
		else ins(at(p,d) < at(t->p,d) ? t->l : t->r, p, !d);
	}
	Node* mn(Node* t, ll k, ll d) { // node with min coordinate k
		if (!t) return t;
		Node* c[] = {mn(t->l,k,!d), d != k ? mn(t->r,k,!d) : 0};
		for (Node* b : c) if (b && at(b->p,k) < at(t->p,k)) t = b;
		return t;
	}
	Node* del(Node* t, P p, ll d) { // removes one copy of p
		if (!t) return t;
		if (t->p == p) {
			if (t->r)
				t->p = mn(t->r,d,!d)->p, t->r = del(t->r,t->p,!d);
			else if (t->l) {
				t->p = mn(t->l, d, !d)->p;
				t->r = del(t->l, t->p, !d), t->l = 0;
			} else return delete t, nullptr;
		} else if (at(p,d) < at(t->p,d)) t->l = del(t->l, p, !d);
		else t->r = del(t->r, p, !d);
		return t;
	}
	// lo, hi: bounding box of the subtree rooted at t
	void nn(Node* t, P q, ll d, P lo, P hi, pair<T,P>& best) {
		P c = q;
		fore(i,0,2) at(c,i) = max(at(lo,i), min(at(hi,i),at(c,i)));
		if (!t || (c - q).dist2() >= best.fst) return;
		// uncomment if we should not find the point itself:
		// if (!(t->p == q))
		best = min(best, {(t->p - q).dist2(), t->p});
		P lh = hi, rl = lo;
		at(lh,d) = at(rl,d) = at(t->p,d);
		if (at(q,d) < at(t->p,d)) nn(t->l,q,!d,lo,lh,best),
			nn(t->r,q,!d,rl,hi,best);
		else nn(t->r,q,!d,rl,hi,best), nn(t->l,q,!d,lo,lh,best);
	}
	void insert(P p) { ins(root, p, 0); }
	void erase(P p) { root = del(root, p, 0); }
	// nearest point to q, squared dist ({INF, P()} if empty)
	pair<T,P> nearest(P q) {
		pair<T,P> best{INF, P()};
		nn(root, q, 0, P(-INF,-INF), P(INF,INF), best);
		return best;
	}
};
