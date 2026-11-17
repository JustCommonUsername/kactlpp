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

const ll MOD = 1e9 + 7;

struct Matrix {
	ll n;
	vector<vi> d;
	Matrix(ll N) : n(N), d(N, vi(N, 0)) {}

	Matrix operator*(const Matrix& other) const {
		Matrix res(n);
		fore(i, 0, n) fore(k, 0, n) fore(j, 0, n)
			res.d[i][j] = (res.d[i][j] + d[i][k] * other.d[k][j]) % MOD;
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
