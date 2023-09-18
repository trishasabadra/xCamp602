#include </usr/local/include/bits/stdc++.h>
//#include <bits/stdc++.h>
#define ms(x, a) memset(x, a, sizeof(x))
const int MX = 1e5+5, MOD = 1e9+7;

using namespace std;
typedef pair<int, int> pi;
typedef long long ll;
#define f first
#define s second

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m; cin >> n >> m;
    vector<int> adj[2*n];
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--; // 0-indexed
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int a = 0; a < n; a++) {
        int vis[n]; ms(vis, 0);
        for (int b : adj[a]) {
            for (int c : adj[b]) {
                if (a == c) continue;
                vis[c]++;
                if (vis[c] == 2) {
                    cout << 2;
                    return 0;
                }
            }
        }
    }
    cout << 3;

}