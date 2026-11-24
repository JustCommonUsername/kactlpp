/**
 * Author: Yan Farba
 * Date: 2026-11-24
 * License: Unlicense
 * Description:
 * \descriptionimage{content/geometry/ConvexHull}
 * Returns a vector of the points of the convex hull in counter-clockwise order.
 * Points on the edge of the hull between two other points \textbf{are} considered part of the hull.
 * Duplicates are removed. If all points are collinear, returns them sorted.
 * Time: O(n \log n)
 * Status: stress-tested
*/
#pragma once

#include "Point.h"

template<class P>
vector<P> convexHullCollinear(vector<P> pts) {
	sort(ALL(pts));
	// uncomment if the duplicates need to be removed
	// pts.erase(unique(ALL(pts)), pts.end());
	bool line = true; // all collinear: return them sorted
	for (P p : pts) line &= pts[0].cross(pts.back(), p) == 0;
	if (line) return pts;
	vector<P> h(2 * SZ(pts));
	ll s = 0, t = 0;
	for (ll it = 2; it--; s = --t, reverse(ALL(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) < 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t};
}
