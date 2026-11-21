// Random test generator for tester.py: ./caseGen <seed>
// Same seed = same test. Keep tests SMALL so the brute force
// is fast and failing cases are easy to read.
// Delete the parts your input format does not need.
#include <bits/stdc++.h>
using namespace std;
mt19937 rng;
long long rnd(long long a, long long b) { // uniform in [a, b]
	return uniform_int_distribution<long long>(a, b)(rng);
}
int main(int argc, char** argv) {
	rng.seed(argc > 1 ? atoi(argv[1]) : 0);
	int n = rnd(1, 8);
	cout << n << "\n";
	// array of n values in [1, 10]
	for (int i = 0; i < n; i++) cout << rnd(1, 10) << " \n"[i == n - 1];
	// tree with n nodes: node i gets a random earlier parent
	for (int i = 2; i <= n; i++) cout << rnd(1, i - 1) << " " << i << "\n";
	// permutation of 1..n
	vector<int> p(n);
	iota(p.begin(), p.end(), 1);
	shuffle(p.begin(), p.end(), rng);
	for (int i = 0; i < n; i++) cout << p[i] << " \n"[i == n - 1];
	// string of length n over 'a'..'c'
	string s;
	for (int i = 0; i < n; i++) s += char('a' + rnd(0, 2));
	cout << s << "\n";
}
