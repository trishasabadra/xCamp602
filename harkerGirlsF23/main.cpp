#include </usr/local/include/bits/stdc++.h>
//#include <bits/stdc++.h>
#define ms(x, a) memset(x, a, sizeof(x))
const int MX = 1e5+5, MOD = 1e9+7;

using namespace std;
typedef pair<int, int> pi;
typedef long long ll;
#define f first
#define s second

int n, dist[501][501], dp[501];
vector<pi> t;
bool vis[501];
void dfs(int cur, int i) {
    for (int j = cur; j < n; j++) {
        if (j == i && i != 0) continue;
        if (dist[t[i].s][t[j].s] <= t[j].f - t[i].f) {
            if (!vis[j]) dfs(t[j].f, j);
            dp[i] = max(dp[i], dp[j] + 1);
            vis[j] = true;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int a; cin >> a;
        t.push_back({a, i});
    }
    sort(t.begin(), t.end());

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> dist[i][j];
    }


    for (int i = 0; i < n; i++) {
        dp[i] = 1; vis[i] = 0;
    }
    dfs(0, 0);

    cout << dp[0];
    //for (int i = 0; i < n; i++) cout << dp[i] << " ";
}
/*
find best edge between two nodes
 for each pair of nodes must know the path length
 then answer = distance + sum of end points
 dp
 want to maximize path length but also added edge
 is it always between two largest?
 is it always the one largest?

 binary search on answer?
 binary search on path length?

 ___
 binary search on maximum number of passengers he can pick up
 sort from first time to last time
 dp[i][j] = maximum number of stops he can make from the first i stops, current stop is k
 dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] + 1

 for all k from i to n:
 IF dist[k][i] <= t[i] - t[k] THAN dp[i][i] = max over dp[i-1][k] +1


if we take the stop, it has to in time
 knapsack dp, can take the stop or not

*/
