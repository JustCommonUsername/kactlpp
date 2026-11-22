/**
 * Author: team, rewritten for readability
 * Date: 2026-11-22
 * License: CC0
 * Source: folklore
 * Description: Implicit treap: an array with insert/erase at any
 * position, range reverse and cut-paste of ranges, all in $O(\log N)$.
 * Positions are 0-based and never stored: a node's index is computed
 * from subtree sizes. split(t, k) gives (first k elements, rest),
 * merge(a, b) glues a in front of b. Every operation is: split into
 * pieces, change one piece, merge back (see reverse\_range).
 * Cut-paste [l, r) to the front: split into A, B, C, root = merge(merge(B, A), C).
 * Range sum/min: add a field to Node and update it in recalc().
 * Usage: Node* root = nullptr; fore(i,0,n) root = merge(root, new Node(a[i]));
 * reverse_range(root, l, r); vi res; to_vector(root, res);
 * Time: $O(\log N)$ expected per operation
 */
#pragma once

mt19937 treap_rng(12345);
struct Node {
	ll val, priority, size = 1;
	bool rev = false; // lazy: children still have to be swapped
	Node *left = nullptr, *right = nullptr;
	Node(ll v) : val(v), priority(treap_rng()) {}
};
ll sz(Node* t) { return t ? t->size : 0; }
void recalc(Node* t) { t->size = 1 + sz(t->left) + sz(t->right); }
void push(Node* t) { // apply the lazy reverse one level down
	if (t && t->rev) {
		swap(t->left, t->right);
		if (t->left) t->left->rev ^= 1;
		if (t->right) t->right->rev ^= 1;
		t->rev = false;
	}
}

// (first k elements of t, the rest)
pair<Node*, Node*> split(Node* t, ll k) {
	if (!t) return {nullptr, nullptr};
	push(t);
	if (sz(t->left) < k) { // t and its left part go to the first half
		auto [a, b] = split(t->right, k - sz(t->left) - 1);
		t->right = a;
		recalc(t);
		return {t, b};
	}
	auto [a, b] = split(t->left, k);
	t->left = b;
	recalc(t);
	return {a, t};
}

// all elements of a, then all elements of b
Node* merge(Node* a, Node* b) {
	if (!a || !b) return a ? a : b;
	if (a->priority > b->priority) { // a becomes the root
		push(a);
		a->right = merge(a->right, b);
		recalc(a);
		return a;
	}
	push(b);
	b->left = merge(a, b->left);
	recalc(b);
	return b;
}

void insert_at(Node*& root, ll pos, ll val) { // new element gets index pos
	auto [a, b] = split(root, pos);
	root = merge(merge(a, new Node(val)), b);
}
void erase_at(Node*& root, ll pos) {
	auto [a, b] = split(root, pos);
	auto [removed, c] = split(b, 1);
	root = merge(a, c);
}
void reverse_range(Node*& root, ll l, ll r) { // reverses [l, r)
	auto [a, b] = split(root, l);
	auto [mid, c] = split(b, r - l);
	if (mid) mid->rev ^= 1; // O(1): just flip the flag
	root = merge(merge(a, mid), c);
}
ll get(Node* t, ll k) { // element at index k
	push(t);
	if (k < sz(t->left)) return get(t->left, k);
	if (k == sz(t->left)) return t->val;
	return get(t->right, k - sz(t->left) - 1);
}
void to_vector(Node* t, vi& out) { // the whole array, in order
	if (!t) return;
	push(t);
	to_vector(t->left, out);
	out.pb(t->val);
	to_vector(t->right, out);
}
