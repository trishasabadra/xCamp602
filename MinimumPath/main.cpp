#include <bits/stdc++.h>
//#include </usr/local/include/bits/stdc++.h>

using namespace std;
typedef pair<int, int> pi;
typedef long long ll;
#define f first
#define s second
const int N = 2e5+1;

int main() {
  int n, m; cin >> n >> m;
  vector<pi> g[N];
  for (int i = 0; i < m; i++) {
    int v, u, w; cin >> v >> u >> w;
    v--; u--;
    g[v].push_back({u, w});
    g[u].push_back({v, w});
  }

    ll d[n][2][2]; // node from the initial graph, flag that some edge has been subtracted, flag that some edge has been added
  // base case
  for (int i = 0; i < n; i++)
    for (int j = 0; j < 2; j++)
      for (int k = 0; k < 2; k++) d[i][j][k] = (ll)1e18;
  d[0][0][0] = 0;

  // dijkstra
  set<pair<ll, array<int, 3>>> q;
  q.insert({0, {0, 0, 0}});
  while (!q.empty()) {
      int v = q.begin()->s[0], mx = q.begin()->s[1], mn = q.begin()->s[2];
    q.erase(q.begin());
    for (auto [u, w] : g[v]) {
      for (int i = 0; i <= 1 - mx; i++) {
        for (int j = 0; j <= 1 - mn; j++) {
          if (d[u][mx | i][mn | j] > d[v][mx][mn] + (1 - i + j) * w) {
            auto it = q.find({d[u][mx | i][mn | j], {u, mx | i, mn | j}});
            if (it != q.end())
              q.erase(it);
            d[u][mx | i][mn | j] = d[v][mx][mn] + (1 - i + j) * w;
            q.insert({d[u][mx | i][mn | j], {u, mx | i, mn | j}});
          }
        }
      }
    }
  }

  for (int i = 1; i < n; i++) cout << d[i][1][1] << " ";
}
/*
 weight of path = sum of the weights of the edges - max weight + min weight
 find the min weight path from 1st vertex to ith vertex for all i

 solve the problem where you can subtract any edge and add any edge -> will automatically subtract max and add min
 store node from the initial graph, flag that some edge has been subtracted, flag that some edge has been added
 */