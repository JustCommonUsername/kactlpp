/**
 * Author: Per Austrin, Simon Lindholm, rewritten for readability
 * Date: 2004-02-08
 * License: CC0
 * Source: https://cp-algorithms.com/linear_algebra/linear-system-gauss.html
 * Description: Solves $A x = b$ with Gauss-Jordan elimination
 * ($n$ equations, $m$ unknowns, \texttt{a} is $n \times (m+1)$ with $b$ as the last column).
 * Returns 0 if there is no solution, 1 if it is unique and 2 if there are
 * infinitely many (then \texttt{x} is one of them, free variables are 0).
 * For mod p: replace division by multiplication with the inverse and
 * compare with 0 instead of EPS. For XOR systems use bitset rows.
 * Time: O(n m \min(n, m))
 */
#pragma once

const double EPS = 1e-9;

ll gauss(vector<vector<double>> a, vector<double>& x) {
	ll n = SZ(a), m = SZ(a[0]) - 1;
	vi where(m, -1); // where[col] = row of the pivot of col
	for (ll col = 0, row = 0; col < m && row < n; col++) {
		// partial pivoting: largest absolute value in this column
		ll best = row;
		fore(i, row, n) if (fabs(a[i][col]) > fabs(a[best][col])) best = i;
		if (fabs(a[best][col]) < EPS) continue;
		swap(a[best], a[row]);
		where[col] = row;
		// eliminate this column from all other rows
		fore(i, 0, n) if (i != row) {
			double factor = a[i][col] / a[row][col];
			fore(j, col, m + 1) a[i][j] -= a[row][j] * factor;
		}
		row++;
	}
	x.assign(m, 0);
	fore(col, 0, m)
		if (where[col] != -1) x[col] = a[where[col]][m] / a[where[col]][col];
	// check that every equation holds
	fore(i, 0, n) {
		double sum = 0;
		fore(j, 0, m) sum += x[j] * a[i][j];
		if (fabs(sum - a[i][m]) > EPS) return 0;
	}
	fore(col, 0, m) if (where[col] == -1) return 2;
	return 1;
}
