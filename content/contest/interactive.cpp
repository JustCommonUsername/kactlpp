// Interactive problems: flush after EVERY query (endl or cout.flush();
// with the template's cin.tie(0) nothing flushes for you), never print
// debug output to stdout (use cerr), read the answer before the next
// query, count your queries, and exit at once if the judge sends -1.
// Example: guess a hidden number in [1, n]; judge says <, > or =.
int main() {
	ll n;
	cin >> n;
	ll lo = 1, hi = n, ans = -1;
	while (lo <= hi) {
		ll mid = (lo + hi) / 2;
		cout << "? " << mid << endl;    // endl flushes
		string reply;
		cin >> reply;
		if (reply == "-1") return 0;    // invalid query or too many
		if (reply == "=") { ans = mid; break; }
		if (reply == "<") hi = mid - 1; // hidden number is smaller
		else lo = mid + 1;
	}
	cout << "! " << ans << endl;
}
