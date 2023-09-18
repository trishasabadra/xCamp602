#include </usr/local/include/bits/stdc++.h>
//#include <bits/stdc++.h>
#define ms(x, a) memset(x, a, sizeof(x))
const int MX = 1e6+5, MOD = 1e9+7;

using namespace std;
typedef pair<int, int> pi;
typedef long long ll;
#define f first
#define s second

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

ll posMod(ll i) {
    return (i % MOD + MOD) % MOD;
}

ll modDiv(ll a, ll b) { // a/b % MOD
    return a*modInverse(b, MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // factorial
    fct[0] = 1;
    for (ll i = 1; i < MX; i++) fct[i] = (fct[i-1]*i) % MOD;

    // power
    ll pow2[MX]; // 2^i
    pow2[0] = 1;
    for (int i = 1; i < MX; i++) pow2[i] = posMod(pow2[i-1]*2);

    int t; cin >> t;
    while (t--) {
        ll n, m, k; cin >> n >> m >> k;

        if(n == m) { // add all
            cout << posMod(n*k) << "\n";
            continue;
        }

        ll ans = 0;
        for (int i = 0; i <= m; i++) {
            ans += posMod(modDiv(posMod(choose(n - i - 1, m - i) * (i*k % MOD)), pow2[n-i])); // # of paths) * # of times to add
            ans %= MOD;
            //cout << ans << " "; // debug
        }
        cout << posMod(ans) << '\n';
    }
}
/*

dp[i][j] = i turns remaining, Bob needs to add j times
calculate how many paths from point (i,i) to (n,m) exist that don't pass through any points (j,j) where j > i
then divide by 2^(n-i)

because the dp transition is dp[i][j] = (dp[i - 1][j] + d[i - 1][j - 1])/2
which is like # of paths but every time you take one edge you divide the # by 2
so at then end you divide by 2^(total path length)

ans = sum of (k*i)/2^(n-i)* funny choose things for each i from 1 to m

*/
