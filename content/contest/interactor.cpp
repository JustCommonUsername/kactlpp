// Local judge for interactive.cpp: ./interactor <seed>. Makes the
// hidden data from the seed, replies on cout with endl, verdict on
// cerr, returns nonzero on failure. Run with problemInteraction.sh.
int main(int argc, char** argv) {
	mt19937 rng(argc > 1 ? atoi(argv[1]) : 0);
	ll n = rng() % 1000 + 1, x = rng() % n + 1, q = 0, lim = 10;
	cout << n << endl;
	string t;
	ll v;
	while (cin >> t >> v) {
		if (t == "!") {
			cerr << (v == x ? "OK" : "WA") << ", n=" << n << " x=" << x
			     << " queries=" << q << "\n";
			return v != x;
		}
		if (++q > lim) {
			cerr << "too many queries\n";
			cout << -1 << endl;
			return 1;
		}
		cout << (x < v ? "<" : x > v ? ">" : "=") << endl;
	}
	cerr << "no answer, n=" << n << " x=" << x << "\n";
	return 1;
}
