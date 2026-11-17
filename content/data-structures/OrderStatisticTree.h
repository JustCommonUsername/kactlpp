/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacked from the GNU pb_ds documentation
 * Description: A \texttt{set} that can also find the $k$-th smallest
 * element and the number of elements smaller than a value.
 * Not a multiset! For duplicates store \texttt{pair(value, uniqueId)}.
 * Time: O(\log N)
 */
#pragma once

#include <ext/pb_ds/assoc_container.hpp> /** keep-include */
using namespace __gnu_pbds;

template<class T>
using OrderedSet = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;

void example() {
	OrderedSet<ll> s;
	s.insert(8), s.insert(10), s.insert(3);
	assert(*s.find_by_order(0) == 3); // 0-th smallest element
	assert(s.order_of_key(9) == 2);   // number of elements < 9
	s.erase(8);
}
