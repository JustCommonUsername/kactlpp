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
template<class A,class B> ostream& operator<<(ostream&o,const pair<A,B>&p);
template<class T,class=decltype(begin(declval<T>())),class=enable_if_t<!is_same_v<T,string>>> ostream& operator<<(ostream&o,const T&v){o<<'{';string s;for(auto&x:v)o<<s<<x,s=", ";return o<<'}';}
template<class A,class B> ostream& operator<<(ostream&o,const pair<A,B>&p){return o<<'('<<p.first<<", "<<p.second<<')';}
void _d(){cerr<<"]\n";}
template<class H,class...T> void _d(H h,T...t){cerr<<h<<(sizeof...(t)?", ":"");_d(t...);}
#define deb(...) cerr<<"["<<#__VA_ARGS__<<"] = [",_d(__VA_ARGS__)
#else
#define deb(...)
#endif
// END-DEBUGGER

int main() {
	cin.tie(0)->sync_with_stdio(0);

}
