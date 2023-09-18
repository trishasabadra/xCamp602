#include </usr/local/include/bits/stdc++.h>
//#include <bits/stdc++.h>
#define ms(x, a) memset(x, a, sizeof(x))
const int MX = 1e6+1, MOD = 998244353;

using namespace std;
typedef pair<int, int> pi;
typedef long long ll;
#define f first
#define s second

// return a^b in O(log b) time
ll binpow(ll a, ll b, ll p) {
    ll res = 1;
    a %= p;
    while (b > 0) {
        if (b & 1) res = (res*a) % p;
        a = (a*a) % p;
        b >>= 1;
    }
    return res;
}
ll modInverse(ll n, ll p) {
    return binpow(n, p-2, p);
}

ll fct[MX]; // factorial
ll choose(int n, int r) {
    return fct[n]*modInverse(fct[r], MOD) % MOD * modInverse(fct[n-r], MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < MX; i++) fct[i] = i == 0 ? 1 : fct[i-1]*i % MOD;

    int n, k; cin >> n >> k;

    ll ans = ((n+1)/2 * binpow(n, k, MOD) + MOD) % MOD;
    if (k % 2 == 1) cout << ans;
    else {
        ll sum = 0;
        for (int i = 1; i < n; i++) {
            sum += (choose(k, k/2) * binpow(i, k/2, MOD) % MOD) * binpow(n-i, k/2, MOD) % MOD;
            sum %= MOD;
            cout << sum << "\n"; // debug
        }
        cout << sum << " " << ans << "\n";
        cout << (ans - sum/2 + MOD) % MOD;
    }
}
/*
if k is odd, then the answer is (n+1)/2 * n^k
if k is even:
    sum over i from 1 to n: (k choose k/2) * i^(k/2) * (n-i)^(k/2)
    answer is n+1/2 * n^k - sum/2
*/
