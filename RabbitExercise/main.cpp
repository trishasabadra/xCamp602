/*
Problem: Rabbit Exercise
 Link: https://atcoder.jp/contests/agc006/tasks/agc006_c?lang=en
 */

#include </usr/local/include/bits/stdc++.h>
//#include <bits/stdc++.h>
#define ms(x, a) memset(x, a, sizeof(x))

using namespace std;
typedef pair<int, int> pi;
typedef long long ll;
#define f first
#define s second

int n;
vector<ll> applySwap(vector<ll> sequence, vector<ll> permutation) {
    vector<ll> newSequence(n-1);
    for(int i = 0; i < n-1; i++) {
        newSequence[i] = sequence[permutation[i]];
    }
    return newSequence;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vector<pair<ll, int>> pos; // position, index
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        pos.push_back({x, i});
    }

    vector<ll> dist;
    for (int i = 0; i < n-1; i++) {
        dist.push_back(pos[i+1].f - pos[i].f);
    }

    // create permutation
    ll m, k; cin >> m >> k;
    vector<ll> swaps;
    for (int i = 0; i < n-1; i++) swaps.push_back(i);
    for (int i = 0; i < m; i++) {
        ll x; cin >> x;
        swap(swaps[x-1], swaps[x-2]);
    }
//    for (int i = 0; i < n-1; i++) cout << swaps[i] << " ";
//    cout << "\n";

    // apply swaps k times with binary exponentiation
    while (k > 0) {
        if (k & 1) {
            dist = applySwap(dist, swaps);
        }
        swaps = applySwap(swaps, swaps);
        k >>= 1;
    }

//    for (int i = 0; i < n-1; i++) cout << dist[i] << " ";
//    cout << "\n";

    ll ans[n]; ans[0] = pos[0].f;
    for (int i = 1; i < n; i++) ans[i] = ans[i-1] + dist[i-1];

    for (int i = 0; i < n; i++) cout << ans[i] << "\n";

}
/*
expected position = 1/2 * (2x_{i+1} - x_i) + 1/2 * (2x_{i-1} - x_i)
= x_{i+1} + x_{i-1} - x_i

*/
