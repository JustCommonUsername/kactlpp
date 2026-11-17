/**
 * Author: Håkan Terelius, rewritten for readability
 * Date: 2009-08-26
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 * Description: Sieve up to \texttt{LIM}: \texttt{spf[i]} = smallest prime factor
 * of i, \texttt{primes} = all primes below LIM. \texttt{factorize(n)} returns
 * \{prime, exponent\} pairs: with the sieve for $n <$ LIM in $O(\log n)$,
 * otherwise by trial division in $O(\sqrt n)$ (fine up to $10^{12}$-ish).
 * Usage: sieve(); auto f = factorize(360); // {{2,3},{3,2},{5,1}}
 * Time: $O(LIM \log \log LIM)$ for the sieve.
 */
#pragma once

const ll LIM = 1e7;
vi spf, primes;

void sieve() {
	spf.assign(LIM, 0);
	for (ll i = 2; i < LIM; i++) {
		if (spf[i] != 0) continue; // not prime
		primes.pb(i);
		for (ll j = i; j < LIM; j += i)
			if (spf[j] == 0) spf[j] = i;
	}
}

vector<ii> factorize(ll n) {
	vector<ii> res;
	if (n < SZ(spf)) {
		while (n > 1) {
			ll p = spf[n], e = 0;
			while (n % p == 0) n /= p, e++;
			res.pb({p, e});
		}
		return res;
	}
	for (ll p = 2; p * p <= n; p++) {
		if (n % p != 0) continue;
		ll e = 0;
		while (n % p == 0) n /= p, e++;
		res.pb({p, e});
	}
	if (n > 1) res.pb({n, 1});
	return res;
}
