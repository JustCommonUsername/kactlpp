// Interactive problems: flush after EVERY query (endl or cout.flush()),
// never print debug output to stdout (use cerr), read the answer
// before the next query, and count your queries against the limit.
// Example: guess a hidden number in [1, n]; judge says <, > or =.
int main() {
	ll n;
	cin >> n;
	ll lo = 1, hi = n;
	while (lo <= hi) {
		ll mid = (lo + hi) / 2;
		cout << "? " << mid << endl;    // endl flushes
		string reply;
		cin >> reply;
		if (reply == "=") break;
		if (reply == "<") hi = mid - 1; // hidden number is smaller
		else lo = mid + 1;
	}
	cout << "! " << (lo + hi) / 2 << endl;
}
