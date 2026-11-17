/**
 * Author: Simon Lindholm, rewritten for readability
 * Date: 2016-09-06
 * License: CC0
 * Source: folklore
 * Description: Determinant of a square matrix with Gaussian elimination.
 * Swapping two rows flips the sign; the result is the product of the pivots.
 * For an exact result mod p, use \texttt{ll}, multiply by the modular
 * inverse instead of dividing and check \texttt{!= 0} instead of EPS.
 * Time: $O(N^3)$
 */
#pragma once

double determinant(vector<vector<double>> a) {
	ll n = SZ(a);
	double det = 1;
	fore(col, 0, n) {
		ll best = col;
		fore(i, col + 1, n) if (fabs(a[i][col]) > fabs(a[best][col])) best = i;
		if (fabs(a[best][col]) < 1e-12) return 0;
		if (best != col) swap(a[best], a[col]), det = -det;
		det *= a[col][col];
		fore(i, col + 1, n) {
			double factor = a[i][col] / a[col][col];
			fore(j, col, n) a[i][j] -= factor * a[col][j];
		}
	}
	return det;
}
