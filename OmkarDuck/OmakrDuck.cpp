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

    int n; cin >> n;

    ll grid[n][n], cnt = 2;
    for(int line = 1; line <= (2*n - 1); line++) {
        int c =  max(0, line - n); // column index
        ll count = min(min(line, n), (n - c));
        for(int j = 0; j < count; j++) {
            if ((c + j) % 2 == 0) grid[min(n, line) - j - 1][c + j] = 0; // even columns are 0
            else grid[min(n, line) - j - 1][c + j] = cnt;
        }
        cnt *= 2;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << " " << flush;
        }
        cout << endl;
    }

    int q; cin >> q;
    while (q--) {
        ll x; cin >> x;
        int r = 1, c = 1; // current row and column
        cout << "1 1" << endl;
        for (int i = 2; r < n || c < n; i++) {
            if (x & (1LL << i)) { // ith bit is on
                if (c % 2 == 1) c++;
                else r++;
            }
            else {
                if (c % 2 == 1) r++;
                else c++;
            }
            cout << r << " " << c << endl;
        }
    }
}
/*

*/
