/**
 * Author: Simon Lindholm, rewritten for readability
 * Date: 2015-02-11
 * License: CC0
 * Source: Wikipedia
 * Description: Integral of $f$ over $[a, b]$ with Simpson's rule on $2n$
 * intervals. The error shrinks like $h^4$; check that the answer is
 * stable when increasing $n$.
 * Usage: double area = simpson(0, 1, [](double x) { return x * x; });
 * Time: $O(n)$ evaluations of $f$.
 */
#pragma once

double simpson(double a, double b, auto f, ll n = 1000) {
	double h = (b - a) / (2 * n);
	double sum = f(a) + f(b);
	// weights 1 4 2 4 2 ... 4 1
	fore(i, 1, 2 * n) sum += f(a + i * h) * (i % 2 == 1 ? 4 : 2);
	return sum * h / 3;
}
