/**
 * Author: Ulf Lundstrom, rewritten for readability
 * Date: 2009-08-03
 * License: CC0
 * Source: My head
 * Description: Square matrix with multiplication and fast power
 * modulo \texttt{MOD}. Typical use: linear recurrences, e.g.
 * Fibonacci with $\begin{pmatrix}1&1\\1&0\end{pmatrix}^n$, or counting
 * walks of length $k$ in a graph (adjacency matrix to the power $k$).
 * Usage: Matrix A(2); A.d = {{1,1},{1,0}}; ll fib = A.power(n).d[0][1];
 * Time: $O(N^3)$ per multiplication, $O(N^3 \log p)$ for power.
 */
#pragma once

#include "../number-theory/ModularArithmetic.h" // only for MOD

struct Matrix {
	ll n;
	vector<vi> d;
	Matrix(ll size) : n(size), d(size, vi(size, 0)) {}

	Matrix operator*(const Matrix& other) const {
		Matrix res(n);
		// i-k-j loop order: the inner loop walks rows, cache friendly
		fore(i, 0, n) fore(k, 0, n) {
			if (d[i][k] == 0) continue;
			fore(j, 0, n) res.d[i][j] = (res.d[i][j] + d[i][k] * other.d[k][j]) % MOD;
		}
		return res;
	}

	// this^p by repeated squaring
	Matrix power(ll p) const {
		Matrix res(n), base = *this;
		fore(i, 0, n) res.d[i][i] = 1;
		while (p > 0) {
			if (p & 1) res = res * base;
			base = base * base;
			p >>= 1;
		}
		return res;
	}
};
