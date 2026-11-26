#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
#define mset(a, v) memset((a), (v), sizeof(a))
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;

// DEBUGGER
#ifdef LOCAL
template<class T> void pr(const T& x) {
	if constexpr (requires { x.first; })
		cerr << "(", pr(x.first), cerr << ", ", pr(x.second), cerr << ")";
	else if constexpr (requires { begin(x); } && !is_convertible_v<T, string>) {
		cerr << "{";
		for (auto&& y : x) cerr << " ", pr(y);
		cerr << " }";
	} else cerr << x;
}
#define deb(...) cerr << "[" #__VA_ARGS__ "] =", \
	[](auto&&... a) { ((cerr << " ", pr(a)), ...); cerr << "\n"; }(__VA_ARGS__)
#else
#define deb(...)
#endif
// END-DEBUGGER

int main() {
	cin.tie(0)->sync_with_stdio(0);

}
