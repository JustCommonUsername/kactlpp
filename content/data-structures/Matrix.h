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

template<class T, int N> struct Matrix {
	typedef Matrix M;
	array<array<T, N>, N> d{};
	M operator*(const M& m) const {
		M a;
		rep(i,0,N) rep(j,0,N)
			rep(k,0,N) a.d[i][k] += d[i][j] * m.d[j][k];
		return a;
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
