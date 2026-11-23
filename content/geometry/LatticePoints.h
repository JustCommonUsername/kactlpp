/**
 * Author: Yan Farba
 * Date: 2026-11-23
 * License: CC0
 * Source: me
 * Description: Given the polygon as a set of adjacent points (ordered clockwise or counter-clockwise)
 *  with integer coordinates, compute it's lattice points (points with integer coordinates inside and on it's boundary).
 *  Uses Pick's theorem and polygon area.
 * Usage:
 *  typedef Point<ll> p;
 *  vector<P> v = {p1, p2, ...} // adjacent
 *  ll latnum = lattice_points(v);
 * Status: Used, works well
 */
#pragma once

#include "Point.h"
#include "PolygonArea.h"
#define ll long long

// gcd(min, max)
template<class T>
ll boundary(const vector<Point<T>>& v) {
    ll xx = abs(v.back().x - v[0].x), yy = abs(v.back().y - v[0].y);
    ll res = gcd(min(xx, yy), max(xx, yy));
    fore(i, 0, SZ(v) - 1) {
        xx = abs(v[i + 1].x - v[i].x);
        yy = abs(v[i + 1].y - v[i].y);
        res += gcd(min(xx, yy), max(xx, yy));
    }
    return res;
}

ll lattice_points(const vector<Point<T>>& v) {
    ll area = abs(polygonArea2<ll>(v));
    ll b = boundary(v);
    return area / 2 - b / 2 + 1;
}
