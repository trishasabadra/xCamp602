#include </usr/local/include/bits/stdc++.h>
//#include <bits/stdc++.h>
#define ms(x, a) memset(x, a, sizeof(x))
const int MX = 1e6+5, MOD = 1e9+7;

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
    return (fct[n]*modInverse(fct[r], MOD) % MOD * modInverse(fct[n-r], MOD) % MOD) % MOD;
}

ll posMod(ll i) {
    return (i % MOD + MOD) % MOD;
}

ll n, h, dp[5500], arr[5500];
ll solve(int house){
    if(dp[house] != -1){
        return dp[house];
    }
    ll ans = fct[arr[house]];
    for(int i = 0; i < house; i++){
        ll val = (fct[arr[house]-arr[i]] * solve(i))%MOD;
        ans -= val;
        ans = posMod(ans);
    }
    dp[house] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // factorial
    fct[0] = 1;
    for (ll i = 1; i < MX; i++) fct[i] = (fct[i-1]*i) % MOD;

    cin >> n >> h; // n = # knights, h = # houses
    for (int i = 0; i < h; i++) {
        cin >> arr[i];
        if (i > 0) arr[i] += arr[i-1]; // prefix sum
    }
    arr[h] = n;
    ms(dp, -1);

    cout << solve(h);
}
/*

*/
